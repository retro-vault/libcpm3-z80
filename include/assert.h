/*
 * assert.h
 *
 * Standard C diagnostics.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#ifndef LIBCPM3_ASSERT_H
#define LIBCPM3_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr)                                                     \
    do {                                                                 \
        if (!(expr)) {                                                   \
            printf("assertion failed: %s (%s:%d)\n", #expr,              \
                   __FILE__, __LINE__);                                  \
            exit(1);                                                     \
        }                                                                \
    } while (0)
#endif

#endif /* LIBCPM3_ASSERT_H */
