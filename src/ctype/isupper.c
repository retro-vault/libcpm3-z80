/*
 * isupper.c
 *
 * Test whether c is an uppercase letter.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool isupper(int c) {
    c &= 0xff;
    return c >= 'A' && c <= 'Z';
}
