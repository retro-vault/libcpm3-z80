/*
 * tsetjmp.c
 *
 * Tests for setjmp/longjmp.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio.h>
#include <setjmp.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

static jmp_buf g_env;
static int g_side_effect;

static void jump_value(int value) {
    g_side_effect += 1;
    longjmp(g_env, value);
}

static void jump_nested(int value) {
    jump_value(value);
}

TEST(setjmp_initial_return_is_zero) {
    int rc = setjmp(g_env);
    EXPECT_EQ_INT(0, rc);
}

TEST(longjmp_returns_value) {
    int rc = setjmp(g_env);
    if (rc == 0) {
        g_side_effect = 10;
        jump_value(7);
        ASSERT_TRUE(0);
    }
    EXPECT_EQ_INT(7, rc);
    EXPECT_EQ_INT(11, g_side_effect);
}

TEST(longjmp_zero_becomes_one) {
    int rc = setjmp(g_env);
    if (rc == 0) {
        longjmp(g_env, 0);
        ASSERT_TRUE(0);
    }
    EXPECT_EQ_INT(1, rc);
}

TEST(longjmp_unwinds_nested_calls) {
    volatile int sentinel = 1234;
    int rc = setjmp(g_env);
    if (rc == 0) {
        g_side_effect = 20;
        jump_nested(9);
        ASSERT_TRUE(0);
    }
    EXPECT_EQ_INT(9, rc);
    EXPECT_EQ_INT(21, g_side_effect);
    EXPECT_EQ_INT(1234, sentinel);
}

int main(void) {
    puts("TSETJMP: setjmp tests");
    RUN_TEST(setjmp_initial_return_is_zero);
    RUN_TEST(longjmp_returns_value);
    RUN_TEST(longjmp_zero_becomes_one);
    RUN_TEST(longjmp_unwinds_nested_calls);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
