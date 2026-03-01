/*
 * print.h
 *
 * Support functions for printf.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.08.2021   tstih
 *
 */
#ifndef LIBCPM3_UTIL_PRINT_H
#define LIBCPM3_UTIL_PRINT_H

#include <stdarg.h>

/*
 * Utility functions. 
 */
extern void _outputchar(char **str, char c);
extern int _prints(char **out, const char *string, int width, int flags);
extern int _outputi(char **out, long i, int base, int sign, int width, int flags, int letbase);
extern int _vsprintf(char **out, char *format, va_list ap);

#endif /* LIBCPM3_UTIL_PRINT_H */