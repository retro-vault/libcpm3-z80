/*
 * getc.c
 *
 * Read the next byte from a stream; thin wrapper around fgetc().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int getc(FILE *fp) {
    return fgetc(fp);
}
