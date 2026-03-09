/*
 * vprintf.c
 *
 * Write formatted output to standard output using a va_list argument.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int vprintf(const char *fmt, va_list ap)
{
    return vfprintf(stdout, fmt, ap);
}
