/*
 * math.h
 *
 * Standard Library header.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 12.02.2022   tstih
 *
 */
#ifndef LIBCPM3_MATH_H
#define LIBCPM3_MATH_H

/* constants */
#define HUGE_VAL    3.402823466e+38

/* Round up to the next integer value. */
extern float ceil(float x);

/* Compute cosine. */
extern float cos(float x);

/* Compute cotangent. */
extern float cot(float x);

/* Compute exponential. */
extern float exp(float x);

/* Compute absolute value. */
extern float fabs(float x);

/* Split value into fraction and exponent. */
extern float frexp(float x, int *pw2);

/* Round down to the previous integer value. */
extern float floor(float x);

/* Multiply by 2 raised to pw2. */
extern float ldexp(float x, int pw2);

/* Compute natural logarithm. */
extern float log(float x);

/* Compute base-10 logarithm. */
extern float log10(float x);

/* Split value into integer and fractional parts. */
extern float modf(float x, float * y);

/* Raise x to the power y. */
extern float pow(float x, float y);

/* Compute sine. */
extern float sin(float f);

/* Compute square root. */
extern float sqrt(float x);

/* Compute tangent. */
extern float tan(float x);

#endif /* LIBCPM3_MATH_H */
