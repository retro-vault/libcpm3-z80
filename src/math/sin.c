/*
 * sin.c
 *
 * Compute the sine of x, where x is in radians.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float sin(float x)
{
    if (x == 0.0f)
        return 0.0f;
    return _sincosf(x, 0);
}
