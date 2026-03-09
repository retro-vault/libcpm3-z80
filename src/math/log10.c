/*
 * log10.c
 *
 * Compute the base-10 logarithm of x.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float log10(float x)
{
    return log(x) * 0.4342944819;
}
