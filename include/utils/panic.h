#ifndef PANIC_H_
#define PANIC_H_

#define panic(msg)  __panic(msg, __FILE__, __LINE__)

void __panic(const char *, const char *, int);

#endif