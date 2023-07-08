/*
 * fabs.c
 *
 * Implementation of fabs (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float fabs(float x)
{
    union _float_long fl;

    fl.f = x;
    fl.l &= 0x7fffffff;
    return fl.f;
}