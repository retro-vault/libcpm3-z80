/*
 * ceil.c
 *
 * Implementation of ceil (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

static float _ftrunc(float x)
{
    union _float_long fl;
    int exp;
    fl.f = x;
    exp = (int)(((fl.l >> 23) & 0xff) - 127);
    if (exp < 0) return 0.0f;
    if (exp >= 23) return x;
    fl.l &= ~((1L << (23 - exp)) - 1L);
    return fl.f;
}

float ceil(float x)
{
    float r = _ftrunc(x);
    if (r < 0.0f) return r;
    if (r < x) r += 1.0f;
    return r;
}