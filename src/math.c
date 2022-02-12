/*
 * math.c
 *
 * Standard Library implementation.
 *
 * From SDCC C math library.
 *
 * 12.02.2022   tstih
 *
 */
#include <stdbool.h>
#include <errno.h>
#include <math.h>

#define PI 3.1415926536
#define TWO_PI 6.2831853071
#define HALF_PI 1.5707963268
#define QUART_PI 0.7853981634
#define iPI 0.3183098862
#define iTWO_PI 0.1591549431
#define TWO_O_PI 0.6366197724

/* EPS=B**(-t/2), where B is the radix of the floating-point representation
   and there are t base-B digits in the significand.  Therefore, for floats
   EPS=2**(-12).  Also define EPS2=EPS*EPS. */
#define EPS 244.14062E-6
#define EPS2 59.6046E-9

#define r1 -0.1666665668E+0
#define r2 0.8333025139E-2
#define r3 -0.1980741872E-3
#define r4 0.2601903036E-5

#define C1 3.140625
#define C2 9.676535897E-4

/* a reasonable value for YMAX is the int part of PI*B**(t/2)=3.1416*2**(12)*/
#define YMAX 12867.0

/* exp definitions */
#define BIGX 88.72283911 /* ln(HUGE_VALF) */
#define EXPEPS 1.0E-7    /* exp(1.0E-7)=0.0000001 */
#define K1 1.4426950409  /* 1/ln(2) */
#define P0 0.2499999995E+0
#define P1 0.4160288626E-2
#define Q0 0.5000000000E+0
#define Q1 0.4998717877E-1
#define P(z) ((P1 * z) + P0)
#define Q(z) ((Q1 * z) + Q0)

#define CE1 0.693359375
#define CE2 -2.1219444005469058277e-4

/* log definitions */
/*Constants for 24 bits or less (8 decimal digits)*/
#define A0 -0.5527074855E+0
#define B0 -0.6632718214E+1
#define A(w) (A0)
#define B(w) (w+B0)

#define CL0  0.70710678118654752440
#define CL1  0.693359375 /*355.0/512.0*/
#define CL2 -2.121944400546905827679E-4

/* utility union */
union _float_long
{
    float f;
    long l;
};

static float _sincosf(float x, bool iscos)
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

float fabs(float x)
{
    union _float_long fl;

    fl.f = x;
    fl.l &= 0x7fffffff;
    return fl.f;
}

float frexp(float x, int *pw2)
{
    union _float_long fl;
    long int i;

    fl.f = x;
    /* Find the exponent (power of 2) */
    i = (fl.l >> 23) & 0x000000ff;
    i -= 0x7e;
    *pw2 = i;
    fl.l &= 0x807fffff; /* strip all exponent bits */
    fl.l |= 0x3f000000; /* mantissa between 0.5 and 1 */
    return (fl.f);
}

float floor(float x)
{
    long r;
    r = x;
    if (r <= 0)
        return (r + ((r > x) ? -1 : 0));
    else
        return r;
}

float ceil(float x)
{
    long r;
    r=x;
    if (r<0)
        return r;
    else
        return (r+((r<x)?1:0));
}

float sin(float x)
{
    if (x == 0.0f)
        return 0.0f;
    return _sincosf(x, 0);
}

float cos(float x)
{
    if (x == 0.0f)
        return 1.0f;
    return _sincosf(x, 1);
}

float ldexp(float x, int pw2)
{
    union _float_long fl;
    long e;

    fl.f = x;

    e=(fl.l >> 23) & 0x000000ff;
    e+=pw2;
    fl.l= ((e & 0xff) << 23) | (fl.l & 0x807fffff);

    return(fl.f);
}

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
            errno = ERANGE;
            return HUGE_VAL;
        }
        else
        {
            return 0.0;
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

float log(float x)
{
    float Rz;
    float f, z, w, znum, zden, xn;
    int n;

    if (x<=0.0f)
    {
        errno=EDOM;
        return 0.0f;
    }
    f=frexp(x, &n);
    znum=f-0.5;
    if (f>CL0)
    {
        znum-=0.5;
        zden=(f*0.5)+0.5;
    }
    else
    {
        n--;
        zden=znum*0.5+0.5;
    }
    z=znum/zden;
    w=z*z;

    Rz=z+z*(w*A(w)/B(w));
    xn=n;
    return ((xn*CL2+Rz)+xn*CL1);
}

float log10(float x)
{
    return log(x)*0.4342944819;
}

float sqrt(float x) 
{
    float f, y;
    int n;

    if (x==0.0f) return x;
    else if (x==1.0f) return 1.0f;
    else if (x<0.0f)
    {
        errno=EDOM;
        return 0.0f;
    }
    f=frexp(x, &n);
    y=0.41731+0.59016*f; /*Educated guess*/
    /*For a 24 bit mantisa (float), two iterations are sufficient*/
    y+=f/y;
    y=ldexp(y, -2) + f/y; /*Faster version of 0.25 * y + f/y*/

    if (n&1)
    {
        y*=0.7071067812;
        ++n;
    }
    return ldexp(y, n/2);
}

float pow(float x, float y)
{
    if(y == 0.0) return 1.0;
    if(y == 1.0) return x;
    if(x <= 0.0) return 0.0;
    return exp(log(x) * y);
}

float modf(float x, float * y)
{
    *y=(long)x;
    return (x-*y);
}

float tan(float x) {
    return sin(x)/cos(x);
}

float cot(float x) {
    return 1/tan(x);
}