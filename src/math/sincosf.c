/*
 * _sincosf.c
 *
 * Implementation of _sincosf (see:math.h)
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#include <math/_math.h>

float _sincosf(float x, bool iscos)
{
    float y, f, r, g, XN;
    int N;
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
    N = ((y * iPI) + 0.5); /*y is positive*/

    /*If N is odd change sign*/
    if (N & 1)
        sign = !sign;

    XN = N;
    /*Cosine required? (is done here to keep accuracy)*/
    if (iscos)
        XN -= 0.5;

    y = fabs(x);
    r = (int)y;
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