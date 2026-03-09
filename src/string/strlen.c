/*
 * strlen.c
 *
 * Return the length of a NUL-terminated string.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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
