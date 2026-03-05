/*
 * ispunct.c
 *
 * ispunct function of ctype.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdbool.h>

bool ispunct(int c)
{
    /* All printable ASCII non-space, non-alphanumeric characters. */
    return (c >= 0x21 && c <= 0x2F) ||   /* !"#$%&'()*+,-./ */
           (c >= 0x3A && c <= 0x40) ||   /* :;<=>?@          */
           (c >= 0x5B && c <= 0x60) ||   /* [\]^_`           */
           (c >= 0x7B && c <= 0x7E);     /* {|}~             */
}