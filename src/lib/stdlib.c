#include <stdlib.h>
#include <heap.h>

unsigned long seed = 3255224;

int rand()
{
    seed = seed * 1103515245 + 12345;
    return (unsigned int) (seed / 65536) % RAND_MAX;
}

int abs(int value)
{
    return (value >= 0 ? value : -value);
}

long labs(long value)
{
    return (value >= 0L ? value : -value);
}

int atoi(const char *str)
{
    int n = 0, m = 1;

    if(*str == '-')
    {
        m = -1;
        str++;
    }

    while(*str)
    {
        n *= 10;
        n += (*str - '0');

        str++;
    }

    n *= m;

    return n;
}

div_t div(int num, int denom)
{
    div_t result;
    
    result.quot = num / denom;
    result.rem = num - (result.quot * denom);
    
    if (num < 0 && result.rem > 0)
    {
        result.quot++;
        result.rem -= denom;
    }
    
    return result;
}

ldiv_t ldiv(long numer, long denom)
{
    ldiv_t result;
    
    result.quot = numer / denom;
    result.rem = numer % denom;
    
    if (numer < 0 && result.rem > 0)
    {
        result.quot++;
        result.rem -= denom;
    }
    
    return result;
}

void *malloc(size_t size)
{
    return heap_malloc(size);
}

void *calloc(size_t num, size_t size)
{
    return malloc(num * size);
}

void *realloc(void *ptr, size_t size)
{
    return NULL;
}

void free(void *block)
{
    heap_free(block);
}
