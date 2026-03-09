/*
 * strcspn.c
 *
 * Return the length of the initial segment of s1 that contains
 * no characters from the reject set s2.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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
