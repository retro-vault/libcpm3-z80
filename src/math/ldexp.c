/*
 * ldexp.c
 *
 * Scale x by 2 raised to the power pw2.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float ldexp(float x, int pw2)
{
    union _float_long fl;
    long e;

    fl.f = x;

    e = (fl.l >> 23) & 0x000000ff;
    e += pw2;
    fl.l = ((e & 0xff) << 23) | (fl.l & 0x807fffff);

    return (fl.f);
}
