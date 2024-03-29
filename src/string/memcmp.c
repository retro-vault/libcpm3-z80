/*
 * memcmp.c
 *
 * memcmp function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <string.h>

int memcmp(const void *lhs, const void *rhs, size_t count) {
    const unsigned char *lhs_ = lhs;
    const unsigned char *rhs_ = rhs;

    for (size_t i = 0; i < count; ++i) {
        const int res = lhs_[i] - rhs_[i];
        if (res != 0) {
            return res;
        }
    }

    return 0;
}