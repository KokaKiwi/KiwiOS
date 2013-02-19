#ifndef STRING_H_
#define STRING_H_

#include "stddef.h"
#include "stdint.h"

#define FAST_STRCMP(x, y)  (*(x) != *(y) ? ((unsigned char) *(x) - (unsigned char) *(y)) : strcmp((x), (y)))

void       *memcpy  (void *, const void *, size_t);
void       *memset  (void *, unsigned, size_t);
int        memcmp   (const void *, const void *, size_t);
char       *strcpy  (char *, const char *);
char       *strncpy (char *, const char *, size_t);
size_t     strlen   (const char *);
int        strcmp   (const char *, const char *);
char       *strdup  (const char *);
char       *strcat  (char *, const char *);
char       *strncat (char *, char *, size_t);
const char *strchr  (const char *, char);

#endif
