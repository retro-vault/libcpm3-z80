/*
 * isdigit.c
 *
 * Test whether c is a decimal digit.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdbool.h>

bool isdigit(int c)
{
    return (c >= '0' && c <= '9');
}
