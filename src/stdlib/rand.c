/*
 * rand.c
 *
 * Return a pseudo-random integer using a linear congruential generator.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

unsigned long _next = 1;

int rand(void) /* RAND_MAX assumed to be 32767 */
{
    _next = _next * 1103515245 + 12345;
    return (unsigned int)(_next / 65536) % 32768;
}
