/*
 * atol.c
 *
 * Convert a character string to a long.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>

long atol(const char *str) {
    return strtol((char *)str, (char **)0, 10);
}
