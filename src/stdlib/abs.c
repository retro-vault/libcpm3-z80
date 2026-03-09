/*
 * abs.c
 *
 * Return the absolute value of an int.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

int abs(int i)
{
    return i < 0 ? -i : i;
}
