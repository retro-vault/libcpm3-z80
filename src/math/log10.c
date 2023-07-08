/*
 * log10.c
 *
 * Implementation of log10 (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float log10(float x)
{
    return log(x) * 0.4342944819;
}