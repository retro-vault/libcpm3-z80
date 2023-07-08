/*
 * ceil.c
 *
 * Implementation of ceil (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
float ceil(float x)
{
    long r;
    r = x;
    if (r < 0)
        return r;
    else
        return (r + ((r < x) ? 1 : 0));
}