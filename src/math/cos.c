/*
 * cos.c
 *
 * Implementation of cos (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float cos(float x)
{
    if (x == 0.0f)
        return 1.0f;
    return _sincosf(x, 1);
}