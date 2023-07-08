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