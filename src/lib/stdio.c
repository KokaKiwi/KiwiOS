#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIGN    1
#define PLUS    2
#define LARGE   4

char *digits       = "0123456789abcdefghijklmnopqrstuvwxyz";
char *upper_digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static char *number(char *buf, int num, int base, int type)
{
    char sign = 0, tmp[66];
    char *dig = digits;
    int i;
    
    if (type & LARGE)
    {
        dig = upper_digits;
    }
    
    if (type & SIGN)
    {
        if (num < 0)
        {
            sign = '-';
            num = -num;
        }
        else if (type & PLUS)
        {
            sign = '+';
        }
    }
    
    i = 0;

    if (num)
    {
        while (num)
        {
            tmp[i++] = dig[((unsigned long) num) % (unsigned) base];
            num = ((unsigned long) num) / (unsigned) base;
        }
    }
    else
    {
        tmp[i++] = '0';
    }

    if(sign)
    {
        tmp[i++] = sign;
    }
    
    while (i--)
    {
        *buf++ = tmp[i];
    }
    
    return buf;
}

int vsprintf(char *buf, const char *fmt, va_list args)
{
    char *str, *s;
    int i, len;
    
    for (str = buf; *fmt; fmt++)
    {
        if (*fmt != '%')
        {
            *str++ = *fmt;
            continue;
        }
        
        switch (*++fmt)
        {
            case 'c':
                *str++ = (unsigned char) va_arg(args, int);
                break;
                
            case 'd':
            case 'f':
                str = number(str, va_arg(args, int), 10, SIGN);
                break;
                
            case 'u':
                str = number(str, va_arg(args, int), 10, 0);
                break;

            case 'P':
                *str++ = '0';
                *str++ = 'x';
            case 'X':
                str = number(str, (unsigned long) va_arg(args, void *), 16,
                        LARGE);
                break;

            case 'p':
                *str++ = '0';
                *str++ = 'x';
            case 'x':
                str = number(str, (unsigned long) va_arg(args, void *), 16, 0);
                break;
                
            case 's':
                s = va_arg(args, char *);
                if (!s)
                {
                    s = "<NULL>";
                }
                len = strlen(s);
                for (i = 0; i < len; i++)
                {
                    *str++ = *s++;
                }
                break;
                
            default:
                if (*fmt == '%')
                {
                    *str++ = '%';
                }
                break;
        }
    }
    
    return (str - buf);
}

inline void putchar(char c)
{
    console.putchar(c);
}

inline void puts(const char *str)
{
    console.puts(str);
}

inline void print(const char *str)
{
    puts(str);
}

inline void println(const char *str)
{
    print(str);
    putchar('\n');
}

void printf(const char *fmt, ...)
{
    static char buf[2048] = { 0 };
    int i, n;
    va_list args;

    va_start(args, fmt);
    n = vsprintf(buf, fmt, args);
    va_end(args);

    for(i = 0; i < n; i++)
    {
        putchar(buf[i]);
    }
}

int sprintf(char *buf, const char *fmt, ...)
{
    va_list args;
    int n;
    
    va_start(args, fmt);
    n = vsprintf(buf, fmt, args);
    va_end(args);
    
    return n;
}
