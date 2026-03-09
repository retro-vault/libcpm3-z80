/*
 * tmpnam.c
 *
 * Generate a unique CP/M-compatible temporary filename.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

static unsigned int _tmpnam_counter = 0;

char *tmpnam(char *s)
{
    static char name[16];
    char *dst = s ? s : name;

    sprintf(dst, "T%07u.TMP", _tmpnam_counter++);
    return dst;
}
