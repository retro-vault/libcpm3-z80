/*
 * vsprintf.c
 *
 * Format output into a memory buffer using a va_list argument.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int vsprintf(char *buf, const char *fmt, va_list ap)
{
    return _vsprintf(&buf, fmt, ap);
}
