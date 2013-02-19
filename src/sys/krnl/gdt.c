#include <gdt.h>
#include <string.h>

gdt_entry_t kgdt[GDTSIZE];
gdt_ptr_t kgdtr;

void init_gdt()
{
    // Init segment descriptors
    init_gdt_entry(0x0, 0x0, 0x0, 0x0, &kgdt[0]);            // NULL
    init_gdt_entry(0x0, 0xfffff, 0x9b, 0x0d, &kgdt[1]);      // Code
    init_gdt_entry(0x0, 0xfffff, 0x93, 0x0d, &kgdt[2]);      // Data
    init_gdt_entry(0x0, 0x0, 0x97, 0x0d, &kgdt[3]);          // Stack

    kgdtr.base = GDTBASE;
    kgdtr.limit = GDTSIZE * sizeof(gdt_entry_t);

    memcpy((void *) kgdtr.base, (void *) kgdt, kgdtr.limit);

    asm("lgdtl (kgdtr)");
    
    asm("movw $0x10, %ax     \n \
         movw %ax, %ds       \n \
         movw %ax, %es       \n \
         movw %ax, %fs       \n \
         movw %ax, %gs       \n \
         ljmp $0x08, $next   \n \
         next:               \n");
}

void init_gdt_entry(uint32_t base, uint32_t limit, uint8_t access, uint8_t other, gdt_entry_t * entry)
{
    entry->limit_0_15 = (limit & 0xffff);
    entry->limit_16_19 = (limit & 0xf0000) >> 16;

    entry->base_0_15 = (base & 0xffff);
    entry->base_16_23 = (base & 0xff0000) >> 16;
    entry->base_24_31 = (base & 0xff000000) >> 24;

    entry->access = access;
    entry->other = (other & 0xf);
}