/*
 * isdigit.c
 *
 * isdigit function of ctype.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdbool.h>

bool isdigit(int c)
{
    return (c >= '0' && c <= '9');
}