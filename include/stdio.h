#ifndef STDIO_H_
#define STDIO_H_

#include "stddef.h"
#include "stdarg.h"
#include "stdint.h"
#include "sys/krnl.h"
#include "list.h"

int vsprintf(char *, const char *, va_list);

inline void putchar(char);
inline void print(const char *);
inline void puts(const char *);
inline void println(const char *);
void printf(const char *, ...);
int sprintf(char *, const char *, ...);

#endif
