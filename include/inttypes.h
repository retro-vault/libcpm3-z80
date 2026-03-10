/*
 * inttypes.h
 *
 * Standard integer format helpers.
 *
 * This header only provides the printf conversion macros supported by
 * libcpm3-z80's formatter: d, i, o, u, x, X with optional h, hh, and l.
 * scanf SCN* macros are not provided.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#ifndef LIBCPM3_INTTYPES_H
#define LIBCPM3_INTTYPES_H

#include <stdint.h>

typedef int32_t  intmax_t;
typedef uint32_t uintmax_t;

#define PRId8   "d"
#define PRIi8   "i"
#define PRIo8   "o"
#define PRIu8   "u"
#define PRIx8   "x"
#define PRIX8   "X"

#define PRId16  "d"
#define PRIi16  "i"
#define PRIo16  "o"
#define PRIu16  "u"
#define PRIx16  "x"
#define PRIX16  "X"

#define PRId32  "ld"
#define PRIi32  "li"
#define PRIo32  "lo"
#define PRIu32  "lu"
#define PRIx32  "lx"
#define PRIX32  "lX"

#define PRIdMAX PRId32
#define PRIiMAX PRIi32
#define PRIoMAX PRIo32
#define PRIuMAX PRIu32
#define PRIxMAX PRIx32
#define PRIXMAX PRIX32

/* Convert string to intmax_t using base. */
extern intmax_t strtoimax(const char *nptr, char **endptr, int base);

/* Convert string to uintmax_t using base. */
extern uintmax_t strtoumax(const char *nptr, char **endptr, int base);

#endif /* LIBCPM3_INTTYPES_H */
