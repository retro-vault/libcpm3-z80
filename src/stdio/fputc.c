/*
 * fputc.c
 *
 * Write one byte to a stream.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int fputc(int c, FILE *fp)
{
    unsigned char ch;

    errno = 0;

    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    if (fp->fd == 1 || fp->fd == 2)
        return putchar(c);

    ch = (unsigned char)c;
    if (write(fp->fd, &ch, 1) != 1)
        return -1;

    fp->eof = false;
    return (int)ch;
}
