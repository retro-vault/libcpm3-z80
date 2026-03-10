/*
 * textrab.c
 *
 * Additional string, stdlib, and math edge-case tests.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 10.03.2026   tstih
 *
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <errno.h>
#include <platform.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

#define TOL 0.0001f

static int int_cmp(const void *a, const void *b)
{
    return *(const int *)a - *(const int *)b;
}

#define DEF_BOOL_TEST(name, expr) \
    TEST(name) { EXPECT_TRUE((expr)); }

#define DEF_INT_TEST(name, exp, expr) \
    TEST(name) { EXPECT_EQ_INT((exp), (expr)); }

#define DEF_LONG_TEST(name, exp, expr) \
    TEST(name) { EXPECT_EQ_LONG((exp), (expr)); }

#define DEF_FLOAT_TEST(name, exp, expr, tol) \
    TEST(name) { EXPECT_EQ_FLOAT((exp), (expr), (tol)); }

/* ---- string ----------------------------------------------------------- */

TEST(string_memset_return) {
    char buf[8];
    EXPECT_TRUE(memset(buf, 'X', 3) == buf);
}

TEST(string_memset_zero_count) {
    char buf[4] = "abc";
    memset(buf, 'Z', 0);
    EXPECT_EQ_STR("abc", buf);
}

TEST(string_memcpy_return) {
    char dst[4];
    char src[4] = "abc";
    EXPECT_TRUE(memcpy(dst, src, 4) == dst);
}

TEST(string_memcpy_zero_count) {
    char dst[4] = "abc";
    char src[4] = "xyz";
    memcpy(dst, src, 0);
    EXPECT_EQ_STR("abc", dst);
}

DEF_INT_TEST(string_memcmp_zero_count, 0, memcmp("abc", "xyz", 0))
DEF_BOOL_TEST(string_memcmp_less, memcmp("abc", "abd", 3) < 0)
DEF_BOOL_TEST(string_memcmp_greater, memcmp("abd", "abc", 3) > 0)
DEF_BOOL_TEST(string_memchr_zero_count, memchr("abc", 'a', 0) == NULL)

TEST(string_memchr_zero_byte) {
    static const char buf[4] = { 'a', '\0', 'b', '\0' };
    EXPECT_TRUE(memchr(buf, '\0', 4) == buf + 1);
}

DEF_INT_TEST(string_strlen_spaces, 3, (int)strlen("   "))
DEF_INT_TEST(string_strlen_single, 1, (int)strlen("x"))

TEST(string_strcpy_return) {
    char dst[8];
    EXPECT_TRUE(strcpy(dst, "hi") == dst);
    EXPECT_EQ_STR("hi", dst);
}

TEST(string_strncpy_pad) {
    char dst[6];
    memset(dst, 'X', sizeof(dst));
    strncpy(dst, "ab", 5);
    EXPECT_EQ_INT('a', dst[0]);
    EXPECT_EQ_INT('b', dst[1]);
    EXPECT_EQ_INT(0, dst[2]);
    EXPECT_EQ_INT(0, dst[4]);
}

TEST(string_strncpy_limit) {
    char dst[4];
    strncpy(dst, "abcdef", 3);
    dst[3] = '\0';
    EXPECT_EQ_STR("abc", dst);
}

DEF_BOOL_TEST(string_strcmp_case, strcmp("abc", "ABC") > 0)
DEF_BOOL_TEST(string_strcmp_prefix, strcmp("abcd", "abc") > 0)
DEF_INT_TEST(string_strncmp_zero, 0, strncmp("abc", "xyz", 0))
DEF_BOOL_TEST(string_strncmp_shorter, strncmp("ab", "ac", 2) < 0)
DEF_BOOL_TEST(string_strchr_missing, strchr("abc", 'z') == NULL)

TEST(string_strchr_first) {
    const char *s = "abc";
    EXPECT_TRUE(strchr(s, 'a') == s);
}

TEST(string_strchr_nul) {
    const char *s = "abc";
    EXPECT_TRUE(strchr(s, '\0') == s + 3);
}

TEST(string_strrchr_nul) {
    const char *s = "abc";
    EXPECT_TRUE(strrchr(s, '\0') == s + 3);
}

TEST(string_strrchr_single) {
    const char *s = "a";
    EXPECT_TRUE(strrchr(s, 'a') == s);
}

DEF_INT_TEST(string_strcspn_empty_set, 3, (int)strcspn("abc", ""))
DEF_INT_TEST(string_strcspn_empty_str, 0, (int)strcspn("", "abc"))

TEST(string_strtok_single) {
    char s[] = "alpha";
    char *tok = strtok(s, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("alpha", tok);
    EXPECT_TRUE(strtok(NULL, ",") == NULL);
}

TEST(string_strtok_leading_delims) {
    char s[] = ",,alpha,beta";
    char *tok = strtok(s, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("alpha", tok);
    tok = strtok(NULL, ",");
    ASSERT_TRUE(tok != NULL);
    EXPECT_EQ_STR("beta", tok);
}

TEST(string_strsep_empty_middle) {
    char s[] = "a::b";
    char *p = s;
    EXPECT_EQ_STR("a", strsep(&p, ":"));
    EXPECT_EQ_STR("", strsep(&p, ":"));
    EXPECT_EQ_STR("b", strsep(&p, ":"));
}

TEST(string_strsep_no_delim) {
    char s[] = "abc";
    char *p = s;
    EXPECT_EQ_STR("abc", strsep(&p, ":"));
    EXPECT_TRUE(strsep(&p, ":") == NULL);
}

TEST(string_strrev_empty) {
    char s[1] = { '\0' };
    strrev(s, 0);
    EXPECT_EQ_STR("", s);
}

TEST(string_strrev_even) {
    char s[] = "abcd";
    strrev(s, 4);
    EXPECT_EQ_STR("dcba", s);
}

TEST(string_stoupper_already) {
    char s[] = "ABC123";
    stoupper(s);
    EXPECT_EQ_STR("ABC123", s);
}

TEST(string_stolower_already) {
    char s[] = "abc123";
    stolower(s);
    EXPECT_EQ_STR("abc123", s);
}

TEST(string_strerror_enoent) {
    const char *s = strerror(ENOENT);
    ASSERT_TRUE(s != NULL);
    EXPECT_TRUE(strlen(s) > 0);
}

/* ---- stdlib ----------------------------------------------------------- */

DEF_INT_TEST(stdlib_atoi_plus, 42, atoi("+42"))
DEF_INT_TEST(stdlib_atoi_minus_zero, 0, atoi("-0"))
DEF_INT_TEST(stdlib_atoi_trailing_space, 12, atoi("12 "))
DEF_LONG_TEST(stdlib_atol_plus, 42L, atol("+42"))
DEF_LONG_TEST(stdlib_atol_spaces, -7L, atol("   -7"))
DEF_FLOAT_TEST(stdlib_atof_whole, 12.0f, atof("12"), TOL)
DEF_FLOAT_TEST(stdlib_atof_leading_space, 3.5f, atof(" 3.5"), TOL)

TEST(stdlib_itoa_octal) {
    char buf[16];
    EXPECT_EQ_STR("10", itoa(8, buf, 8));
}

TEST(stdlib_itoa_binary) {
    char buf[16];
    EXPECT_EQ_STR("101", itoa(5, buf, 2));
}

TEST(stdlib_itoa_invalid_base) {
    char buf[4];
    EXPECT_EQ_STR("", itoa(5, buf, 1));
}

DEF_LONG_TEST(stdlib_strtol_base8, 63L, strtol("77", NULL, 8))
DEF_LONG_TEST(stdlib_strtol_negative_hex, -255L, strtol("-0xff", NULL, 16))
DEF_LONG_TEST(stdlib_strtol_plus_sign, 99L, strtol("+99", NULL, 10))

TEST(stdlib_strtol_no_digits_endptr) {
    char buf[] = "xyz";
    char *end;
    EXPECT_EQ_LONG(0L, strtol(buf, &end, 10));
    EXPECT_TRUE(end == buf);
}

DEF_LONG_TEST(stdlib_strtoul_base0_octal, 63L, (long)strtoul("077", NULL, 0))
DEF_LONG_TEST(stdlib_strtoul_base0_hex, 255L, (long)strtoul("0xff", NULL, 0))
DEF_LONG_TEST(stdlib_strtoumax_decimal, 123456L, (long)strtoumax("123456", NULL, 10))

TEST(stdlib_strtoimax_endptr) {
    char *end;
    EXPECT_EQ_LONG(15L, (long)strtoimax("15xyz", &end, 10));
    EXPECT_EQ_STR("xyz", end);
}

TEST(stdlib_rand_two_sequence_repro) {
    int a1, a2, b1, b2;
    srand(7);
    a1 = rand();
    a2 = rand();
    srand(7);
    b1 = rand();
    b2 = rand();
    EXPECT_EQ_INT(a1, b1);
    EXPECT_EQ_INT(a2, b2);
}

TEST(stdlib_bsearch_first) {
    static const int arr[] = { 1, 3, 5, 7 };
    int key = 1;
    int *p = (int *)bsearch(&key, arr, 4, sizeof(arr[0]), int_cmp);
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ_INT(1, *p);
}

TEST(stdlib_bsearch_last) {
    static const int arr[] = { 1, 3, 5, 7 };
    int key = 7;
    int *p = (int *)bsearch(&key, arr, 4, sizeof(arr[0]), int_cmp);
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ_INT(7, *p);
}

TEST(stdlib_qsort_reverse) {
    int arr[] = { 5, 4, 3, 2, 1 };
    qsort(arr, 5, sizeof(arr[0]), int_cmp);
    EXPECT_EQ_INT(1, arr[0]);
    EXPECT_EQ_INT(5, arr[4]);
}

TEST(stdlib_qsort_duplicates) {
    int arr[] = { 4, 1, 4, 2, 2 };
    qsort(arr, 5, sizeof(arr[0]), int_cmp);
    EXPECT_EQ_INT(1, arr[0]);
    EXPECT_EQ_INT(2, arr[1]);
    EXPECT_EQ_INT(2, arr[2]);
    EXPECT_EQ_INT(4, arr[3]);
    EXPECT_EQ_INT(4, arr[4]);
}

DEF_LONG_TEST(stdlib_labs_large, 123456L, labs(-123456L))

TEST(stdlib_div_exact) {
    div_t qr = div(20, 5);
    EXPECT_EQ_INT(4, qr.quot);
    EXPECT_EQ_INT(0, qr.rem);
}

TEST(stdlib_ldiv_exact) {
    ldiv_t qr = ldiv(120000L, 1000L);
    EXPECT_EQ_LONG(120L, qr.quot);
    EXPECT_EQ_LONG(0L, qr.rem);
}

TEST(stdlib_malloc_one) {
    unsigned char *p = (unsigned char *)malloc(1);
    ASSERT_TRUE(p != NULL);
    *p = 0x5a;
    { volatile int expected = 0x5a; EXPECT_EQ_INT(expected, *p); }
    free(p);
}

TEST(stdlib_calloc_two_by_two) {
    unsigned char *p = (unsigned char *)calloc(2, 2);
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ_INT(0, p[0]);
    EXPECT_EQ_INT(0, p[3]);
    free(p);
}

TEST(stdlib_splitpath_lowercase_normalizes) {
    char drive[MAX_DRIVE + 1];
    int user;
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    EXPECT_EQ_INT(0, _splitpath("b:read.me", drive, &user, fname, ext));
    EXPECT_EQ_STR("B", drive);
    EXPECT_EQ_STR("READ", fname);
    EXPECT_EQ_STR("ME", ext);
}

TEST(stdlib_nltype_set_lfcr) {
    volatile char *p = &nltype;
    char old = *p;
    *p = NL_LFCR;
    { volatile int expected = NL_LFCR; EXPECT_EQ_INT(expected, *p); }
    *p = old;
}

/* ---- math ------------------------------------------------------------- */

DEF_FLOAT_TEST(math_fabs_neg_zero, 0.0f, fabs(-0.0f), TOL)
DEF_FLOAT_TEST(math_ceil_zero, 0.0f, ceil(0.0f), TOL)
DEF_FLOAT_TEST(math_floor_zero, 0.0f, floor(0.0f), TOL)
DEF_FLOAT_TEST(math_sqrt_fraction, 0.5f, sqrt(0.25f), TOL)
DEF_FLOAT_TEST(math_sin_negative, -1.0f, sin(-1.57079633f), 0.001f)
DEF_FLOAT_TEST(math_cos_even, cos(1.0f), cos(-1.0f), TOL)
DEF_FLOAT_TEST(math_tan_negative, -1.0f, tan(-0.78539816f), 0.001f)
DEF_FLOAT_TEST(math_cot_negative, -1.0f, cot(-0.78539816f), 0.001f)
DEF_FLOAT_TEST(math_exp_two, 7.389056f, exp(2.0f), 0.001f)
DEF_FLOAT_TEST(math_log10_fraction, -1.0f, log10(0.1f), 0.001f)
DEF_FLOAT_TEST(math_pow_zero_power, 1.0f, pow(7.0f, 0.0f), TOL)

DEF_FLOAT_TEST(math_ldexp_zero, 0.0f, ldexp(0.0f, 7), TOL)

TEST(math_modf_integer) {
    float ip;
    float fp = modf(7.0f, &ip);
    EXPECT_EQ_FLOAT(7.0f, ip, TOL);
    EXPECT_EQ_FLOAT(0.0f, fp, TOL);
}

DEF_FLOAT_TEST(math_sin_zero, 0.0f, sin(0.0f), TOL)
DEF_FLOAT_TEST(math_cos_zero, 1.0f, cos(0.0f), TOL)
DEF_FLOAT_TEST(math_sqrt_one, 1.0f, sqrt(1.0f), TOL)
DEF_FLOAT_TEST(math_exp_log_three, 3.0f, exp(log(3.0f)), 0.001f)
DEF_FLOAT_TEST(math_pow_one_any, 1.0f, pow(1.0f, 123.0f), TOL)

int main(void)
{
    puts("TEXTRAB: extra string/stdlib/math tests");

    RUN_TEST(string_memset_return);
    RUN_TEST(string_memset_zero_count);
    RUN_TEST(string_memcpy_return);
    RUN_TEST(string_memcpy_zero_count);
    RUN_TEST(string_memcmp_zero_count);
    RUN_TEST(string_memcmp_less);
    RUN_TEST(string_memcmp_greater);
    RUN_TEST(string_memchr_zero_count);
    RUN_TEST(string_memchr_zero_byte);
    RUN_TEST(string_strlen_spaces);
    RUN_TEST(string_strlen_single);
    RUN_TEST(string_strcpy_return);
    RUN_TEST(string_strncpy_pad);
    RUN_TEST(string_strncpy_limit);
    RUN_TEST(string_strcmp_case);
    RUN_TEST(string_strcmp_prefix);
    RUN_TEST(string_strncmp_zero);
    RUN_TEST(string_strncmp_shorter);
    RUN_TEST(string_strchr_missing);
    RUN_TEST(string_strchr_first);
    RUN_TEST(string_strchr_nul);
    RUN_TEST(string_strrchr_nul);
    RUN_TEST(string_strrchr_single);
    RUN_TEST(string_strcspn_empty_set);
    RUN_TEST(string_strcspn_empty_str);
    RUN_TEST(string_strtok_single);
    RUN_TEST(string_strtok_leading_delims);
    RUN_TEST(string_strsep_empty_middle);
    RUN_TEST(string_strsep_no_delim);
    RUN_TEST(string_strrev_empty);
    RUN_TEST(string_strrev_even);
    RUN_TEST(string_stoupper_already);
    RUN_TEST(string_stolower_already);
    RUN_TEST(string_strerror_enoent);

    RUN_TEST(stdlib_atoi_plus);
    RUN_TEST(stdlib_atoi_minus_zero);
    RUN_TEST(stdlib_atoi_trailing_space);
    RUN_TEST(stdlib_atol_plus);
    RUN_TEST(stdlib_atol_spaces);
    RUN_TEST(stdlib_atof_whole);
    RUN_TEST(stdlib_atof_leading_space);
    RUN_TEST(stdlib_itoa_octal);
    RUN_TEST(stdlib_itoa_binary);
    RUN_TEST(stdlib_itoa_invalid_base);
    RUN_TEST(stdlib_strtol_base8);
    RUN_TEST(stdlib_strtol_negative_hex);
    RUN_TEST(stdlib_strtol_plus_sign);
    RUN_TEST(stdlib_strtol_no_digits_endptr);
    RUN_TEST(stdlib_strtoul_base0_octal);
    RUN_TEST(stdlib_strtoul_base0_hex);
    RUN_TEST(stdlib_strtoumax_decimal);
    RUN_TEST(stdlib_strtoimax_endptr);
    RUN_TEST(stdlib_rand_two_sequence_repro);
    RUN_TEST(stdlib_bsearch_first);
    RUN_TEST(stdlib_bsearch_last);
    RUN_TEST(stdlib_qsort_reverse);
    RUN_TEST(stdlib_qsort_duplicates);
    RUN_TEST(stdlib_labs_large);
    RUN_TEST(stdlib_div_exact);
    RUN_TEST(stdlib_ldiv_exact);
    RUN_TEST(stdlib_malloc_one);
    RUN_TEST(stdlib_calloc_two_by_two);
    RUN_TEST(stdlib_splitpath_lowercase_normalizes);
    RUN_TEST(stdlib_nltype_set_lfcr);

    RUN_TEST(math_fabs_neg_zero);
    RUN_TEST(math_ceil_zero);
    RUN_TEST(math_floor_zero);
    RUN_TEST(math_sqrt_fraction);
    RUN_TEST(math_sin_negative);
    RUN_TEST(math_cos_even);
    RUN_TEST(math_tan_negative);
    RUN_TEST(math_cot_negative);
    RUN_TEST(math_exp_two);
    RUN_TEST(math_log10_fraction);
    RUN_TEST(math_pow_zero_power);
    RUN_TEST(math_ldexp_zero);
    RUN_TEST(math_modf_integer);
    RUN_TEST(math_sin_zero);
    RUN_TEST(math_cos_zero);
    RUN_TEST(math_sqrt_one);
    RUN_TEST(math_exp_log_three);
    RUN_TEST(math_pow_one_any);

    if (g_failures == 0) {
        printf("PASS all %d tests\r\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\r\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
