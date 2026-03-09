/*
 * strcpy.c
 *
 * Copy a NUL-terminated string into the destination buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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
    dest[index] = '\0';

    return (dest);
}
