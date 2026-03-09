/*
 * cot.c
 *
 * Compute the cotangent of x in radians as cos(x) / sin(x).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float cot(float x)
{
    return 1 / tan(x);
}
