/*
 * feof.c
 *
 * feof function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int feof(FILE *fp)
{
    /* Make sure fp is valid file. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    } else 
        return (fp->eof) ? 1 : 0;
}