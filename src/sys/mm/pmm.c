#include <pmm.h>
#include <vmm.h>
#include <utils/panic.h>
#include <stdio.h>
#include <string.h>

uint8_t *pmm_mmap;
uint32_t pmm_memsize;

inline void pmm_mmap_set(uint32_t page)
{
    pmm_mmap[page / 8] |= (1 << (page % 8));
}

inline void pmm_mmap_unset(uint32_t page)
{
    pmm_mmap[page / 8] &= ~(1 << (page % 8));
}

void init_pmm(uint8_t *mmap, uint32_t memsize)
{
    int i;

    pmm_mmap = mmap;
    pmm_memsize = memsize / PAGE_SIZE;

    memset(pmm_mmap, 0, memsize / PAGE_SIZE / 8);

    // Init kernel space
    for(i = PADDR_TO_VADDR(0x0); i < PADDR_TO_VADDR(0x20000); i++)
    {
        pmm_mmap_set(i);
    }

    // Init hardware space
    for(i = PADDR_TO_VADDR(0xA0000); i < PADDR_TO_VADDR(0x100000); i++)
    {
        pmm_mmap_set(i);
    }
}

uint32_t pmm_alloc_page()
{
    uint32_t page = -1;
    int byte, bit;

    for(byte = 0; byte < pmm_memsize / 8 && page == -1; byte++)
    {
        if(pmm_mmap[byte] != 0xff)
        {
            for(bit = 0; bit < 8 && page == -1; bit++)
            {
                if(!(pmm_mmap[byte] & (1 << bit)))
                {
                    page = 8 * byte + bit;
                    pmm_mmap_set(page);
                }
            }
        }
    }

    return VADDR_TO_PADDR(page);
}

void pmm_free_page(uint32_t page)
{
    pmm_mmap_unset(PADDR_TO_VADDR(page));
}