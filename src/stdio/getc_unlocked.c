/*
 * getc_unlocked.c
 *
 * Read the next byte from a stream without locking semantics.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int getc_unlocked(FILE *fp) {
    return fgetc(fp);
}
