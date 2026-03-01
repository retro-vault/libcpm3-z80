/*
 * atoi.c
 *
 * atoi function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

int atoi(const char *str)
{
    return (int)strtol((char *)str, NULL, 10);
}
