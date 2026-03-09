/*
 * isalnum.c
 *
 * Test whether c is an alphanumeric character.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <ctype.h>

bool isalnum(int c) {
    return isalpha(c) || isdigit(c);
}
