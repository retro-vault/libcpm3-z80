/*
 * labs.c
 *
 * Return the absolute value of a long.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

long labs(long i) {
    return (i < 0) ? -i : i;
}
