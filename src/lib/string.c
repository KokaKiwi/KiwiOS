#include <string.h>
#include <stdlib.h>

void *memcpy(void *destination, const void *source, size_t num)
{
    while (num--)
    {
        *((uint8_t *) destination++) = *((const uint8_t *) source++);
    }
    
    return destination;
}

void *memset(void *p, unsigned c, size_t n)
{
    uint8_t *pb = (uint8_t *) p;
    uint8_t *pbend = pb + n;
    while (pb != pbend)
    {
        *pb++ = c;
    }
    return p;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const uint8_t *p1 = ptr1;
    const uint8_t *p2 = ptr2;
    
    while (num-- && (*p1++ == *p2++))
        ;
    
    return (*(uint8_t *) --p1 < *(uint8_t *) --p2) ?
            -1 : (*(uint8_t *) p1 != *(uint8_t *) p2);
}

char *strcpy(char *destination, const char *source)
{
    while ((*destination++ = *source++))
        ;
    
    return destination;
}

char *strncpy(char *destination, const char *source, size_t num)
{
    while (num--)
    {
        *destination++ = *source++;
    }
    
    return destination;
}

size_t strlen(const char *str)
{
    size_t i = 0;
    while (*str++)
    {
        i++;
    }
    
    return i;
}

int strcmp(const char* s1, const char* s2)
{
    while ((*s1++ == *s2++) && (*s1 != '\n') && *s1)
        ;
    return (*(unsigned char *) --s1 < *(unsigned char *) --s2) ?
            -1 : (*(unsigned char *) s1 != *(unsigned char *) s2);
}

char *strdup(const char *str)
{
    int length = strlen(str);
    char *buf = malloc(length + 1);
    
    strcpy(buf, str);
    return buf;
}

char *strcat(char *dst, const char *src)
{
    char *tmp = dst;
    
    while (*tmp++);
    tmp--;
    while ((*tmp++ = *src++));
    *tmp = 0;
    return dst;
}

char *strncat(char *dst, char *src, size_t length)
{
    char *tmp = dst;
    
    while (*tmp++);
    tmp--;
    while (length-- && (*tmp++ = *src++));
    *tmp = 0;
    return dst;
}

const char *strchr(const char *str, char c)
{
    while (*str)
    {
        if (*str == c)
        {
            return str;
        }
        str++;
    }
    return NULL;
}
