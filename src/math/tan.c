/*
 * tan.c
 *
 * Implementation of tan (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float tan(float x)
{
    return sin(x) / cos(x);
}