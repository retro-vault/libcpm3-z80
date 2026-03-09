/*
 * memcpy.c
 *
 * Copy n bytes from src to dest; overlap is not handled.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

static void *_memcpy_impl(void *s1, const void *s2, size_t n) {
    unsigned char *s1_ = s1;
    const unsigned char *s2_ = s2;
    for (size_t i = 0; i < n; ++i) {
        s1_[i] = s2_[i];
    }

    return s1;
}

void *__memcpy(void *dest, const void *src, size_t n) {
    return _memcpy_impl(dest, src, n);
}

void *memcpy(void *dest, const void *src, size_t n) {
    return _memcpy_impl(dest, src, n);
}
