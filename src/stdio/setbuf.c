/*
 * setbuf.c
 *
 * Stub for setbuf(); buffering is managed by the BDOS DMA buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

void setbuf(FILE *fp, char *buf) {
    (void)fp;
    (void)buf;
}
