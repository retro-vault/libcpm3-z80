/*
 * strncpy.c
 *
 * strncpy function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

char* strncpy(char* dst, const char* src, size_t num)
{
    if (dst == NULL) {
        return NULL;
    }
    char* ptr = dst;
    while (*src && num--)
    {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = '\0';
    return ptr;
}