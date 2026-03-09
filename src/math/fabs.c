/*
 * fabs.c
 *
 * Return the absolute value of the floating-point number x.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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
