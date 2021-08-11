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
#ifndef __PRINT_H__
#define __PRINT_H__

#include <stdarg.h>
#include <util/leanmean.h>

/*
 * Utility functions. 
 */
extern void _outputchar(char **str, char c);
extern int _prints(char **out, const char *string, int width, int flags);
extern int _outputi(char **out, long long i, int base, int sign, int width, int flags, int letbase);
extern int _vsprintf(char **out, char *format, va_list ap);

#endif /* __PRINT_H__ */