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

#include <util/print.h>

#include <sys/bdos.h>

int putchar(int c) {
    /* Extend newline if DOS. */
    if (c=='\n') {
        switch(nltype) {
            case NL_LF:
                bdos(C_WRITE,'\n');
                break;
            case NL_CRLF:
                bdos(C_WRITE,'\r');
                bdos(C_WRITE,'\n');
                break;
            case NL_LFCR:
                bdos(C_WRITE,'\n');
                bdos(C_WRITE,'\r');
                break;
        }
    } else bdos(C_WRITE,c);
    return c;
}

int puts(const char *s)
{
   int i = 0;
   while(s[i]) { putchar(s[i]); i++; }
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