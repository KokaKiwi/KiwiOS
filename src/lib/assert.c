#include <assert.h>
#include <utils/panic.h>
#include <stdio.h>

void __assert(int expr, char *msg, char *filename, int lineno)
{
    if(!expr)
    {
        __panic(msg, filename, lineno);
    }
}
