#ifndef VMM_H_
#define VMM_H_

#include "stdint.h"

#define PAGING_FLAG                 0x80000000

#define PAGE_DIR_ADDRESS            0xffbff000

#define PAGE_MASK                   0xfffff000
#define MAX_PAGES                   1024

#define VADDR_PD_OFFSET(addr)       ((addr) >> 22) & 0xffc
#define VADDR_PT_OFFSET(addr)       ((addr) >> 12) & 0x3ff
#define VADDR_PG_OFFSET(addr)       (addr) & 0xfff

#define PAGE_SIZE                   4096

#define VADDR_TO_PADDR(addr)        (addr) * PAGE_SIZE
#define PADDR_TO_VADDR(addr)        (addr) / PAGE_SIZE

#define PAGE_FLAG_PRESENT           0x001
#define PAGE_FLAG_WRITABLE          0x002
#define PAGE_FLAG_USER              0x004
#define PAGE_FLAG_ACCESSED          0x020
#define PAGE_FLAG_DIRTY             0x040
#define PAGE_FLAG_GLOBAL            0x100

typedef union _pt_entry_t pt_entry_t;
union _pt_entry_t
{
    uint32_t raw;

    struct
    {
        uint32_t flags :12;

        uint32_t base :20;
    } basic __attribute__ ((packed));

    struct
    {
        uint32_t present :1;            // 0x001
        uint32_t writable :1;           // 0x002
        uint32_t user :1;               // 0x004
        uint32_t pwt :1;                // 0x008
        uint32_t pcd :1;                // 0x010
        uint32_t accessed :1;           // 0x020
        uint32_t dirty :1;              // 0x040
        uint32_t pat :1;                // 0x080
        uint32_t global :1;             // 0x100
        uint32_t avail :3;
        
        uint32_t page_base :20;
    } entry __attribute__ ((packed));
};
typedef pt_entry_t* page_table_t;

typedef union _pd_entry_t pd_entry_t;
union _pd_entry_t
{
    uint32_t raw;

    struct
    {
        uint32_t flags :12;

        uint32_t base :20;
    } basic __attribute__ ((packed));
    
    struct
    {
        uint32_t present :1;            // 0x001
        uint32_t writable :1;           // 0x002
        uint32_t user :1;               // 0x004
        uint32_t pwt :1;                // 0x008
        uint32_t pcd :1;                // 0x010
        uint32_t accessed :1;           // 0x020
        uint32_t _unused :1;            // 0x040
        uint32_t page_size :1;          // 0x080
        uint32_t global :1;             // 0x100
        uint32_t avail :3;
        
        uint32_t page_table_base :20;
    } entry __attribute__ ((packed));
};
typedef pd_entry_t* page_directory_t;

void init_vmm(void);

void vmm_map(uint32_t, uint32_t);
void vmm_unmap(uint32_t);
inline page_table_t vmm_create_pd_entry(pd_entry_t *);
pt_entry_t *vmm_get(uint32_t);

void vmm_switch_page_directory(page_directory_t);
void vmm_enable_paging(void);

#endif