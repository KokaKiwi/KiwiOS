#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/lfb.h>
#include <sys/io.h>
#include <vga.h>

void setup_video_bochs(uint32_t width, uint32_t height)
{
    uint16_t i;

    println("Setting up video driver...");
    outb(VBE_DISPI_IOPORT_INDEX, 0x00);
    i = inb(VBE_DISPI_IOPORT_DATA);
    if (i < 0xb0c0 || i > 0xb0c6)
    {
        return ;
    }

    outb(VBE_DISPI_IOPORT_DATA, 0xb0c4);
    i = inb(VBE_DISPI_IOPORT_DATA);

    // Disable VBE
    outb(VBE_DISPI_IOPORT_INDEX, 0x04);
    outb(VBE_DISPI_IOPORT_DATA, 0x00);
    // Setting X res
    outb(VBE_DISPI_IOPORT_INDEX, 0x01);
    outb(VBE_DISPI_IOPORT_DATA, width);
    // Setting Y res
    outb(VBE_DISPI_IOPORT_INDEX, 0x02);
    outb(VBE_DISPI_IOPORT_DATA, height);
    // Set bpp to 32
    outb(VBE_DISPI_IOPORT_INDEX, 0x03);
    outb(VBE_DISPI_IOPORT_DATA, VBE_SCREEN_BPP);
    // Set Virtual Height to stuff
    outb(VBE_DISPI_IOPORT_INDEX, 0x07);
    outb(VBE_DISPI_IOPORT_DATA, VBE_SCREEN_VHEIGHT);
    // Enable VBE
    outb(VBE_DISPI_IOPORT_INDEX, 0x04);
    outb(VBE_DISPI_IOPORT_DATA, 0x41);
}

void setup_video(uint32_t width, uint32_t height)
{
    setup_video_bochs(width, height);
}