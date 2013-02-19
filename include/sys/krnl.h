#ifndef KRNL_H_
#define KRNL_H_

#include "stdint.h"
#include "stdarg.h"

typedef struct _console_t console_t;
struct _console_t
{
    void (*putchar)(char);
    void (*puts)(const char *);
    
    void (*clear)(void);
    void (*scroll)(unsigned int);
    
    void (*move_cursor)(uint8_t, uint8_t);
    void (*show_cursor)(void);
    void (*update_cursor)(void);
    void (*hide_cursor)(void);
};

extern console_t console;

#endif
