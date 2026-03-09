/*
 * putc.c
 *
 * Write one byte to a stream; thin wrapper around fputc().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int putc(int c, FILE *fp) {
    return fputc(c, fp);
}
