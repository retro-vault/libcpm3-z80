/*
 * ftell.c
 *
 * ftell function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

long ftell(FILE *fp) {
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    } else {
        fd_t* pfd = _fd_get(fp->fd);
        return pfd->fpos;
    }
}