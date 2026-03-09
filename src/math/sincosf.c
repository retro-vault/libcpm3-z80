/*
 * sincosf.c
 *
 * Compute sine or cosine using a shared single-precision core.
 * Internal helper called by sin() and cos().
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <math/_math.h>

static float _ftrunc(float x)
{
    union _float_long fl;
    int exp;
    fl.f = x;
    exp = (int)(((fl.l >> 23) & 0xff) - 127);
    if (exp < 0) return 0.0f;
    if (exp >= 23) return x;
    fl.l &= ~((1L << (23 - exp)) - 1L);
    return fl.f;
}

float _sincosf(float x, bool iscos)
{
    float y, f, r, g, XN, N_f;
    bool sign;

    if (iscos)
    {
        y = fabs(x) + HALF_PI;
        sign = 0;
    }
    else
    {
        if (x < 0.0)
        {
            y = -x;
            sign = 1;
        }
        else
        {
            y = x;
            sign = 0;
        }
    }

    if (y > YMAX)
    {
        errno = ERANGE;
        return 0.0;
    }

    /*Round y/PI to the nearest integer*/
    N_f = _ftrunc(y * iPI + 0.5f); /*y is positive*/

    /*If N is odd change sign*/
    if (N_f - _ftrunc(N_f * 0.5f) * 2.0f >= 0.5f)
        sign = !sign;

    XN = N_f;
    /*Cosine required? (is done here to keep accuracy)*/
    if (iscos)
        XN -= 0.5f;

    y = fabs(x);
    r = _ftrunc(y);
    g = y - r;
    f = ((r - XN * C1) + g) - XN * C2;

    g = f * f;
    if (g > EPS2) // Used to be if(fabsf(f)>EPS)
    {
        r = (((r4 * g + r3) * g + r2) * g + r1) * g;
        f += f * r;
    }
    return (sign ? -f : f);
}
