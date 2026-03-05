/*
 * tsdcc.c
 *
 * Low-level arithmetic tests for SDCC's software float and long
 * runtime routines (__fsmul, __fsadd, __fsdiv, __fssub, etc.).
 * No math.h functions are used -- only C operators, casts, and
 * comparisons, so failures point directly at SDCC library bugs.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.03.2026   tstih
 *
 */
#include <stdio.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

#define TOL  0.0001f

/* Volatile barrier helpers: prevent SDCC from constant-folding operands. */
static float vf(float x) { volatile float t = x; return t; }
static long  vl(long  x) { volatile long  t = x; return t; }
static int   vi(int   x) { volatile int   t = x; return t; }

/* ---- float casts -------------------------------------------------------- */

TEST(float_cast_from_int) {
    EXPECT_EQ_FLOAT(0.0f,    (float)vi(0),    TOL);
    EXPECT_EQ_FLOAT(1.0f,    (float)vi(1),    TOL);
    EXPECT_EQ_FLOAT(-1.0f,   (float)vi(-1),   TOL);
    EXPECT_EQ_FLOAT(100.0f,  (float)vi(100),  TOL);
    EXPECT_EQ_FLOAT(-100.0f, (float)vi(-100), TOL);
    EXPECT_EQ_FLOAT(1000.0f, (float)vi(1000), TOL);
}

TEST(float_cast_to_int) {
    EXPECT_EQ_INT(0,    (int)vf(0.0f));
    EXPECT_EQ_INT(1,    (int)vf(1.0f));
    EXPECT_EQ_INT(-1,   (int)vf(-1.0f));
    EXPECT_EQ_INT(3,    (int)vf(3.7f));
    EXPECT_EQ_INT(-3,   (int)vf(-3.7f));
    EXPECT_EQ_INT(100,  (int)vf(100.0f));
    EXPECT_EQ_INT(-100, (int)vf(-100.0f));
}

TEST(float_cast_from_long) {
    EXPECT_EQ_FLOAT(0.0f,      (float)vl(0L),      TOL);
    EXPECT_EQ_FLOAT(1.0f,      (float)vl(1L),      TOL);
    EXPECT_EQ_FLOAT(-1.0f,     (float)vl(-1L),     TOL);
    EXPECT_EQ_FLOAT(1000.0f,   (float)vl(1000L),   TOL);
    EXPECT_EQ_FLOAT(-1000.0f,  (float)vl(-1000L),  TOL);
    EXPECT_EQ_FLOAT(100000.0f, (float)vl(100000L), 1.0f);
}

TEST(float_cast_to_long) {
    EXPECT_EQ_LONG(0L,     (long)vf(0.0f));
    EXPECT_EQ_LONG(1L,     (long)vf(1.0f));
    EXPECT_EQ_LONG(-1L,    (long)vf(-1.0f));
    EXPECT_EQ_LONG(3L,     (long)vf(3.9f));
    EXPECT_EQ_LONG(-3L,    (long)vf(-3.9f));
    EXPECT_EQ_LONG(1000L,  (long)vf(1000.0f));
    EXPECT_EQ_LONG(-1000L, (long)vf(-1000.0f));
}

/* ---- float arithmetic --------------------------------------------------- */

TEST(float_add) {
    EXPECT_EQ_FLOAT(2.0f,   vf(1.0f)   + vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(0.0f,   vf(1.0f)   + vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(-2.0f,  vf(-1.0f)  + vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(1.5f,   vf(0.5f)   + vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(0.3f,   vf(0.1f)   + vf(0.2f),   TOL);
    EXPECT_EQ_FLOAT(100.5f, vf(100.0f) + vf(0.5f),   TOL);
}

TEST(float_sub) {
    EXPECT_EQ_FLOAT(0.0f,   vf(1.0f)   - vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(2.0f,   vf(1.0f)   - vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(0.5f,   vf(1.5f)   - vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(-0.5f,  vf(1.0f)   - vf(1.5f),   TOL);
    EXPECT_EQ_FLOAT(99.5f,  vf(100.0f) - vf(0.5f),   TOL);
}

TEST(float_mul) {
    EXPECT_EQ_FLOAT(0.0f,   vf(0.0f)  * vf(5.0f),   TOL);
    EXPECT_EQ_FLOAT(1.0f,   vf(1.0f)  * vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(-1.0f,  vf(1.0f)  * vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(1.0f,   vf(-1.0f) * vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(6.0f,   vf(2.0f)  * vf(3.0f),   TOL);
    EXPECT_EQ_FLOAT(0.25f,  vf(0.5f)  * vf(0.5f),   TOL);
    EXPECT_EQ_FLOAT(100.0f, vf(10.0f) * vf(10.0f),  TOL);
    EXPECT_EQ_FLOAT(-6.0f,  vf(-2.0f) * vf(3.0f),   TOL);
}

TEST(float_div) {
    EXPECT_EQ_FLOAT(1.0f,   vf(1.0f)  / vf(1.0f),   TOL);
    EXPECT_EQ_FLOAT(-1.0f,  vf(1.0f)  / vf(-1.0f),  TOL);
    EXPECT_EQ_FLOAT(2.0f,   vf(6.0f)  / vf(3.0f),   TOL);
    EXPECT_EQ_FLOAT(0.5f,   vf(1.0f)  / vf(2.0f),   TOL);
    EXPECT_EQ_FLOAT(0.25f,  vf(1.0f)  / vf(4.0f),   TOL);
    EXPECT_EQ_FLOAT(0.1f,   vf(1.0f)  / vf(10.0f),  TOL);
    EXPECT_EQ_FLOAT(3.3333f,vf(10.0f) / vf(3.0f),   0.001f);
}

/* ---- float comparisons -------------------------------------------------- */

TEST(float_compare) {
    EXPECT_TRUE(vf(1.0f)  >  vf(0.0f));
    EXPECT_TRUE(vf(0.0f)  <  vf(1.0f));
    EXPECT_TRUE(vf(1.0f)  == vf(1.0f));
    EXPECT_TRUE(vf(-1.0f) <  vf(0.0f));
    EXPECT_TRUE(vf(0.0f)  >  vf(-1.0f));
    EXPECT_TRUE(vf(1.5f)  >  vf(1.0f));
    EXPECT_TRUE(vf(1.0f)  <  vf(1.5f));
    EXPECT_TRUE(vf(0.0f)  == vf(0.0f));
    EXPECT_TRUE(vf(-1.0f) <  vf(-0.5f));
}

/* ---- float edge cases --------------------------------------------------- */

TEST(float_edge) {
    float z   = vf(0.0f);
    float one = vf(1.0f);
    float neg = vf(-1.0f);

    /* zero arithmetic */
    EXPECT_EQ_FLOAT(0.0f,  z + z,   TOL);
    EXPECT_EQ_FLOAT(0.0f,  z * one, TOL);
    EXPECT_EQ_FLOAT(0.0f,  z / one, TOL);

    /* identity */
    EXPECT_EQ_FLOAT(1.0f,  one * one,  TOL);
    EXPECT_EQ_FLOAT(1.0f,  one / vf(one),  TOL);
    EXPECT_EQ_FLOAT(0.0f,  one - vf(1.0f),  TOL);

    /* sign flip */
    EXPECT_EQ_FLOAT(-1.0f, neg * one,  TOL);
    EXPECT_EQ_FLOAT( 1.0f, neg * vf(neg),  TOL);
    EXPECT_EQ_FLOAT(-1.0f, neg / one,  TOL);
    EXPECT_EQ_FLOAT( 1.0f, neg / vf(neg),  TOL);

    /* accumulation */
    float acc = 0.0f;
    int j;
    for (j = 0; j < 10; j++) acc += vf(0.1f);
    EXPECT_EQ_FLOAT(1.0f, acc, 0.001f);
}

/* ---- long casts --------------------------------------------------------- */

TEST(long_cast_from_int) {
    EXPECT_EQ_LONG(0L,     (long)vi(0));
    EXPECT_EQ_LONG(1L,     (long)vi(1));
    EXPECT_EQ_LONG(-1L,    (long)vi(-1));
    EXPECT_EQ_LONG(1000L,  (long)vi(1000));
    EXPECT_EQ_LONG(-1000L, (long)vi(-1000));
}

TEST(long_cast_to_int) {
    EXPECT_EQ_INT(0,     (int)vl(0L));
    EXPECT_EQ_INT(1,     (int)vl(1L));
    EXPECT_EQ_INT(-1,    (int)vl(-1L));
    EXPECT_EQ_INT(100,   (int)vl(100L));
    EXPECT_EQ_INT(-100,  (int)vl(-100L));
    EXPECT_EQ_INT(32767, (int)vl(32767L));
}

/* ---- long arithmetic ---------------------------------------------------- */

TEST(long_add) {
    EXPECT_EQ_LONG(0L,        vl(0L)      + vl(0L));
    EXPECT_EQ_LONG(2L,        vl(1L)      + vl(1L));
    EXPECT_EQ_LONG(0L,        vl(1L)      + vl(-1L));
    EXPECT_EQ_LONG(-2L,       vl(-1L)     + vl(-1L));
    EXPECT_EQ_LONG(100000L,   vl(99999L)  + vl(1L));
    EXPECT_EQ_LONG(-100000L,  vl(-99999L) + vl(-1L));
    EXPECT_EQ_LONG(65536L,    vl(32768L)  + vl(32768L));
}

TEST(long_sub) {
    EXPECT_EQ_LONG(0L,        vl(1L)      - vl(1L));
    EXPECT_EQ_LONG(2L,        vl(1L)      - vl(-1L));
    EXPECT_EQ_LONG(100000L,   vl(200000L) - vl(100000L));
    EXPECT_EQ_LONG(-100000L,  vl(0L)      - vl(100000L));
}

TEST(long_mul) {
    EXPECT_EQ_LONG(0L,        vl(0L)    * vl(5L));
    EXPECT_EQ_LONG(1L,        vl(1L)    * vl(1L));
    EXPECT_EQ_LONG(-1L,       vl(1L)    * vl(-1L));
    EXPECT_EQ_LONG(1L,        vl(-1L)   * vl(-1L));
    EXPECT_EQ_LONG(6L,        vl(2L)    * vl(3L));
    EXPECT_EQ_LONG(100000L,   vl(1000L) * vl(100L));
    EXPECT_EQ_LONG(-6L,       vl(-2L)   * vl(3L));
}

TEST(long_div) {
    EXPECT_EQ_LONG(1L,        vl(1L)      / vl(1L));
    EXPECT_EQ_LONG(-1L,       vl(1L)      / vl(-1L));
    EXPECT_EQ_LONG(2L,        vl(6L)      / vl(3L));
    EXPECT_EQ_LONG(1000L,     vl(100000L) / vl(100L));
    EXPECT_EQ_LONG(-2L,       vl(6L)      / vl(-3L));
    EXPECT_EQ_LONG(0L,        vl(1L)      / vl(2L));
}

TEST(long_mod) {
    EXPECT_EQ_LONG(0L,  vl(6L)      % vl(3L));
    EXPECT_EQ_LONG(1L,  vl(7L)      % vl(3L));
    EXPECT_EQ_LONG(2L,  vl(8L)      % vl(3L));
    EXPECT_EQ_LONG(0L,  vl(0L)      % vl(5L));
    EXPECT_EQ_LONG(1L,  vl(100001L) % vl(2L));
    EXPECT_EQ_LONG(0L,  vl(100000L) % vl(2L));
}

/* ---- long comparisons --------------------------------------------------- */

TEST(long_compare) {
    EXPECT_TRUE(vl(1L)       >  vl(0L));
    EXPECT_TRUE(vl(0L)       <  vl(1L));
    EXPECT_TRUE(vl(1L)       == vl(1L));
    EXPECT_TRUE(vl(-1L)      <  vl(0L));
    EXPECT_TRUE(vl(0L)       >  vl(-1L));
    EXPECT_TRUE(vl(100000L)  >  vl(99999L));
    EXPECT_TRUE(vl(99999L)   <  vl(100000L));
    EXPECT_TRUE(vl(-100000L) <  vl(-99999L));
}

/* ---- mixed float/long chains -------------------------------------------- */

TEST(float_long_chain) {
    /* (float -> long -> float) round-trip */
    float f1 = vf(42.0f);
    long  l1 = (long)f1;
    float f2 = (float)l1;
    EXPECT_EQ_FLOAT(42.0f, f2, TOL);

    /* accumulate longs, cast result to float */
    long acc = 0L;
    int  j;
    for (j = 0; j < 100; j++) acc += vl(1L);
    EXPECT_EQ_FLOAT(100.0f, (float)acc, TOL);

    /* simple float expression, store in long */
    float fx = vf(3.0f) * vf(4.0f);
    long  lx = (long)fx;
    EXPECT_EQ_LONG(12L, lx);
}

/* ---- main --------------------------------------------------------------- */

void main(void) {
    printf("TSDCC: SDCC float/long arithmetic\r\n");

    /* float casts */
    RUN_TEST(float_cast_from_int);
    RUN_TEST(float_cast_to_int);
    RUN_TEST(float_cast_from_long);
    RUN_TEST(float_cast_to_long);

    /* float arithmetic */
    RUN_TEST(float_add);
    RUN_TEST(float_sub);
    RUN_TEST(float_mul);
    RUN_TEST(float_div);
    RUN_TEST(float_compare);
    RUN_TEST(float_edge);

    /* long casts */
    RUN_TEST(long_cast_from_int);
    RUN_TEST(long_cast_to_int);

    /* long arithmetic */
    RUN_TEST(long_add);
    RUN_TEST(long_sub);
    RUN_TEST(long_mul);
    RUN_TEST(long_div);
    RUN_TEST(long_mod);
    RUN_TEST(long_compare);

    /* mixed */
    RUN_TEST(float_long_chain);

    if (g_tests_failed == 0)
        printf("PASS all %d tests\r\n", g_tests_run);
    else
        printf("FAIL %d failures in %d/%d tests\r\n",
               g_failures, g_tests_failed, g_tests_run);
}
