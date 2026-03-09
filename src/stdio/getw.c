/*
 * getw.c
 *
 * Read one machine-word (int) value from a stream in little-endian order.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int getw(FILE *fp)
{
    unsigned char lo, hi;
    int c;

    c = fgetc(fp);
    if (c == EOF || c < 0)
        return EOF;
    lo = (unsigned char)c;

    c = fgetc(fp);
    if (c == EOF || c < 0) {
        fp->err = true;
        return EOF;
    }
    hi = (unsigned char)c;

    return (int)(lo | ((unsigned int)hi << 8));
}
