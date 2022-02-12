/*
 * math.h
 *
 * Standard Library header.
 *
 * From SDCC C math library.
 *
 * 12.02.2022   tstih
 *
 */
#ifndef __MATH_H__
#define __MATH_H__

/* constants */
#define HUGE_VAL    3.402823466e+38

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

#endif /* __MATH_H__ */