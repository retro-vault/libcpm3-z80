/*
 * modf.c
 *
 * Implementation of modf (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float modf(float x, float *y)
{
    *y = (long)x;
    return (x - *y);
}
