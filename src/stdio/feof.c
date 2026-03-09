/*
 * feof.c
 *
 * Test whether the stream end-of-file indicator is set.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int feof(FILE *fp)
{
    /* Make sure fp is valid file. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }
    return (fp->eof) ? 1 : 0;
}
