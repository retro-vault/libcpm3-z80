/*
 * math.h
 *
 * Internal header for math functions.
 *
 * From SDCC C math library.
 *
 * 05.07.2023   tstih
 *
 */
#ifndef ___MATH_H__
#define ___MATH_H__

#include <stdbool.h>
#include <errno.h>

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
#define B(w) (w + B0)

#define CL0 0.70710678118654752440
#define CL1 0.693359375 /*355.0/512.0*/
#define CL2 -2.121944400546905827679E-4

/* constants */
#define HUGE_VAL    3.402823466e+38

/* utility union */
union _float_long
{
    float f;
    long l;
};

/* functions */
extern float ceil(float x);
extern float cos(float x);
extern float cot(float x);
extern float exp(float x);
extern float fabs(float x);
extern float frexp(float x, int *pw2);
extern float floor(float x);
extern float ldexp(float x, int pw2);
extern float log(float x);
extern float log10(float x);
extern float modf(float x, float * y);
extern float pow(float x, float y);
extern float sin(float f);
extern float sqrt(float x);
extern float tan(float x);
extern float _sincosf(float x, bool iscos);

#endif /* ___MATH_H__ */