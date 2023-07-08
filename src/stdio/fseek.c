/*
 * fseek.c
 *
 * fseek function (see:stdio.h)
 *
 * 05.07.2023   tstih
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
        return -1;
    }

    /* Try... */
    if (lseek(fp->fd, offset, whence) == -1) return -1;

    /* We're good. */
    fp->eof=false;
    return 0;
}