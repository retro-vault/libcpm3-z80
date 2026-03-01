/*
 * check_fp.c
 *
 * Check if fp is valid.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

bool _check_fp(FILE *fp) {
    return fp!=NULL && _fd_get(fp->fd)!=NULL;
}