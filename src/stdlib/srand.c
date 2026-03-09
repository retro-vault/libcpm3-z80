/*
 * srand.c
 *
 * Seed the pseudo-random number generator.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

void srand(unsigned int seed)
{
    _next = seed;
}
