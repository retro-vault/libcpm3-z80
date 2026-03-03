/*
 * tctype.c
 *
 * Tests for ctype.h character classification functions.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <ctype.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

TEST(isalpha_letters) {
    EXPECT_TRUE(isalpha('a'));
    EXPECT_TRUE(isalpha('z'));
    EXPECT_TRUE(isalpha('A'));
    EXPECT_TRUE(isalpha('Z'));
    EXPECT_TRUE(isalpha('m'));
    EXPECT_TRUE(!isalpha('0'));
    EXPECT_TRUE(!isalpha('9'));
    EXPECT_TRUE(!isalpha(' '));
    EXPECT_TRUE(!isalpha('!'));
    EXPECT_TRUE(!isalpha('\0'));
}

TEST(isdigit_digits) {
    EXPECT_TRUE(isdigit('0'));
    EXPECT_TRUE(isdigit('5'));
    EXPECT_TRUE(isdigit('9'));
    EXPECT_TRUE(!isdigit('a'));
    EXPECT_TRUE(!isdigit('A'));
    EXPECT_TRUE(!isdigit('/'));   /* ASCII 47 -- just before '0' (48) */
    EXPECT_TRUE(!isdigit(':'));   /* ASCII 58 -- just after  '9' (57) */
    EXPECT_TRUE(!isdigit(' '));
}

TEST(isspace_whitespace) {
    EXPECT_TRUE(isspace(' '));
    EXPECT_TRUE(isspace('\t'));
    EXPECT_TRUE(isspace('\n'));
    EXPECT_TRUE(isspace('\r'));
    EXPECT_TRUE(!isspace('a'));
    EXPECT_TRUE(!isspace('0'));
    EXPECT_TRUE(!isspace('!'));
    EXPECT_TRUE(!isspace('\0'));
}

TEST(ispunct_punctuation) {
    EXPECT_TRUE(ispunct('!'));
    EXPECT_TRUE(ispunct('.'));
    EXPECT_TRUE(ispunct(','));
    EXPECT_TRUE(ispunct(';'));
    EXPECT_TRUE(ispunct('@'));
    EXPECT_TRUE(ispunct('['));
    EXPECT_TRUE(!ispunct('a'));
    EXPECT_TRUE(!ispunct('0'));
    EXPECT_TRUE(!ispunct(' '));
}

TEST(tolower_converts) {
    EXPECT_EQ_INT('a', tolower('A'));
    EXPECT_EQ_INT('z', tolower('Z'));
    EXPECT_EQ_INT('m', tolower('M'));
    EXPECT_EQ_INT('a', tolower('a'));  /* already lower -- unchanged */
    EXPECT_EQ_INT('0', tolower('0'));  /* digit unchanged */
    EXPECT_EQ_INT(' ', tolower(' ')); /* space unchanged */
}

TEST(toupper_converts) {
    EXPECT_EQ_INT('A', toupper('a'));
    EXPECT_EQ_INT('Z', toupper('z'));
    EXPECT_EQ_INT('M', toupper('m'));
    EXPECT_EQ_INT('A', toupper('A'));  /* already upper -- unchanged */
    EXPECT_EQ_INT('0', toupper('0')); /* digit unchanged */
    EXPECT_EQ_INT(' ', toupper(' ')); /* space unchanged */
}

int main(void) {
    puts("TCTYPE: ctype tests");
    RUN_TEST(isalpha_letters);
    RUN_TEST(isdigit_digits);
    RUN_TEST(isspace_whitespace);
    RUN_TEST(ispunct_punctuation);
    RUN_TEST(tolower_converts);
    RUN_TEST(toupper_converts);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
