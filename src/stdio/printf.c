/*
 * printf.c
 *
 * printf function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int printf(char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(NULL, fmt, ap);
	va_end(ap);
	return r;
}