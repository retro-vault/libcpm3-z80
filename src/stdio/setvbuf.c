/*
 * setvbuf.c
 *
 * Stub for setvbuf(); buffering is managed by the BDOS DMA buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int setvbuf(FILE *fp, char *buf, int mode, size_t size) {
    (void)fp;
    (void)buf;
    (void)mode;
    (void)size;
    return 0;
}
