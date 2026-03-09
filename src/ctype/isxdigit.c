/*
 * isxdigit.c
 *
 * Test whether c is a hexadecimal digit.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool isxdigit(int c) {
    c &= 0xff;
    return isdigit(c) || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f');
}
