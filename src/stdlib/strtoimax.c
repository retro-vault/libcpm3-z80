/*
 * strtoimax.c
 *
 * Convert a character string to an intmax_t value.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <inttypes.h>
#include <stdlib.h>

intmax_t strtoimax(const char *nptr, char **endptr, int base) {
    return (intmax_t)strtol((char *)nptr, endptr, base);
}
