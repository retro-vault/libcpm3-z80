/*
 * stdio.c
 *
 * Standard Library implementation.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 28.04.2021   tstih
 *
 */
#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <util/bdos.h>
#include <util/print.h>

int putchar(int c) {
    bdos_call_t cwrite = { C_WRITE, { (uint16_t)c } };
    _bdos(&cwrite);
    return c;
}

int puts(const char *s)
{
   int i = 0;
   while(s[i]) putchar(s[i++]);
   return 1;
}

int printf(char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(NULL, fmt, ap);
	va_end(ap);
	return r;
}

int sprintf(char *buf, char *fmt, ...)
{
	va_list ap;
	int r;
	va_start(ap, fmt);
	r = _vsprintf(&buf, fmt, ap);
	va_end(ap);
	return r;
}