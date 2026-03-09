/*
 * rewind.c
 *
 * Seek a stream back to the beginning and clear status flags.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

void rewind(FILE *fp)
{
    if (fp == NULL)
        return;
    fseek(fp, 0L, SEEK_SET);
    fp->eof = false;
}
