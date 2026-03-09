/*
 * isgraph.c
 *
 * Test whether c has a visible graphical representation.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool isgraph(int c) {
    c &= 0xff;
    return c > 0x20 && c < 0x7f;
}
