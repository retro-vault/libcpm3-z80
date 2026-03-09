/*
 * pow.c
 *
 * Raise x to the power y.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float pow(float x, float y)
{
    if (y == 0.0)
        return 1.0;
    if (y == 1.0)
        return x;
    if (x <= 0.0)
        return 0.0;
    return exp(log(x) * y);
}
