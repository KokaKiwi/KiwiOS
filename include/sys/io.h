#ifndef IO_H_
#define IO_H_

// Halt
#define hlt asm("hlt"::)

// Disable interrupts
#define cli asm("cli"::)

// Enable interrupts
#define sti asm("sti"::)

// Write data on output port
#define outb(port,value) \
        asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value));

// Write data on output port and do a temporisation
#define outbp(port,value) \
        asm volatile ("outb %%al, %%dx; jmp 1f; 1:" :: "d" (port), "a" (value));

// Read data on input port
#define inb(port) ({    \
        unsigned char _v;       \
        asm volatile ("inb %%dx, %%al" : "=a" (_v) : "d" (port)); \
        _v;     \
})

#endif
