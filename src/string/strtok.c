/*
 * strtok.c
 *
 * Tokenize a string by a delimiter set using internal static state.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

char *strtok(char *s, const char *delim) {
    static char *last;

    if (s == NULL) {
        s = last;
    }
    int ch;
    do {
        ch = *s++;
        if (ch == '\0') {
            return NULL;
        }
    } while (strchr(delim, ch));
    --s;
    last = s + strcspn(s, delim);
    if (*last != '\0') {
        *last++ = '\0';
    }
    return s;
}
