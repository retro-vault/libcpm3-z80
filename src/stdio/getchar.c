/*
 * getchar.c
 *
 * Read the next byte from standard input via the CP/M BDOS.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int getchar(void) {
    return (int)(unsigned char)bdos(C_READ, 0);
}
