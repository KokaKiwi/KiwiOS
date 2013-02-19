#ifndef STDLIB_H_
#define STDLIB_H_

#include <stddef.h>
#include <stdint.h>

#define srand(newSeed)  seed = newSeed

#define RAND_MAX        0x7fff

#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1

#ifndef _DIV_T_DEFINED
#define _DIV_T_DEFINED

typedef struct _div_t div_t;
struct _div_t
{
    int quot;
    int rem;
};

typedef struct _ldiv_t ldiv_t;
struct _ldiv_t
{
    long quot;
    long rem;
};

#endif

int rand(void);

int abs(int);
long labs(long);

int atoi(const char *);

div_t div(int, int);
ldiv_t ldiv(long, long);

void *malloc(size_t);
void *calloc(size_t, size_t);
void *realloc(void *, size_t);
void free(void *);

unsigned long seed;

#endif
