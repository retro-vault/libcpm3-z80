/*
 * ungetc.c
 *
 * Push one byte back onto a stream so it is returned by the next read.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int ungetc(int c, FILE *fp)
{
    if (!_check_fp(fp)) {
        errno = EBADF;
        return EOF;
    }
    if (c == EOF || fp->ungot != -1)
        return EOF;
    fp->ungot = c & 0xff;
    fp->eof = false;
    return fp->ungot;
}
