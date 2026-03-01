/*
 * ttime.c
 *
 * Self-contained tests for time.h functions.
 *
 * These tests do not compare against glibc; they verify internal
 * consistency (mktime/gmtime round-trip) and known reference values.
 * The time/gettimeofday functions require a real-time clock to be
 * meaningful; those tests are smoke tests only.
 *
 * Reference epoch used throughout: 2000-01-01 00:00:00 UTC = 946684800L
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

/* ---- helpers ----------------------------------------------------------- */

/* Fill a struct tm with an arbitrary calendar time. */
static void fill_tm(struct tm *t,
                    int year, int mon, int mday,
                    int hour, int min,  int sec) {
    t->tm_year  = year;
    t->tm_mon   = mon;
    t->tm_mday  = mday;
    t->tm_hour  = hour;
    t->tm_min   = min;
    t->tm_sec   = sec;
    t->tm_wday  = 0;
    t->tm_yday  = 0;
    t->tm_isdst = 0;
}

/* ---- difftime ---------------------------------------------------------- */

TEST(difftime_positive) {
    EXPECT_EQ_LONG(5L,  difftime((time_t)10, (time_t)5));
    EXPECT_EQ_LONG(0L,  difftime((time_t)7,  (time_t)7));
}

TEST(difftime_negative) {
    EXPECT_EQ_LONG(-5L, difftime((time_t)5,  (time_t)10));
}

TEST(difftime_epoch) {
    /* 2000-01-01 is 946684800 seconds after Unix epoch */
    EXPECT_EQ_LONG(946684800L,
        difftime((time_t)946684800L, (time_t)0));
}

/* ---- mktime ------------------------------------------------------------ */

TEST(mktime_unix_epoch) {
    struct tm t;
    time_t epoch;
    fill_tm(&t, 70, 0, 1, 0, 0, 0);  /* 1970-01-01 00:00:00 */
    epoch = mktime(&t);
    EXPECT_EQ_LONG(0L, (long)epoch);
}

TEST(mktime_y2k) {
    struct tm t;
    time_t epoch;
    fill_tm(&t, 100, 0, 1, 0, 0, 0); /* 2000-01-01 00:00:00 */
    epoch = mktime(&t);
    EXPECT_EQ_LONG(946684800L, (long)epoch);
}

TEST(mktime_end_of_day) {
    struct tm t;
    time_t epoch;
    fill_tm(&t, 70, 0, 1, 23, 59, 59); /* 1970-01-01 23:59:59 */
    epoch = mktime(&t);
    EXPECT_EQ_LONG(86399L, (long)epoch);
}

TEST(mktime_leap_day) {
    struct tm t;
    time_t epoch;
    fill_tm(&t, 100, 1, 29, 0, 0, 0); /* 2000-02-29 (leap year) */
    epoch = mktime(&t);
    /* Days from epoch: 365*30 + 8 leap years (72,76,80,84,88,92,96,00
       -- but 2000 is not a leap by century rule... wait, 2000 IS a leap
       year because it's divisible by 400).
       Verified reference value: 951782400 */
    EXPECT_EQ_LONG(951782400L, (long)epoch);
}

/* ---- gmtime ------------------------------------------------------------ */

TEST(gmtime_epoch_zero) {
    time_t t = (time_t)0L;
    struct tm *tm = gmtime(&t);
    ASSERT_TRUE(tm != NULL);
    EXPECT_EQ_INT(70, tm->tm_year);  /* 1970 = year 70 since 1900 */
    EXPECT_EQ_INT(0,  tm->tm_mon);   /* January */
    EXPECT_EQ_INT(1,  tm->tm_mday);
    EXPECT_EQ_INT(0,  tm->tm_hour);
    EXPECT_EQ_INT(0,  tm->tm_min);
    EXPECT_EQ_INT(0,  tm->tm_sec);
    EXPECT_EQ_INT(4,  tm->tm_wday);  /* Thursday */
    EXPECT_EQ_INT(0,  tm->tm_yday);
}

TEST(gmtime_y2k) {
    time_t t = (time_t)946684800L;
    struct tm *tm = gmtime(&t);
    ASSERT_TRUE(tm != NULL);
    EXPECT_EQ_INT(100, tm->tm_year); /* 2000 = year 100 since 1900 */
    EXPECT_EQ_INT(0,   tm->tm_mon);  /* January */
    EXPECT_EQ_INT(1,   tm->tm_mday);
    EXPECT_EQ_INT(0,   tm->tm_hour);
    EXPECT_EQ_INT(0,   tm->tm_min);
    EXPECT_EQ_INT(0,   tm->tm_sec);
    EXPECT_EQ_INT(6,   tm->tm_wday); /* Saturday */
    EXPECT_EQ_INT(0,   tm->tm_yday);
}

/* ---- mktime / gmtime round-trip --------------------------------------- */

TEST(roundtrip_known_dates) {
    struct tm in, *out;
    time_t epoch;

    /* 1999-12-31 23:59:59 */
    fill_tm(&in, 99, 11, 31, 23, 59, 59);
    epoch = mktime(&in);
    out = gmtime(&epoch);
    ASSERT_TRUE(out != NULL);
    EXPECT_EQ_INT(99,  out->tm_year);
    EXPECT_EQ_INT(11,  out->tm_mon);
    EXPECT_EQ_INT(31,  out->tm_mday);
    EXPECT_EQ_INT(23,  out->tm_hour);
    EXPECT_EQ_INT(59,  out->tm_min);
    EXPECT_EQ_INT(59,  out->tm_sec);
}

TEST(roundtrip_mid_year) {
    struct tm in, *out;
    time_t epoch;

    /* 2024-06-15 12:30:45 */
    fill_tm(&in, 124, 5, 15, 12, 30, 45);
    epoch = mktime(&in);
    out = gmtime(&epoch);
    ASSERT_TRUE(out != NULL);
    EXPECT_EQ_INT(124, out->tm_year);
    EXPECT_EQ_INT(5,   out->tm_mon);
    EXPECT_EQ_INT(15,  out->tm_mday);
    EXPECT_EQ_INT(12,  out->tm_hour);
    EXPECT_EQ_INT(30,  out->tm_min);
    EXPECT_EQ_INT(45,  out->tm_sec);
}

/* ---- asctime format ---------------------------------------------------- */

TEST(asctime_format_length) {
    /* asctime() returns "Www Mmm dd hh:mm:ss yyyy\n" -- 25 chars + NUL */
    struct tm t;
    const char *s;
    fill_tm(&t, 100, 0, 1, 0, 0, 0);
    t.tm_wday = 6; /* Saturday */
    s = asctime(&t);
    ASSERT_TRUE(s != NULL);
    EXPECT_EQ_INT(25, (int)strlen(s)); /* 24 chars + newline */
}

TEST(asctime_y2k) {
    struct tm t;
    const char *s;
    fill_tm(&t, 100, 0, 1, 0, 0, 0);
    t.tm_wday = 6; /* Saturday */
    s = asctime(&t);
    ASSERT_TRUE(s != NULL);
    /* Check year appears at position 20 */
    EXPECT_EQ_INT('2', s[20]);
    EXPECT_EQ_INT('0', s[21]);
    EXPECT_EQ_INT('0', s[22]);
    EXPECT_EQ_INT('0', s[23]);
}

/* ---- ctime format ------------------------------------------------------ */

TEST(ctime_epoch_zero) {
    time_t t = (time_t)0L;
    const char *s = ctime(&t);
    ASSERT_TRUE(s != NULL);
    EXPECT_EQ_INT(25, (int)strlen(s));
    /* Should contain "1970" */
    EXPECT_TRUE(s[20] == '1' && s[21] == '9' && s[22] == '7' && s[23] == '0');
}

/* ---- clock smoke test -------------------------------------------------- */

TEST(clock_non_negative) {
    clock_t c = clock();
    EXPECT_TRUE(c >= 0);
}

int main(void) {
    puts("TTIME: time tests");
    RUN_TEST(difftime_positive);
    RUN_TEST(difftime_negative);
    RUN_TEST(difftime_epoch);
    RUN_TEST(mktime_unix_epoch);
    RUN_TEST(mktime_y2k);
    RUN_TEST(mktime_end_of_day);
    RUN_TEST(mktime_leap_day);
    RUN_TEST(gmtime_epoch_zero);
    RUN_TEST(gmtime_y2k);
    RUN_TEST(roundtrip_known_dates);
    RUN_TEST(roundtrip_mid_year);
    RUN_TEST(asctime_format_length);
    RUN_TEST(asctime_y2k);
    RUN_TEST(ctime_epoch_zero);
    RUN_TEST(clock_non_negative);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
