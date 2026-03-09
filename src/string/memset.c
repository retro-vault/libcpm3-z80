/*
 * memset.c
 *
 * Set the first n bytes of memory block s to the value c.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
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
