/*
 * cot.c
 *
 * Implementation of cot (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float cot(float x)
{
    return 1 / tan(x);
}