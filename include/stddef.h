#ifndef STDDEF_H_
#define STDDEF_H_

#include "stdint.h"

#ifndef NULL
#define NULL ((void*) 0)
#endif

#ifndef SIZE_T_
#define SIZE_T
typedef uint32_t size_t;
#endif

#ifndef offsetof
#define offsetof(s, m) ((size_t)&(((s *) 0)->m))
#endif

#ifndef container_of
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );\
            })
#endif

#endif
