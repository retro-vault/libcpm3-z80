/*
 * toupper.c
 *
 * tolower function of ctype.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
int toupper(int c)
{
    if (('a' <= c) && (c <= 'z'))
        return 'A' + (c - 'a');
    else
        return c;
}