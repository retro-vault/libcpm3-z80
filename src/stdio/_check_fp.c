/*
 * _check_fp.c
 *
 * Validate a FILE pointer before stdio operations use it.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

bool _check_fp(FILE *fp) {
    if (fp == NULL)
        return false;
    if (fp->fd >= 0 && fp->fd <= 2)
        return true;
    return _fd_get(fp->fd)!=NULL;
}
