#include <pmm.h>
#include <vmm.h>
#include <idt.h>
#include <string.h>
#include <utils/panic.h>

void page_fault(registers_t *);

page_directory_t page_directory;

void init_vmm()
{
    int i;
    page_table_t page_table0;
    uint32_t page_addr;

    // Register Page Fault handler
    register_interrupt_handler(PAGEFAULT_ISR, &page_fault);

    page_directory = (page_directory_t) pmm_alloc_page();
    memset(page_directory, 0, MAX_PAGES * sizeof(pd_entry_t));

    page_table0 = vmm_create_pd_entry(&page_directory[0]);
    if(page_table0)
    {
        // Init Page Table 0
        for(i = 0, page_addr = 0; i < 1024; i++, page_addr += 4096)
        {
            page_table0[i].basic.base = page_addr >> 12;
            page_table0[i].entry.present = 1;
            page_table0[i].entry.writable = 1;
        }

        vmm_switch_page_directory(page_directory);
        vmm_enable_paging();
    }
    else
    {
        panic("Error during VMM init.");
    }
}

void vmm_map(uint32_t vaddr, uint32_t paddr)
{
    pt_entry_t *pt;

    pt = vmm_get(vaddr);

    pt->basic.base = paddr >> 12;

    pt->entry.present = 1;
    pt->entry.writable = 1;
}

void vmm_unmap(uint32_t vaddr)
{
    pt_entry_t *pt;

    pt = vmm_get(vaddr);

    memset(pt, 0, sizeof(pt_entry_t));
}

inline page_table_t vmm_create_pd_entry(pd_entry_t *pd)
{
    page_table_t page_table;

    page_table = (page_table_t) pmm_alloc_page();
    if(!page_table)
    {
        return 0;
    }

    memset(page_table, 0, MAX_PAGES * sizeof(pt_entry_t));

    pd->entry.present = 1;
    pd->entry.writable = 1;
    pd->basic.base = (uint32_t) page_table >> 12;

    return page_table;
}

pt_entry_t *vmm_get(uint32_t vaddr)
{
    pt_entry_t *pt;
    pd_entry_t *pd;
    page_table_t page_table;

    pd = &page_directory[VADDR_PD_OFFSET(vaddr)];
    if(!pd->entry.present)
    {
        page_table = vmm_create_pd_entry(pd);
        if(!page_table)
        {
            return NULL;
        }
    }
    else
    {
        page_table = (page_table_t) (uint32_t) (pd->basic.base << 12);
    }

    pt = &page_table[VADDR_PT_OFFSET(vaddr)];

    return pt;
}

void vmm_switch_page_directory(page_directory_t pd)
{
    asm volatile ("\
        mov %0, %%eax\n\
        mov %%eax, %%cr3\n\
    " : : "r" (pd));
}

void vmm_enable_paging()
{
    asm volatile ("\
        mov %%cr0, %%eax \n\
        or %0, %%eax \n\
        mov %%eax, %%cr0\
    ":: "i" (PAGING_FLAG));
}

void page_fault(registers_t *regs)
{
    panic("Page fault!");
}
