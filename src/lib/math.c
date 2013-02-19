#include <math.h>

double pow(double base, double exponent)
{
    double result = 1;

    while(exponent--)
    {
        result *= base;
    }

    return result;
}