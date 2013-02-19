#include <utils/panic.h>
#include <sys/io.h>
#include <stdio.h>

void __panic(const char *msg, const char *filename, int line)
{
    printf("*** SYSTEM PANIC ***\n");
    printf("Message: %s\n", msg);
    printf("In file %s:%u\n", filename, line);
    printf("********************");
    hlt;
    while(1);
}