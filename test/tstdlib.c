/*
 * tstdlib.c
 *
 * Tests for stdlib.h general utility functions.
 *
 * Notes:
 *  - On SDCC Z80, int is 16-bit (-32768..32767). atoi test values stay
 *    within that range. strtol/strtoul use 32-bit long.
 *  - malloc/calloc/free tests use small allocations that fit in the
 *    default heap.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <platform.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

static int int_cmp(const void *a, const void *b);

/* ---- abs --------------------------------------------------------------- */

TEST(abs_values) {
    EXPECT_EQ_INT(5,  abs(5));
    EXPECT_EQ_INT(5,  abs(-5));
    EXPECT_EQ_INT(0,  abs(0));
    EXPECT_EQ_INT(32767, abs(32767));
    EXPECT_EQ_INT(32767, abs(-32767));
}

/* ---- atoi -------------------------------------------------------------- */

TEST(atoi_decimal) {
    EXPECT_EQ_INT(0,     atoi("0"));
    EXPECT_EQ_INT(42,    atoi("42"));
    EXPECT_EQ_INT(-42,   atoi("-42"));
    EXPECT_EQ_INT(32767, atoi("32767"));   /* INT_MAX for 16-bit */
    EXPECT_EQ_INT(1,     atoi("   1"));    /* leading spaces */
    EXPECT_EQ_INT(12,    atoi("12abc"));   /* stops at non-digit */
}

/* ---- itoa -------------------------------------------------------------- */

TEST(itoa_decimal) {
    char buf[8];
    EXPECT_EQ_STR("0",    itoa(0,    buf, 10));
    EXPECT_EQ_STR("42",   itoa(42,   buf, 10));
    EXPECT_EQ_STR("-42",  itoa(-42,  buf, 10));
    EXPECT_EQ_STR("1000", itoa(1000, buf, 10));
}

TEST(itoa_hex) {
    char buf[8];
    EXPECT_EQ_STR("0",  itoa(0,    buf, 16));
    EXPECT_EQ_STR("ff", itoa(255,  buf, 16));
    EXPECT_EQ_STR("1a", itoa(26,   buf, 16));
}

/* ---- strtol ------------------------------------------------------------ */

TEST(strtol_decimal) {
    char *end;
    EXPECT_EQ_LONG(0L,      strtol("0",    &end, 10));
    EXPECT_EQ_LONG(12345L,  strtol("12345",&end, 10));
    EXPECT_EQ_LONG(-9999L,  strtol("-9999",&end, 10));
}

TEST(strtol_hex) {
    char *end;
    EXPECT_EQ_LONG(255L,  strtol("ff",  &end, 16));
    EXPECT_EQ_LONG(255L,  strtol("FF",  &end, 16));
    EXPECT_EQ_LONG(255L,  strtol("0xff",&end, 16));
    EXPECT_EQ_LONG(256L,  strtol("100", &end, 16));
}

TEST(strtol_endptr) {
    char *end;
    strtol("42xyz", &end, 10);
    EXPECT_EQ_STR("xyz", end);  /* end points past digits */
}

/* ---- strtoul ----------------------------------------------------------- */

TEST(strtoul_decimal) {
    char *end;
    EXPECT_EQ_LONG(0UL,     (long)strtoul("0",     &end, 10));
    EXPECT_EQ_LONG(65535UL, (long)strtoul("65535",  &end, 10));
}

TEST(strtoul_hex) {
    char *end;
    EXPECT_EQ_LONG(0xFFFFUL, (long)strtoul("ffff", &end, 16));
}

TEST(strtoimax_decimal) {
    char *end;
    EXPECT_EQ_LONG(12345L, (long)strtoimax("12345", &end, 10));
    EXPECT_EQ_LONG(-42L, (long)strtoimax("-42", &end, 10));
}

TEST(strtoumax_hex) {
    char *end;
    EXPECT_EQ_LONG(0x1234UL, (long)strtoumax("1234", &end, 16));
}

TEST(atol_decimal) {
    EXPECT_EQ_LONG(0L, atol("0"));
    EXPECT_EQ_LONG(123456L, atol("123456"));
    EXPECT_EQ_LONG(-42L, atol("-42"));
}

TEST(atof_decimal) {
    EXPECT_EQ_FLOAT(0.0f, atof("0"), 0.0001f);
    EXPECT_EQ_FLOAT(12.5f, atof("12.5"), 0.0001f);
    EXPECT_EQ_FLOAT(-3.25f, atof("-3.25"), 0.0001f);
}

/* ---- rand / srand ------------------------------------------------------ */

TEST(rand_in_range) {
    int i, r;
    srand(1);
    for (i = 0; i < 16; ++i) {
        r = rand();
        EXPECT_TRUE(r >= 0);    /* rand() must be non-negative */
    }
}

TEST(rand_reproducible) {
    int a, b;
    srand(42);
    a = rand();
    srand(42);
    b = rand();
    EXPECT_EQ_INT(a, b);  /* same seed → same first value */
}

TEST(bsearch_found_and_missing) {
    static const int arr[] = { 1, 3, 5, 7, 9, 11 };
    int key;
    int *found;

    key = 7;
    found = (int *)bsearch(&key, arr, 6, sizeof(arr[0]), int_cmp);
    ASSERT_TRUE(found != NULL);
    EXPECT_EQ_INT(7, *found);

    key = 6;
    found = (int *)bsearch(&key, arr, 6, sizeof(arr[0]), int_cmp);
    EXPECT_TRUE(found == NULL);
}

TEST(div_helpers) {
    div_t qr = div(17, 5);
    ldiv_t lqr = ldiv(123456L, 1000L);

    EXPECT_EQ_INT(3, qr.quot);
    EXPECT_EQ_INT(2, qr.rem);
    EXPECT_EQ_LONG(123L, lqr.quot);
    EXPECT_EQ_LONG(456L, lqr.rem);
}

TEST(labs_values) {
    EXPECT_EQ_LONG(0L, labs(0L));
    EXPECT_EQ_LONG(42L, labs(42L));
    EXPECT_EQ_LONG(42L, labs(-42L));
}

/* ---- qsort ------------------------------------------------------------- */

static int int_cmp(const void *a, const void *b) {
    return *(const int *)a - *(const int *)b;
}

TEST(qsort_integers) {
    int arr[] = { 5, 3, 8, 1, 9, 2, 7, 4, 6, 0 };
    int exp[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int i;
    qsort(arr, 10, sizeof(int), int_cmp);
    for (i = 0; i < 10; ++i)
        EXPECT_EQ_INT(exp[i], arr[i]);
}

TEST(qsort_single) {
    int arr[] = { 42 };
    qsort(arr, 1, sizeof(int), int_cmp);
    EXPECT_EQ_INT(42, arr[0]);
}

TEST(qsort_sorted) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int i;
    qsort(arr, 5, sizeof(int), int_cmp);
    for (i = 0; i < 5; ++i)
        EXPECT_EQ_INT(i + 1, arr[i]);
}

/* ---- malloc / calloc / free -------------------------------------------- */

TEST(malloc_basic) {
    void *p = malloc(16);
    ASSERT_TRUE(p != NULL);
    /* write and read back to verify the block is usable */
    memset(p, 0xAB, 16);
    EXPECT_EQ_INT(0xAB & 0xFF, (unsigned char)((char *)p)[0]);
    EXPECT_EQ_INT(0xAB & 0xFF, (unsigned char)((char *)p)[15]);
    free(p);
}

TEST(malloc_zero_returns_null_or_valid) {
    /* malloc(0) behaviour is implementation-defined; just ensure no crash */
    void *p = malloc(0);
    if (p != NULL)
        free(p);
}

TEST(calloc_zeroed) {
    char *p = (char *)calloc(8, 1);
    int i;
    ASSERT_TRUE(p != NULL);
    for (i = 0; i < 8; ++i)
        EXPECT_EQ_INT(0, p[i]);
    free(p);
}

TEST(calloc_overflow_returns_null) {
    /* num*size overflow must fail safely. */
    void *p = calloc((size_t)-1, 2);
    EXPECT_TRUE(p == NULL);
}

TEST(malloc_multiple_frees) {
    /* Allocate several blocks, free them -- no crash expected. */
    void *a = malloc(10);
    void *b = malloc(20);
    void *c = malloc(30);
    ASSERT_TRUE(a != NULL);
    ASSERT_TRUE(b != NULL);
    ASSERT_TRUE(c != NULL);
    free(b);
    free(a);
    free(c);
}

TEST(malloc_reuse_after_free) {
    void *a = malloc(32);
    ASSERT_TRUE(a != NULL);
    free(a);
    /* After freeing, another allocation of the same size should succeed. */
    void *b = malloc(32);
    ASSERT_TRUE(b != NULL);
    free(b);
}

TEST(malloc_enomem_sets_errno) {
    void *p;
    errno = 0;
    p = malloc((size_t)-1);
    EXPECT_TRUE(p == NULL);
    EXPECT_EQ_INT(ENOMEM, errno);
}

TEST(free_null_is_noop) {
    int old_errno = errno;
    free(NULL);
    EXPECT_EQ_INT(old_errno, errno);
}

/* ---- splitpath --------------------------------------------------------- */

TEST(splitpath_basic) {
    char drive[MAX_DRIVE + 1];
    int  user;
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    int  rc;

    rc = _splitpath("A:HELLO.TXT", drive, &user, fname, ext);
    EXPECT_EQ_INT(0, rc);
    EXPECT_EQ_STR("A", drive);
    EXPECT_EQ_STR("HELLO", fname);
    EXPECT_EQ_STR("TXT", ext);
}

TEST(splitpath_no_drive) {
    char drive[MAX_DRIVE + 1];
    int  user;
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    int  rc;

    rc = _splitpath("TEST.COM", drive, &user, fname, ext);
    EXPECT_EQ_INT(0, rc);
    EXPECT_EQ_STR("TEST", fname);
    EXPECT_EQ_STR("COM", ext);
}

TEST(splitpath_with_user_area) {
    char drive[MAX_DRIVE + 1];
    int  user;
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    int  rc;

    rc = _splitpath("B:NAME.BIN[15]", drive, &user, fname, ext);
    EXPECT_EQ_INT(0, rc);
    EXPECT_EQ_STR("B", drive);
    EXPECT_EQ_INT(15, user);
    EXPECT_EQ_STR("NAME", fname);
    EXPECT_EQ_STR("BIN", ext);
}

TEST(splitpath_invalid_too_long_name) {
    char drive[MAX_DRIVE + 1];
    int  user;
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    int  rc;

    rc = _splitpath("ABCDEFGHI.TXT", drive, &user, fname, ext);
    EXPECT_EQ_INT(-1, rc);
}

TEST(nltype_roundtrip) {
    volatile char *p = &nltype;
    char old = *p;
    *p = NL_CRLF;
    { volatile int _expected = NL_CRLF; EXPECT_EQ_INT(_expected, *p); }
    *p = old;
}

int main(void) {
    puts("TSTDLIB: stdlib tests");
    RUN_TEST(abs_values);
    RUN_TEST(atoi_decimal);
    RUN_TEST(itoa_decimal);
    RUN_TEST(itoa_hex);
    RUN_TEST(strtol_decimal);
    RUN_TEST(strtol_hex);
    RUN_TEST(strtol_endptr);
    RUN_TEST(strtoul_decimal);
    RUN_TEST(strtoul_hex);
    RUN_TEST(strtoimax_decimal);
    RUN_TEST(strtoumax_hex);
    RUN_TEST(atol_decimal);
    RUN_TEST(atof_decimal);
    RUN_TEST(rand_in_range);
    RUN_TEST(rand_reproducible);
    RUN_TEST(bsearch_found_and_missing);
    RUN_TEST(div_helpers);
    RUN_TEST(labs_values);
    RUN_TEST(qsort_integers);
    RUN_TEST(qsort_single);
    RUN_TEST(qsort_sorted);
    RUN_TEST(malloc_basic);
    RUN_TEST(malloc_zero_returns_null_or_valid);
    RUN_TEST(calloc_zeroed);
    RUN_TEST(calloc_overflow_returns_null);
    RUN_TEST(malloc_multiple_frees);
    RUN_TEST(malloc_reuse_after_free);
    RUN_TEST(malloc_enomem_sets_errno);
    RUN_TEST(free_null_is_noop);
    RUN_TEST(splitpath_basic);
    RUN_TEST(splitpath_no_drive);
    RUN_TEST(splitpath_with_user_area);
    RUN_TEST(splitpath_invalid_too_long_name);
    RUN_TEST(nltype_roundtrip);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
