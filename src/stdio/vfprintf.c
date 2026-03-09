/*
 * vfprintf.c
 *
 * Write formatted output to a stream using a va_list argument.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int vfprintf(FILE *fp, const char *fmt, va_list ap)
{
    char buf[256];
    char *out = buf;
    int n;
    int i;

    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    n = _vsprintf(&out, fmt, ap);
    *out = '\0';

    for (i = 0; i < n; ++i) {
        if (fputc((unsigned char)buf[i], fp) < 0) {
            fp->err = true;
            return -1;
        }
    }

    return n;
}
