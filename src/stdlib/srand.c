/*
 * srand.c
 *
 * srand function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void srand(unsigned int seed)
{
    _next = seed;
}