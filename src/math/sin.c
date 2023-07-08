/*
 * sin.c
 *
 * Implementation of sin (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float sin(float x)
{
    if (x == 0.0f)
        return 0.0f;
    return _sincosf(x, 0);
}