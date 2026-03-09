/*
 * tstdio.c
 *
 * Tests for stdio.h formatting and file I/O functions.
 *
 * File I/O tests create "TEST.TMP" in the current CP/M user area.
 * The file is not removed after the tests (CP/M has no remove()).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

/* Test file used for all file I/O tests. */
#define TEST_FILE "TEST.TMP"

static int helper_vsprintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    int rc;
    va_start(ap, fmt);
    rc = vsprintf(buf, fmt, ap);
    va_end(ap);
    return rc;
}

/* ---- sprintf ----------------------------------------------------------- */

TEST(sprintf_int) {
    char buf[16];
    sprintf(buf, "%d", 0);
    EXPECT_EQ_STR("0", buf);
    sprintf(buf, "%d", 42);
    EXPECT_EQ_STR("42", buf);
    sprintf(buf, "%d", -42);
    EXPECT_EQ_STR("-42", buf);
    sprintf(buf, "%d", 32767);
    EXPECT_EQ_STR("32767", buf);
}

TEST(sprintf_string) {
    char buf[32];
    sprintf(buf, "%s", "hello");
    EXPECT_EQ_STR("hello", buf);
    sprintf(buf, "[%s]", "hi");
    EXPECT_EQ_STR("[hi]", buf);
    sprintf(buf, "%s %s", "foo", "bar");
    EXPECT_EQ_STR("foo bar", buf);
}

TEST(sprintf_char) {
    char buf[8];
    sprintf(buf, "%c", 'A');
    EXPECT_EQ_STR("A", buf);
    sprintf(buf, "%c%c%c", 'h', 'i', '!');
    EXPECT_EQ_STR("hi!", buf);
}

TEST(sprintf_hex) {
    char buf[8];
    sprintf(buf, "%x", 0xFF);
    EXPECT_EQ_STR("ff", buf);
    sprintf(buf, "%x", 0);
    EXPECT_EQ_STR("0", buf);
    sprintf(buf, "%x", 256);
    EXPECT_EQ_STR("100", buf);
}

TEST(sprintf_mixed) {
    char buf[32];
    sprintf(buf, "%d-%s-%c", 7, "UP", 'Z');
    EXPECT_EQ_STR("7-UP-Z", buf);
}

/* ---- puts / putchar output (smoke tests -- no capture on CP/M) --------- */

TEST(puts_no_crash) {
    /* puts() must return a non-negative value on success. */
    int r = puts("puts smoke test");
    EXPECT_TRUE(r >= 0);
}

TEST(printf_no_crash) {
    int r = printf("printf smoke: %d %s\n", 1, "ok");
    EXPECT_TRUE(r > 0);
}

TEST(vprintf_no_crash) {
    char buf[32];
    int r = helper_vsprintf(buf, "%s %d", "fmt", 7);
    EXPECT_EQ_INT(5, r);
    EXPECT_EQ_STR("fmt 7", buf);
}

TEST(fputs_no_crash) {
    EXPECT_EQ_INT(0, fputs("fputs smoke test\n", stdout));
}

TEST(getchar_reads_console_char) {
    int c = getchar();
    EXPECT_EQ_INT('Q', c);

    /* Consume the rest of the input line so the next scripted input starts
       at the following line. */
    do {
        c = getchar();
    } while (c != '\r' && c != '\n' && c != EOF);
}

TEST(gets_reads_console_line) {
    char buf[32];
    char *r = gets(buf);
    ASSERT_TRUE(r != NULL);
    EXPECT_TRUE(strcmp(buf, "hello world") == 0 || strcmp(buf, "HELLO WORLD") == 0);
}

/* ---- file I/O ---------------------------------------------------------- */

TEST(fopen_write_read) {
    FILE *fp;
    char wbuf[] = "Hello CP/M";
    char rbuf[16];
    size_t n;

    /* Write. */
    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    n = fwrite(wbuf, 1, sizeof(wbuf), fp);
    EXPECT_EQ_INT((int)sizeof(wbuf), (int)n);
    fclose(fp);

    /* Read back. */
    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    memset(rbuf, 0, sizeof(rbuf));
    n = fread(rbuf, 1, sizeof(wbuf), fp);
    EXPECT_EQ_INT((int)sizeof(wbuf), (int)n);
    fclose(fp);

    EXPECT_EQ_INT(0, memcmp(wbuf, rbuf, sizeof(wbuf)));
}

TEST(fputs_fgets_roundtrip) {
    FILE *fp;
    char buf[16];

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT(0, fputs("line1\n", fp));
    EXPECT_EQ_INT(0, fflush(fp));
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    ASSERT_TRUE(fgets(buf, sizeof(buf), fp) != NULL);
    EXPECT_TRUE(strcmp(buf, "line1\n") == 0 || strcmp(buf, "line1") == 0);
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(fprintf_roundtrip) {
    FILE *fp;
    char buf[32];

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    EXPECT_TRUE(fprintf(fp, "%s:%d", "item", 42) > 0);
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    memset(buf, 0, sizeof(buf));
    ASSERT_TRUE(fgets(buf, sizeof(buf), fp) != NULL);
    EXPECT_EQ_STR("item:42", buf);
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(getc_putc_rewind) {
    FILE *fp;

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT('A', putc('A', fp));
    EXPECT_EQ_INT('B', putc('B', fp));
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT('A', getc(fp));
    EXPECT_EQ_INT('B', getc(fp));
    rewind(fp);
    EXPECT_EQ_INT('A', getc(fp));
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(fopen_bad_mode) {
    /* Open a non-existent file for reading -- must return NULL. */
    FILE *fp = fopen("NOFILE.TMP", "r");
    EXPECT_TRUE(fp == NULL);
}

TEST(fgetc_reads_chars) {
    FILE *fp;
    char wbuf[] = "ABC";
    int c;

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    fwrite(wbuf, 1, 3, fp);
    fclose(fp);

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    c = fgetc(fp);  EXPECT_EQ_INT('A', c);
    c = fgetc(fp);  EXPECT_EQ_INT('B', c);
    c = fgetc(fp);  EXPECT_EQ_INT('C', c);
    fclose(fp);
}

TEST(ungetc_and_getc_unlocked) {
    FILE *fp;
    char wbuf[] = "ABC";

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT(3, (int)fwrite(wbuf, 1, 3, fp));
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT('A', getc_unlocked(fp));
    EXPECT_EQ_INT('B', fgetc(fp));
    EXPECT_EQ_INT('B', ungetc('B', fp));
    EXPECT_EQ_INT('B', fgetc(fp));
    EXPECT_EQ_INT('C', getc(fp));
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(getw_reads_word) {
    FILE *fp;
    unsigned char wbuf[] = { 0x34, 0x12 };

    fp = fopen(TEST_FILE, "wb");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT(2, (int)fwrite(wbuf, 1, 2, fp));
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "rb");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT(0x1234, getw(fp));
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(fseek_ftell) {
    FILE *fp;
    char wbuf[] = "0123456789";
    long pos;

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    fwrite(wbuf, 1, 10, fp);
    fclose(fp);

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);

    /* Start at position 0. */
    pos = ftell(fp);
    EXPECT_EQ_LONG(0L, pos);

    /* Seek to byte 5. */
    EXPECT_EQ_INT(0, fseek(fp, 5L, SEEK_SET));
    pos = ftell(fp);
    EXPECT_EQ_LONG(5L, pos);

    /* Read one byte -- should be '5'. */
    EXPECT_EQ_INT('5', fgetc(fp));
    pos = ftell(fp);
    EXPECT_EQ_LONG(6L, pos);

    /* Seek forward 2 relative to current. */
    EXPECT_EQ_INT(0, fseek(fp, 2L, SEEK_CUR));
    pos = ftell(fp);
    EXPECT_EQ_LONG(8L, pos);
    EXPECT_EQ_INT('8', fgetc(fp));

    fclose(fp);
}

TEST(feof_detection) {
    FILE *fp;
    char wbuf[] = "X";

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    fwrite(wbuf, 1, 1, fp);
    fclose(fp);

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);

    EXPECT_TRUE(!feof(fp));
    fgetc(fp);          /* read the one character */
    fgetc(fp);          /* attempt read past end -- triggers EOF */
    EXPECT_TRUE(feof(fp));

    fclose(fp);
}

TEST(clearerr_resets_eof) {
    FILE *fp;
    char wbuf[] = "X";

    fp = fopen(TEST_FILE, "w");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT(1, (int)fwrite(wbuf, 1, 1, fp));
    EXPECT_EQ_INT(0, fclose(fp));

    fp = fopen(TEST_FILE, "r");
    ASSERT_TRUE(fp != NULL);
    EXPECT_EQ_INT('X', fgetc(fp));
    EXPECT_EQ_INT(EOF, fgetc(fp));
    EXPECT_TRUE(feof(fp));
    clearerr(fp);
    EXPECT_TRUE(!feof(fp));
    EXPECT_EQ_INT(0, ferror(fp));
    EXPECT_EQ_INT(0, fclose(fp));
}

TEST(tmpnam_and_tmpfile) {
    char name1[16];
    char name2[16];
    char buf[16];
    FILE *fp;

    ASSERT_TRUE(tmpnam(name1) != NULL);
    ASSERT_TRUE(tmpnam(name2) != NULL);
    EXPECT_TRUE(strcmp(name1, name2) != 0);

    fp = tmpfile();
    ASSERT_TRUE(fp != NULL);
    EXPECT_TRUE(fprintf(fp, "tmp") > 0);
    EXPECT_EQ_INT(0, fseek(fp, 0L, SEEK_SET));
    ASSERT_TRUE(fgets(buf, sizeof(buf), fp) != NULL);
    EXPECT_EQ_STR("tmp", buf);
    EXPECT_EQ_INT(0, fclose(fp));
}

int main(void) {
    printf("TSTDIO: stdio tests\r\n");
    RUN_TEST(sprintf_int);
    RUN_TEST(sprintf_string);
    RUN_TEST(sprintf_char);
    RUN_TEST(sprintf_hex);
    RUN_TEST(sprintf_mixed);
    RUN_TEST(puts_no_crash);
    RUN_TEST(printf_no_crash);
    RUN_TEST(vprintf_no_crash);
    RUN_TEST(fputs_no_crash);
    RUN_TEST(getchar_reads_console_char);
    RUN_TEST(gets_reads_console_line);
    RUN_TEST(fopen_write_read);
    RUN_TEST(fputs_fgets_roundtrip);
    RUN_TEST(fprintf_roundtrip);
    RUN_TEST(getc_putc_rewind);
    RUN_TEST(fopen_bad_mode);
    RUN_TEST(fgetc_reads_chars);
    RUN_TEST(ungetc_and_getc_unlocked);
    RUN_TEST(getw_reads_word);
    RUN_TEST(fseek_ftell);
    RUN_TEST(feof_detection);
    RUN_TEST(clearerr_resets_eof);
    RUN_TEST(tmpnam_and_tmpfile);
    if (g_failures == 0) {
        printf("PASS all %d tests\r\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\r\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
