/*
 * sqrt.c
 *
 * Implementation of sqrt (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float sqrt(float x)
{
    float f, y;
    int n;

    if (x == 0.0f)
        return x;
    else if (x == 1.0f)
        return 1.0f;
    else if (x < 0.0f)
    {
        errno = EDOM;
        return 0.0f;
    }
    f = frexp(x, &n);
    y = 0.41731 + 0.59016 * f; /*Educated guess*/
    /*For a 24 bit mantisa (float), two iterations are sufficient*/
    y += f / y;
    y = ldexp(y, -2) + f / y; /*Faster version of 0.25 * y + f/y*/

    if (n & 1)
    {
        y *= 0.7071067812;
        ++n;
    }
    return ldexp(y, n / 2);
}