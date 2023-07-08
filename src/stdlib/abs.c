/*
 * abs.c
 *
 * abs function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

int abs(int i)
{
    return i < 0 ? -i : i;
}