/*
 * memchr.c
 *
 * Locate the first byte equal to c within a memory block of n bytes.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *s_ = s;
    const unsigned char c_ = (unsigned char)c;

    for (size_t i = 0; i < n; ++i) {
        if (s_[i] == c_) {
            return (void *)(s_ + i);
        }
    }

    return NULL;
}
