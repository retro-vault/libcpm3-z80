/*
 * islower.c
 *
 * Test whether c is a lowercase letter.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool islower(int c) {
    c &= 0xff;
    return c >= 'a' && c <= 'z';
}
