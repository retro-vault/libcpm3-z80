/*
 * isprint.c
 *
 * Test whether c is a printable character, including space.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool isprint(int c) {
    c &= 0xff;
    return c >= 0x20 && c < 0x7f;
}
