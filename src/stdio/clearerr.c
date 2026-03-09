/*
 * clearerr.c
 *
 * Clear the end-of-file and error indicators on a stream.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

void clearerr(FILE *fp) {
    if (fp == NULL)
        return;
    fp->eof = false;
    fp->err = false;
    fp->ungot = -1;
}
