/*
 * nltype.h
 *
 * Newline translation mode shared by stdio and stdlib.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 17.02.2026   tstih
 *
 */
#ifndef LIBCPM3_UTIL_NLTYPE_H
#define LIBCPM3_UTIL_NLTYPE_H

/* How console functions interpret \n */
#define NL_LF       0   /* output \n as-is */
#define NL_CRLF     1   /* output \n as \r\n */
#define NL_LFCR     2   /* output \n as \n\r */

extern char nltype;

#endif /* LIBCPM3_UTIL_NLTYPE_H */
