/*
 * strncpy.c
 *
 * Copy up to num characters from src into the destination buffer,
 * padding with NUL bytes if src is shorter than num.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

char* strncpy(char* dst, const char* src, size_t num)
{
    if (dst == NULL) {
        return NULL;
    }
    char* ptr = dst;
    while (num && *src) {
        *dst++ = *src++;
        --num;
    }
    while (num) {
        *dst++ = '\0';
        --num;
    }
    return ptr;
}
