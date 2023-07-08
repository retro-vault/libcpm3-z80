/*
 * tolower.c
 *
 * tolower function of ctype.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
int tolower(int c)
{
    if (('A' <= c) && (c <= 'Z'))
        return 'a' + (c - 'A');
    else
        return c;
}