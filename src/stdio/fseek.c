/*
 * fseek.c
 *
 * Reposition a stream to a new file offset.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int fseek(FILE *fp, long offset, int whence)
{
    /* Reset errno. */
    errno = 0;

    /* Must be fvalid file pointer. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        if (fp)
            fp->err = true;
        return -1;
    }

    /* Try... */
    if (lseek(fp->fd, offset, whence) == -1) {
        fp->err = true;
        return -1;
    }

    /* We're good. */
    fp->eof=false;
    fp->err=false;
    fp->ungot=-1;
    return 0;
}
