/*
 * gets.c
 *
 * Read a line from standard input into a caller-supplied buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

char *gets(char *str) {
    char *p = str;
    int c;

    if (str == NULL)
        return NULL;

    for (;;) {
        c = getchar();
        if (c == EOF) {
            if (p == str)
                return NULL;
            break;
        }
        if (c == '\r' || c == '\n')
            break;
        *p++ = (char)c;
    }

    *p = '\0';
    return str;
}
