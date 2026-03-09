/*
 * fflush.c
 *
 * Flush buffered output for a stream or all open streams.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int fflush(FILE *fp)
{
    int i;

    errno = 0;

    if (fp == NULL) {
        for (i = 0; i < MAX_FILES; ++i) {
            if (_fds[i] != NULL && fsync(i) == -1)
                return -1;
        }
        return 0;
    }

    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    if (fp->fd >= 0 && fp->fd <= 2)
        return 0;

    return fsync(fp->fd);
}
