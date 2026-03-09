/*
 * tolower.c
 *
 * Convert uppercase letter to lowercase; leave others unchanged.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
int tolower(int c)
{
    if (('A' <= c) && (c <= 'Z'))
        return 'a' + (c - 'A');
    else
        return c;
}
