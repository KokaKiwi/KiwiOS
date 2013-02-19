#ifndef PMM_H_
#define PMM_H_

#include "stdint.h"
#include "stddef.h"

#define PMM_STACK_ADDRESS       0xff000000

void init_pmm(uint8_t *, uint32_t);

uint32_t pmm_alloc_page(void);
void pmm_free_page(uint32_t);

#endif