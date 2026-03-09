/*
 * iscntrl.c
 *
 * Test whether c is an ASCII control character.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool iscntrl(int c) {
    c &= 0xff;
    return c < 0x20 || c == 0x7f;
}
