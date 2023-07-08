/*
 * sprintf.c
 *
 * sprintf function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int sprintf(char *buf, char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(&buf, fmt, ap);
	va_end(ap);
	return r;
}