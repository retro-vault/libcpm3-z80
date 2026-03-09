/*
 * strtoumax.c
 *
 * Convert a character string to a uintmax_t value.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <inttypes.h>
#include <stdlib.h>

uintmax_t strtoumax(const char *nptr, char **endptr, int base) {
    return (uintmax_t)strtoul(nptr, endptr, base);
}
