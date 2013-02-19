// Mainly copied from https://github.com/rickbutton/os/kernel/mm/heap.c
// I wanted to write my own. But it's very brainfuck :/

#include <heap.h>
#include <pmm.h>
#include <vmm.h>

#include <stdio.h>

uint32_t heap_max = HEAP_START_ADDR;
heap_header_t *heap_first = 0;

void heap_alloc_chunk(uint32_t, size_t);
void heap_free_chunk(heap_header_t *);
void heap_split_chunk(heap_header_t *, size_t);
void heap_glue_chunk(heap_header_t *);

void init_heap()
{

}

void *heap_malloc(size_t size)
{
    heap_header_t *current_header, *prev_header;
    uint32_t chunk_start;

    size += sizeof(heap_header_t);

    current_header = heap_first;
    prev_header = 0;

    while(current_header)
    {
        if(!current_header->allocated && current_header->size >= size)
        {
            heap_split_chunk(current_header, size);
            current_header->allocated = 1;
            return (void *) ((uint32_t) current_header + sizeof(heap_header_t));
        }

        prev_header = current_header;
        current_header = current_header->next;
    }

    if(prev_header)
    {
        chunk_start = (uint32_t) prev_header + prev_header->size;
    }
    else
    {
        chunk_start = HEAP_START_ADDR;
        heap_first = (heap_header_t *) HEAP_START_ADDR;
    }

    // Alloc chunk
    heap_alloc_chunk(chunk_start, size);
    current_header = (heap_header_t *) chunk_start;
    current_header->prev = prev_header;
    current_header->next = 0;
    current_header->allocated = 1;
    current_header->size = size;

    if(prev_header)
    {
        prev_header->next = current_header;
    }

    return (void *) (chunk_start + sizeof(heap_header_t));
}

void heap_free(void *ptr)
{
    heap_header_t *header;

    header = (heap_header_t *) ((uint32_t) ptr - sizeof(heap_header_t));
    header->allocated = 0;

    heap_glue_chunk(header);
}

void heap_alloc_chunk(uint32_t start, size_t length)
{
    uint32_t page;

    while(start + length > heap_max)
    {
        page = pmm_alloc_page();

        vmm_map(heap_max, page);
        heap_max += PAGE_SIZE;
    }
}

void heap_free_chunk(heap_header_t *header)
{
    pt_entry_t *pt;

    header->prev->next = 0;

    if(!header->prev)
    {
        heap_first = 0;
    }

    while((heap_max - PAGE_SIZE) >= (uint32_t) header)
    {
        heap_max -= PAGE_SIZE;
        pt = vmm_get(heap_max);
        pmm_free_page(pt->raw & PAGE_MASK);
        vmm_unmap(heap_max);
    }
}

void heap_split_chunk(heap_header_t *header, size_t length)
{
    heap_header_t *new_header;

    if(header->size - length > sizeof(heap_header_t))
    {
        new_header = (heap_header_t *) ((uint32_t) header + header->size);
        new_header->prev = header;
        new_header->next = 0;
        new_header->allocated = 0;
        new_header->size = header->size - length;

        header->next = new_header;
        header->size = length;
    }
}

void heap_glue_chunk(heap_header_t *header)
{
    if(header->next && !header->next->allocated)
    {
        header->size += header->next->size;
        header->next->next->prev = header;
        header->next = header->next->next;
    }

    if(header->prev && !header->prev->allocated)
    {
        header->prev->size += header->size;
        header->prev->next = header->next;
        header->next->prev = header->prev;
        header = header->prev;
    }

    if(!header->next)
    {
        heap_free_chunk(header);
    }
}
