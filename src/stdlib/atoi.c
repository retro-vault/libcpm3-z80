/*
 * atoi.c
 *
 * Convert a character string to an int.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

int atoi(const char *str)
{
    return (int)strtol((char *)str, NULL, 10);
}
