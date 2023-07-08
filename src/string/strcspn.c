/*
 * strcspn.c
 *
 * strcspn function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

size_t strcspn(const char *s1, const char *s2) {
    size_t res = 0;
    while (*s1 != '\0') {
        if (strchr(s2, *s1) == NULL) {
            ++s1;
            ++res;
        } else {
            return res;
        }
    }
    return res;
}