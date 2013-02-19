#ifndef ASSERT_H_
#define ASSERT_H_

extern void __assert(int, char*, char *, int);

#define assert(expr, msg) ((expr) || (__assert((int) (expr), msg, __FILE__, __LINE__), 0))

#endif
