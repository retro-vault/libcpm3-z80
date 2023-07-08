/*
 * floor.c
 *
 * Implementation of floor (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
float floor(float x)
{
    long r;
    r = x;
    if (r <= 0)
        return (r + ((r > x) ? -1 : 0));
    else
        return r;
}