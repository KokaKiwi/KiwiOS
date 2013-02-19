#ifndef VGA_H_
#define VGA_H_

#include "stdint.h"
#include "sys/krnl.h"

#define COLOR_BLACK                 0x0
#define COLOR_BLUE                  0x1
#define COLOR_GREEN                 0x2
#define COLOR_CYAN                  0x3
#define COLOR_RED                   0x4
#define COLOR_MAGENTA               0x5
#define COLOR_YELLOW                0x6
#define COLOR_WHITE                 0x7

#define BG_BLACK                    0x00
#define BG_BLUE                     0x10
#define BG_GREEN                    0x20
#define BG_CYAN                     0x30
#define BG_RED                      0x40
#define BG_MAGENTA                  0x50
#define BG_YELLOW                   0x60
#define BG_WHITE                    0x70

#define SURINTENSITY                0x8
#define BLINK                       0x80

#define VGA_SCREEN_MODE_TEXT        0
#define VGA_SCREEN_MODE_GRAPHICS    1

#define VGA_VRAM_START              0xB8000
#define VGA_VRAM_END                0xB8FA0
#define VGA_SCREEN_WIDTH            80
#define VGA_SCREEN_HEIGHT           25

typedef struct _vga_state_t vga_state_t;
struct _vga_state_t
{
    uint8_t     x;
    uint8_t     y;
    char        attribute;
};

typedef struct _vga_screen_t vga_screen_t;
struct _vga_screen_t
{
    char        *vram_start;
    char        *vram_end;
    uint32_t    width;
    uint32_t    height;
    int         mode;
};

void vga_putchar        (char);
void vga_puts           (const char *);
void vga_clear          (void);
void vga_scroll         (unsigned int);
void vga_move_cursor    (uint8_t, uint8_t);
void vga_show_cursor    (void);
void vga_hide_cursor    (void);
void vga_init           (void);

extern vga_screen_t vga_screen;

#endif
