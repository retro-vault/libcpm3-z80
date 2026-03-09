/*
 * toupper.c
 *
 * Convert lowercase letter to uppercase; leave others unchanged.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
int toupper(int c)
{
    if (('a' <= c) && (c <= 'z'))
        return 'A' + (c - 'a');
    else
        return c;
}
