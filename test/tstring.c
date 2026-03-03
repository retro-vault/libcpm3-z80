/*
 * tstring.c
 *
 * Tests for string.h memory and string functions.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

/* ---- memory functions -------------------------------------------------- */

TEST(memset_fills) {
    char buf[8];
    memset(buf, 0xAA, 8);
    EXPECT_EQ_INT(0xAA & 0xFF, (unsigned char)buf[0]);
    EXPECT_EQ_INT(0xAA & 0xFF, (unsigned char)buf[7]);
    memset(buf, 0, 8);
    EXPECT_EQ_INT(0, buf[0]);
    EXPECT_EQ_INT(0, buf[7]);
}

TEST(memcpy_copies) {
    char src[6] = "hello";
    char dst[6];
    memcpy(dst, src, 6);
    EXPECT_EQ_INT(0, memcmp(dst, src, 6));
}

TEST(memcmp_compares) {
    EXPECT_EQ_INT(0, memcmp("abc", "abc", 3));
    EXPECT_TRUE(memcmp("abc", "abd", 3) < 0);
    EXPECT_TRUE(memcmp("abd", "abc", 3) > 0);
    EXPECT_EQ_INT(0, memcmp("abc", "abcXYZ", 3)); /* only first 3 */
}

TEST(memchr_finds) {
    const char *s = "abcdef";
    EXPECT_TRUE(memchr(s, 'c', 6) == s + 2);
    EXPECT_TRUE(memchr(s, 'z', 6) == NULL);
    EXPECT_TRUE(memchr(s, 'a', 1) == s);     /* found at position 0 */
    EXPECT_TRUE(memchr(s, 'b', 1) == NULL);  /* not within n=1 */
}

/* ---- string length and copy ------------------------------------------- */

TEST(strlen_basic) {
    EXPECT_EQ_INT(0, (int)strlen(""));
    EXPECT_EQ_INT(5, (int)strlen("hello"));
    EXPECT_EQ_INT(1, (int)strlen("x"));
    EXPECT_EQ_INT(3, (int)strlen("abc"));
}

TEST(strcpy_copies) {
    char dst[16];
    strcpy(dst, "hello");
    EXPECT_EQ_STR("hello", dst);
    strcpy(dst, "");
    EXPECT_EQ_STR("", dst);
}

TEST(strncpy_partial) {
    char dst[8];
    memset(dst, 0xFF, 8);
    strncpy(dst, "hello", 3);
    /* first 3 bytes copied, rest padded with \0 up to n */
    EXPECT_EQ_INT('h', dst[0]);
    EXPECT_EQ_INT('e', dst[1]);
    EXPECT_EQ_INT('l', dst[2]);
}

TEST(strncpy_full) {
    char dst[8];
    strncpy(dst, "hi", 8);
    EXPECT_EQ_STR("hi", dst);
    EXPECT_EQ_INT(0, dst[2]); /* padded with NUL */
    EXPECT_EQ_INT(0, dst[7]);
}

/* ---- string comparison ------------------------------------------------- */

TEST(strcmp_compares) {
    EXPECT_EQ_INT(0, strcmp("abc", "abc"));
    EXPECT_TRUE(strcmp("abc", "abd") < 0);
    EXPECT_TRUE(strcmp("abd", "abc") > 0);
    EXPECT_TRUE(strcmp("",  "a")   < 0);
    EXPECT_TRUE(strcmp("a", "")    > 0);
    EXPECT_EQ_INT(0, strcmp("", ""));
}

TEST(strncmp_partial) {
    EXPECT_EQ_INT(0, strncmp("abcX", "abcY", 3));
    EXPECT_TRUE(strncmp("abcX", "abcY", 4) < 0);
    EXPECT_EQ_INT(0, strncmp("", "", 0));
}

/* ---- string search ----------------------------------------------------- */

TEST(strchr_finds) {
    const char *s = "abcabc";
    EXPECT_TRUE(strchr(s, 'a') == s);         /* first 'a' */
    EXPECT_TRUE(strchr(s, 'c') == s + 2);     /* first 'c' */
    EXPECT_TRUE(strchr(s, '\0') == s + 6);    /* NUL terminator */
    EXPECT_TRUE(strchr(s, 'z') == NULL);
}

TEST(strrchr_last) {
    const char *s = "abcabc";
    EXPECT_TRUE(strrchr(s, 'a') == s + 3);    /* last 'a' */
    EXPECT_TRUE(strrchr(s, 'c') == s + 5);    /* last 'c' */
    EXPECT_TRUE(strrchr(s, 'z') == NULL);
}

TEST(strcspn_span) {
    EXPECT_EQ_INT(3, (int)strcspn("abcdef", "dxyz")); /* 'a','b','c' before 'd' */
    EXPECT_EQ_INT(0, (int)strcspn("abcdef", "a"));    /* 'a' is first char */
    EXPECT_EQ_INT(6, (int)strcspn("abcdef", "xyz"));  /* no match */
}

/* ---- tokenisation ------------------------------------------------------ */

TEST(strtok_splits) {
    char s[] = "one,two,three";
    char *tok;
    tok = strtok(s, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("one", tok);
    tok = strtok(NULL, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("two", tok);
    tok = strtok(NULL, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("three", tok);
    tok = strtok(NULL, ",");
    EXPECT_TRUE(tok == NULL);
}

TEST(strsep_splits) {
    char buf[] = "a:b:c";
    char *p = buf;
    char *tok;
    tok = strsep(&p, ":");
    EXPECT_EQ_STR("a", tok);
    tok = strsep(&p, ":");
    EXPECT_EQ_STR("b", tok);
    tok = strsep(&p, ":");
    EXPECT_EQ_STR("c", tok);
    tok = strsep(&p, ":");
    EXPECT_TRUE(tok == NULL);
}

/* ---- case and reverse -------------------------------------------------- */

TEST(strrev_reverses) {
    char s[] = "hello";
    strrev(s, 5);
    EXPECT_EQ_STR("olleh", s);

    char s2[] = "a";
    strrev(s2, 1);
    EXPECT_EQ_STR("a", s2);

    char s3[] = "ab";
    strrev(s3, 2);
    EXPECT_EQ_STR("ba", s3);
}

TEST(stoupper_converts) {
    char s[] = "Hello World 123";
    stoupper(s);
    EXPECT_EQ_STR("HELLO WORLD 123", s);
}

TEST(stolower_converts) {
    char s[] = "Hello World 123";
    stolower(s);
    EXPECT_EQ_STR("hello world 123", s);
}

/* ---- error string ------------------------------------------------------ */

TEST(strerror_returns_string) {
    const char *msg;
    msg = strerror(ENOENT);
    EXPECT_TRUE(msg != NULL);
    EXPECT_TRUE(strlen(msg) > 0);
    msg = strerror(0);          /* no error */
    EXPECT_TRUE(msg != NULL);
}

int main(void) {
    puts("TSTRING: string tests");
    RUN_TEST(memset_fills);
    RUN_TEST(memcpy_copies);
    RUN_TEST(memcmp_compares);
    RUN_TEST(memchr_finds);
    RUN_TEST(strlen_basic);
    RUN_TEST(strcpy_copies);
    RUN_TEST(strncpy_partial);
    RUN_TEST(strncpy_full);
    RUN_TEST(strcmp_compares);
    RUN_TEST(strncmp_partial);
    RUN_TEST(strchr_finds);
    RUN_TEST(strrchr_last);
    RUN_TEST(strcspn_span);
    RUN_TEST(strtok_splits);
    RUN_TEST(strsep_splits);
    RUN_TEST(strrev_reverses);
    RUN_TEST(stoupper_converts);
    RUN_TEST(stolower_converts);
    RUN_TEST(strerror_returns_string);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
