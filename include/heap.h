#ifndef HEAP_H_
#define HEAP_H_

#include "stddef.h"
#include "stdint.h"

#define HEAP_START_ADDR     0xd0000000

typedef struct _heap_header_t heap_header_t;
struct _heap_header_t
{
    heap_header_t *prev, *next;
    uint32_t allocated :1;
    uint32_t size :31;
};

void init_heap(void);

void *heap_malloc(size_t);
void heap_free(void *);

#endif