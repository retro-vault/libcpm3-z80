/*
 * strrchr.c
 *
 * Locate the last occurrence of character c in a string.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

char *strrchr(const char *s, int c)
{
    const char *ptr = s;
    const char *retptr = NULL;
    char ch = (char)c;

    while (ptr[0] != '\0') {
        if (ptr[0] == ch) {
            retptr = ptr;
        }
        ptr ++;
    }
    if (ch == '\0')
        return (char *)ptr;
    return (char *)retptr;
}
