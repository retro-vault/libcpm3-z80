/*
 * isspace.c
 *
 * isspace function of ctype.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdbool.h>

bool isspace(int c)
{
    return c == ' ' || c == '\t'; // || whatever other char you consider space
}