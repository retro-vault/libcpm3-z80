/*
 * strcpy.c
 *
 * strcpy function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

char *strcpy(char *dest, const char *src)
{
    size_t index = 0;

    while (src[index])
    {
        dest[index] = src[index];
        index++;
    }

    return (dest);
}