/*
 * exp.c
 *
 * Compute e raised to the power x.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

float exp(float x)
{
    int n;
    float xn, g, r, z, y;
    bool sign;

    if (x >= 0.0)
    {
        y = x;
        sign = 0;
    }
    else
    {
        y = -x;
        sign = 1;
    }

    if (y < EXPEPS)
        return 1.0;

    if (y > BIGX)
    {
        if (sign)
        {
            return 0.0;
        }
        else
        {
            errno = ERANGE;
            return HUGE_VAL;
        }
    }

    z = y * K1;
    n = z;

    if (n < 0)
        --n;
    if (z - n >= 0.5)
        ++n;
    xn = n;
    g = ((y - xn * CE1)) - xn * CE2;
    z = g * g;
    r = P(z) * g;
    r = 0.5 + (r / (Q(z) - r));

    n++;
    z = ldexp(r, n);
    if (sign)
        return 1.0 / z;
    else
        return z;
}
