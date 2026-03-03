/*
 * tmath.c
 *
 * Tests for math.h floating-point functions.
 *
 * The library's printf does not support %f, so float comparisons use
 * the EXPECT_EQ_FLOAT(expected, actual, tolerance) macro from
 * test_macros.h. On failure only the expression names are printed.
 *
 * Constants:
 *   PI   ~= 3.14159265
 *   PI/2 ~= 1.57079633
 *   e    ~= 2.71828183
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

#define PI      3.14159265f
#define PI_2    1.57079633f
#define E_VAL   2.71828183f
#define TOL     0.0001f     /* tolerance for single-precision results */

/* ---- fabs -------------------------------------------------------------- */

TEST(fabs_values) {
    EXPECT_EQ_FLOAT(3.5f,  fabs(3.5f),  TOL);
    EXPECT_EQ_FLOAT(3.5f,  fabs(-3.5f), TOL);
    EXPECT_EQ_FLOAT(0.0f,  fabs(0.0f),  TOL);
    EXPECT_EQ_FLOAT(1.0f,  fabs(-1.0f), TOL);
}

/* ---- ceil / floor ------------------------------------------------------ */

TEST(ceil_values) {
    EXPECT_EQ_FLOAT(2.0f,  ceil(1.1f),  TOL);
    EXPECT_EQ_FLOAT(2.0f,  ceil(1.9f),  TOL);
    EXPECT_EQ_FLOAT(2.0f,  ceil(2.0f),  TOL);
    EXPECT_EQ_FLOAT(-1.0f, ceil(-1.9f), TOL);
    EXPECT_EQ_FLOAT(0.0f,  ceil(-0.5f), TOL);
}

TEST(floor_values) {
    EXPECT_EQ_FLOAT(1.0f,  floor(1.1f),  TOL);
    EXPECT_EQ_FLOAT(1.0f,  floor(1.9f),  TOL);
    EXPECT_EQ_FLOAT(2.0f,  floor(2.0f),  TOL);
    EXPECT_EQ_FLOAT(-2.0f, floor(-1.1f), TOL);
    EXPECT_EQ_FLOAT(-1.0f, floor(-0.5f), TOL);
}

/* ---- sqrt -------------------------------------------------------------- */

TEST(sqrt_perfect_squares) {
    EXPECT_EQ_FLOAT(0.0f, sqrt(0.0f), TOL);
    EXPECT_EQ_FLOAT(1.0f, sqrt(1.0f), TOL);
    EXPECT_EQ_FLOAT(2.0f, sqrt(4.0f), TOL);
    EXPECT_EQ_FLOAT(3.0f, sqrt(9.0f), TOL);
    EXPECT_EQ_FLOAT(4.0f, sqrt(16.0f), TOL);
    EXPECT_EQ_FLOAT(5.0f, sqrt(25.0f), TOL);
    EXPECT_EQ_FLOAT(10.0f, sqrt(100.0f), TOL);
}

TEST(sqrt_non_integer) {
    /* sqrt(2) ~ 1.41421 */
    EXPECT_EQ_FLOAT(1.41421f, sqrt(2.0f), TOL);
}

/* ---- sin / cos --------------------------------------------------------- */

TEST(sin_known_values) {
    EXPECT_EQ_FLOAT(0.0f,  sin(0.0f),  TOL);
    EXPECT_EQ_FLOAT(1.0f,  sin(PI_2),  TOL);  /* sin(pi/2) = 1 */
    EXPECT_EQ_FLOAT(0.0f,  sin(PI),    0.001f); /* sin(pi) ~ 0 */
}

TEST(cos_known_values) {
    EXPECT_EQ_FLOAT(1.0f,  cos(0.0f),  TOL);
    EXPECT_EQ_FLOAT(0.0f,  cos(PI_2),  0.001f); /* cos(pi/2) ~ 0 */
    EXPECT_EQ_FLOAT(-1.0f, cos(PI),    TOL);    /* cos(pi) = -1 */
}

TEST(sin_cos_identity) {
    /* sin^2 + cos^2 = 1 for any angle */
    float s = sin(1.0f);
    float c = cos(1.0f);
    EXPECT_EQ_FLOAT(1.0f, s*s + c*c, TOL);
}

/* ---- tan --------------------------------------------------------------- */

TEST(tan_known_values) {
    EXPECT_EQ_FLOAT(0.0f,     tan(0.0f), TOL);
    EXPECT_EQ_FLOAT(1.0f,     tan(PI/4), TOL); /* tan(45 deg) = 1 */
}

TEST(cot_known_values) {
    EXPECT_EQ_FLOAT(1.0f, cot(PI/4), TOL); /* cot(45 deg) = 1 */
    EXPECT_EQ_FLOAT(0.0f, cot(PI_2), 0.001f);
}

/* ---- exp --------------------------------------------------------------- */

TEST(exp_known_values) {
    EXPECT_EQ_FLOAT(1.0f,    exp(0.0f), TOL);
    EXPECT_EQ_FLOAT(E_VAL,   exp(1.0f), 0.001f);
    EXPECT_EQ_FLOAT(1.0f/E_VAL, exp(-1.0f), 0.001f);
}

/* ---- log --------------------------------------------------------------- */

TEST(log_known_values) {
    EXPECT_EQ_FLOAT(0.0f,  log(1.0f),   TOL);
    EXPECT_EQ_FLOAT(1.0f,  log(E_VAL),  0.001f);  /* ln(e) = 1 */
}

TEST(log_exp_inverse) {
    /* exp(log(x)) == x for x > 0 */
    EXPECT_EQ_FLOAT(2.0f, exp(log(2.0f)), TOL);
    EXPECT_EQ_FLOAT(5.0f, exp(log(5.0f)), TOL);
}

TEST(sin_range_error) {
    errno = 0;
    EXPECT_EQ_FLOAT(0.0f, sin(20000.0f), TOL);
    EXPECT_EQ_INT(ERANGE, errno);
}

/* ---- log10 ------------------------------------------------------------- */

TEST(log10_known_values) {
    EXPECT_EQ_FLOAT(0.0f, log10(1.0f),    TOL);
    EXPECT_EQ_FLOAT(1.0f, log10(10.0f),   TOL);
    EXPECT_EQ_FLOAT(2.0f, log10(100.0f),  TOL);
    EXPECT_EQ_FLOAT(3.0f, log10(1000.0f), TOL);
}

/* ---- pow --------------------------------------------------------------- */

TEST(pow_known_values) {
    EXPECT_EQ_FLOAT(1.0f,  pow(2.0f, 0.0f), TOL);
    EXPECT_EQ_FLOAT(2.0f,  pow(2.0f, 1.0f), TOL);
    EXPECT_EQ_FLOAT(4.0f,  pow(2.0f, 2.0f), TOL);
    EXPECT_EQ_FLOAT(8.0f,  pow(2.0f, 3.0f), TOL);
    EXPECT_EQ_FLOAT(1.0f,  pow(5.0f, 0.0f), TOL);
    EXPECT_EQ_FLOAT(25.0f, pow(5.0f, 2.0f), TOL);
}

TEST(pow_sqrt_identity) {
    /* pow(x, 0.5) == sqrt(x) */
    EXPECT_EQ_FLOAT(sqrt(9.0f),   pow(9.0f,   0.5f), TOL);
    EXPECT_EQ_FLOAT(sqrt(16.0f),  pow(16.0f,  0.5f), TOL);
}

/* ---- frexp / ldexp / modf --------------------------------------------- */

TEST(frexp_basic) {
    int exp;
    float m;
    /* frexp(8.0) should give mantissa 0.5 and exp 4, since 8 = 0.5 * 2^4 */
    m = frexp(8.0f, &exp);
    EXPECT_EQ_INT(4, exp);
    EXPECT_EQ_FLOAT(0.5f, m, TOL);
}

TEST(ldexp_basic) {
    /* ldexp(0.5, 4) == 8.0 */
    EXPECT_EQ_FLOAT(8.0f,   ldexp(0.5f, 4),  TOL);
    EXPECT_EQ_FLOAT(1.0f,   ldexp(0.5f, 1),  TOL);
    EXPECT_EQ_FLOAT(0.25f,  ldexp(0.5f, -1), TOL);
}

TEST(modf_basic) {
    float ipart;
    float fpart;
    fpart = modf(3.75f, &ipart);
    EXPECT_EQ_FLOAT(3.0f,  ipart, TOL);
    EXPECT_EQ_FLOAT(0.75f, fpart, TOL);

    fpart = modf(-2.5f, &ipart);
    EXPECT_EQ_FLOAT(-2.0f, ipart, TOL);
    EXPECT_EQ_FLOAT(-0.5f, fpart, TOL);
}

int main(void) {
    puts("TMATH: math tests");
    RUN_TEST(fabs_values);
    RUN_TEST(ceil_values);
    RUN_TEST(floor_values);
    RUN_TEST(sqrt_perfect_squares);
    RUN_TEST(sqrt_non_integer);
    RUN_TEST(sin_known_values);
    RUN_TEST(cos_known_values);
    RUN_TEST(sin_cos_identity);
    RUN_TEST(tan_known_values);
    RUN_TEST(cot_known_values);
    RUN_TEST(exp_known_values);
    RUN_TEST(log_known_values);
    RUN_TEST(log_exp_inverse);
    RUN_TEST(sin_range_error);
    RUN_TEST(log10_known_values);
    RUN_TEST(pow_known_values);
    RUN_TEST(pow_sqrt_identity);
    RUN_TEST(frexp_basic);
    RUN_TEST(ldexp_basic);
    RUN_TEST(modf_basic);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
