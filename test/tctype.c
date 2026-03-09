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

TEST(classification_helpers) {
    EXPECT_TRUE(isalnum('A'));
    EXPECT_TRUE(isalnum('7'));
    EXPECT_TRUE(!isalnum('!'));

    EXPECT_TRUE(iscntrl('\n'));
    EXPECT_TRUE(iscntrl('\r'));
    EXPECT_TRUE(!iscntrl('A'));

    EXPECT_TRUE(isgraph('!'));
    EXPECT_TRUE(isgraph('A'));
    EXPECT_TRUE(!isgraph(' '));

    EXPECT_TRUE(islower('a'));
    EXPECT_TRUE(!islower('A'));
    EXPECT_TRUE(isupper('Z'));
    EXPECT_TRUE(!isupper('z'));

    EXPECT_TRUE(isprint(' '));
    EXPECT_TRUE(isprint('~'));
    EXPECT_TRUE(!isprint('\n'));

    EXPECT_TRUE(isxdigit('0'));
    EXPECT_TRUE(isxdigit('9'));
    EXPECT_TRUE(isxdigit('a'));
    EXPECT_TRUE(isxdigit('F'));
    EXPECT_TRUE(!isxdigit('g'));
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
    printf("TCTYPE: ctype tests\r\n");
    RUN_TEST(isalpha_letters);
    RUN_TEST(isdigit_digits);
    RUN_TEST(isspace_whitespace);
    RUN_TEST(ispunct_punctuation);
    RUN_TEST(classification_helpers);
    RUN_TEST(tolower_converts);
    RUN_TEST(toupper_converts);
    if (g_failures == 0) {
        printf("PASS all %d tests\r\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\r\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
