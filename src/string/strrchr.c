/*
 * strrchr.c
 *
 * strrchr function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
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
