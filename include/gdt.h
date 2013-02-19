#ifndef GDT_H_
#define GDT_H_

#include "stdint.h"

#define GDTBASE     0x0     // GDT Address
#define GDTSIZE     0xff    // GDT Size

typedef struct _gdt_entry_t gdt_entry_t;
struct _gdt_entry_t
{
    uint16_t limit_0_15;
    uint16_t base_0_15;
    uint8_t base_16_23;
    uint8_t access;
    uint8_t limit_16_19 :4;
    uint8_t other :4;
    uint8_t base_24_31;
}__attribute__ ((packed));

typedef struct _gdt_ptr_t gdt_ptr_t;
struct _gdt_ptr_t
{
    uint16_t limit;
    uint32_t base;
}__attribute__ ((packed));

void init_gdt(void);
void init_gdt_entry(uint32_t, uint32_t, uint8_t, uint8_t, gdt_entry_t *);

extern gdt_entry_t kgdt[];
extern gdt_ptr_t kgdtr;

#endif