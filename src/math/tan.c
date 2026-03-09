/*
 * tan.c
 *
 * Compute the tangent of x, where x is in radians.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float tan(float x)
{
    return sin(x) / cos(x);
}
