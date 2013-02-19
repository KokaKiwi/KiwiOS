#include <gnu/multiboot.h>
#include <sys/io.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gdt.h>
#include <idt.h>
#include <vmm.h>
#include <pmm.h>
#include <heap.h>
#include <vga.h>

void start(uint32_t mbmagic, multiboot_info_t *mbi)
{
    // Init primary console
    vga_init();
    console.clear();
    console.hide_cursor();

    println("Starting KiwiOS [0.1.0]...");
    println("Loading kernel...");
    printf("Memory: %uk (lower), %uk (upper)\n", mbi->mem_lower, mbi->mem_upper);

    // Init CPU
    init_gdt();
    init_idt();

    // Init Memory Management
    // Later, we will detecting CPU mmap to determine how much memory we have.
    init_pmm((uint8_t *) (mbi->mem_upper + PAGE_SIZE), 1024 * PAGE_SIZE);
    init_vmm();
    init_heap();

    sti;

    console.show_cursor();
}
