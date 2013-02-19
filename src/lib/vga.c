#include <vga.h>
#include <sys/io.h>
#include <utils/panic.h>
#include <stdio.h>
#include <string.h>

char *vga_base = "0123456789abcdef";

vga_state_t vga_state = {0, 0, COLOR_WHITE};
vga_screen_t vga_screen = { (char *) VGA_VRAM_START, (char *) VGA_VRAM_END, VGA_SCREEN_WIDTH, VGA_SCREEN_HEIGHT, VGA_SCREEN_MODE_TEXT};

void vga_putchar(char c)
{
    static int attribute_mode = 0;
    const char *base_loc;
    char *vram_c = (char *) (vga_screen.vram_start + 2 * vga_state.x + 2 * vga_screen.width * vga_state.y);
    if (attribute_mode > 0)
    {
        switch (attribute_mode)
        {
            case 1:
                base_loc = strchr(vga_base, c);
                if (base_loc != NULL)
                {
                    vga_state.attribute = ((base_loc - vga_base) & 0xff);
                    attribute_mode = 2;
                }
                else
                {
                    attribute_mode = 0;
                    vga_state.attribute = COLOR_WHITE;
                    panic("Wrong string format!");
                }
                break;
            case 2:
                base_loc = strchr(vga_base, c);
                if (base_loc != NULL)
                {
                    vga_state.attribute = (vga_state.attribute << 4) + ((base_loc - vga_base) & 0xff);
                    attribute_mode = 3;
                }
                else if (c == ';')
                {
                    attribute_mode = 1;
                }
                else if (c == ']')
                {
                    attribute_mode = 0;
                }
                else
                {
                    attribute_mode = 0;
                    vga_state.attribute = COLOR_WHITE;
                    panic("Wrong string format!");
                }
                break;
            case 3:
                if (c == ']')
                {
                    attribute_mode = 0;
                }
                else if (c == ';')
                {
                    attribute_mode = 1;
                }
                else
                {
                    attribute_mode = 0;
                    vga_state.attribute = COLOR_WHITE;
                    panic("Wrong string format!");
                }
                break;
            default:
                attribute_mode = 0;
                vga_state.attribute = COLOR_WHITE;
                panic("Wrong string format!");
                break;
        }
    }
    else
    {
        switch (c)
        {
            case '\n':
                vga_state.x = 0;
                vga_state.y++;
                break;
            case '\t':
                vga_state.x = vga_state.x + 8 - (vga_state.x % 8);
                break;
            case '\r':
                vga_state.x = 0;
                break;
            case '\b':
                if (vga_state.x > 0)
                {
                    vga_state.x--;
                }
                break;
            case '\033':
                attribute_mode = 1;
                break;
            default:
                *vram_c = c;
                *(vram_c + 1) = vga_state.attribute;
                
                vga_state.x++;
                if (vga_state.x > 79)
                {
                    vga_state.x = 0;
                    vga_state.y++;
                }
                break;
        }

        if(vga_state.y >= 25)
        {
            console.scroll(1);
        }
    }
}

void vga_puts(const char *str)
{
    while (*str)
    {
        console.putchar(*str++);
    }
}

void vga_clear()
{
    unsigned char *video;
    
    for (video = (unsigned char *) vga_screen.vram_start;
            video < (unsigned char *) vga_screen.vram_end; video += 2)
    {
        *video = 0;
        *(video + 1) = vga_state.attribute;
    }
}

void vga_scroll(unsigned int amount)
{
    unsigned char *video, *tmp;
    
    for (video = (unsigned char *) vga_screen.vram_start;
            video < (unsigned char *) vga_screen.vram_end; video += 2)
    {
        tmp = (unsigned char *) (video + amount * 160);
        
        if (tmp < (unsigned char *) vga_screen.vram_end)
        {
            *video = *tmp;
            *(video + 1) = *(tmp + 1);
        }
        else
        {
            *video = 0;
            *(video + 1) = 0x07;
        }
    }
    
    vga_state.y -= amount;
    if (vga_state.y < 0)
    {
        vga_state.y = 0;
    }
}

void vga_move_cursor(uint8_t x, uint8_t y)
{
    uint16_t c_pos = y * 80 + x;
    
    outb(0x3d4, 0x0f);
    outb(0x3d5, (uint8_t) (c_pos & 0xff));
    outb(0x3d4, 0x0e);
    outb(0x3d5, (uint8_t) ((c_pos >> 8) & 0xff));
}

void vga_show_cursor()
{
    console.move_cursor(vga_state.x, vga_state.y);
}

void vga_hide_cursor()
{
    console.move_cursor(-1, -1);
}

void vga_init()
{
    console.clear = &vga_clear;
    console.hide_cursor = &vga_hide_cursor;
    console.move_cursor = &vga_move_cursor;
    console.putchar = &vga_putchar;
    console.puts = &vga_puts;
    console.scroll = &vga_scroll;
    console.show_cursor = &vga_show_cursor;
    console.update_cursor = &vga_show_cursor;
}
