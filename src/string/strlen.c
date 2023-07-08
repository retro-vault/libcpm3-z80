/*
 * strlen.c
 *
 * strlen function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

size_t strlen(const char *str)
{
    size_t length = 0;

    while (*str++)
        length++;

    return (length);
}