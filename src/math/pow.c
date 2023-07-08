/*
 * pow.c
 *
 * Implementation of pow (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float pow(float x, float y)
{
    if (y == 0.0)
        return 1.0;
    if (y == 1.0)
        return x;
    if (x <= 0.0)
        return 0.0;
    return exp(log(x) * y);
}