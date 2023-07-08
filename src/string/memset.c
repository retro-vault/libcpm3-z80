/*
 * memset.c
 *
 * memset function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

void *memset(void *s, int c, size_t n) {
    unsigned char *s_ = s;
    const unsigned char c_ = (unsigned char)c;
    for (size_t i = 0; i < n; ++i) {
        s_[i] = c_;
    }
    return s;
}