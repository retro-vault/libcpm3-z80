/*
 * ftell.c
 *
 * Return the current file offset for a stream.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

long ftell(FILE *fp) {
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    } else {
        _fd_t* pfd = _fd_get(fp->fd);
        return pfd->fpos;
    }
}
