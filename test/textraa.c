/*
 * textraa.c
 *
 * Additional ctype and stdio formatting edge-case tests.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 10.03.2026   tstih
 *
 */
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

static int helper_vsprintf(char *buf, const char *fmt, ...)
{
    va_list ap;
    int rc;
    va_start(ap, fmt);
    rc = vsprintf(buf, fmt, ap);
    va_end(ap);
    return rc;
}

#define DEF_BOOL_TEST(name, expr) \
    TEST(name) { EXPECT_TRUE((expr)); }

#define DEF_INT_TEST(name, exp, expr) \
    TEST(name) { EXPECT_EQ_INT((exp), (expr)); }

#define DEF_SPRINTF0_TEST(name, expected, fmt) \
    TEST(name) { \
        char buf[64]; \
        sprintf(buf, (fmt)); \
        EXPECT_EQ_STR((expected), buf); \
    }

#define DEF_SPRINTF_TEST(name, expected, fmt, value) \
    TEST(name) { \
        char buf[64]; \
        sprintf(buf, (fmt), (value)); \
        EXPECT_EQ_STR((expected), buf); \
    }

/* ---- ctype ------------------------------------------------------------ */

DEF_BOOL_TEST(ctype_alpha_a, isalpha('a'))
DEF_BOOL_TEST(ctype_alpha_Z, isalpha('Z'))
DEF_BOOL_TEST(ctype_alpha_digit_false, !isalpha('7'))
DEF_BOOL_TEST(ctype_alpha_punct_false, !isalpha('!'))
DEF_BOOL_TEST(ctype_alnum_A, isalnum('A'))
DEF_BOOL_TEST(ctype_alnum_9, isalnum('9'))
DEF_BOOL_TEST(ctype_alnum_space_false, !isalnum(' '))
DEF_BOOL_TEST(ctype_digit_0, isdigit('0'))
DEF_BOOL_TEST(ctype_digit_9, isdigit('9'))
DEF_BOOL_TEST(ctype_digit_slash_false, !isdigit('/'))
DEF_BOOL_TEST(ctype_digit_colon_false, !isdigit(':'))
DEF_BOOL_TEST(ctype_space_tab, isspace('\t'))
DEF_BOOL_TEST(ctype_space_cr, isspace('\r'))
DEF_BOOL_TEST(ctype_space_A_false, !isspace('A'))
DEF_BOOL_TEST(ctype_punct_bang, ispunct('!'))
DEF_BOOL_TEST(ctype_punct_tilde, ispunct('~'))
DEF_BOOL_TEST(ctype_punct_A_false, !ispunct('A'))
DEF_BOOL_TEST(ctype_cntrl_nul, iscntrl('\0'))
DEF_BOOL_TEST(ctype_cntrl_lf, iscntrl('\n'))
DEF_BOOL_TEST(ctype_cntrl_A_false, !iscntrl('A'))
DEF_BOOL_TEST(ctype_graph_A, isgraph('A'))
DEF_BOOL_TEST(ctype_graph_tilde, isgraph('~'))
DEF_BOOL_TEST(ctype_graph_space_false, !isgraph(' '))
DEF_BOOL_TEST(ctype_lower_a, islower('a'))
DEF_BOOL_TEST(ctype_lower_Z_false, !islower('Z'))
DEF_BOOL_TEST(ctype_upper_Z, isupper('Z'))
DEF_BOOL_TEST(ctype_upper_a_false, !isupper('a'))
DEF_BOOL_TEST(ctype_print_space, isprint(' '))
DEF_BOOL_TEST(ctype_print_tilde, isprint('~'))
DEF_BOOL_TEST(ctype_print_lf_false, !isprint('\n'))
DEF_BOOL_TEST(ctype_xdigit_0, isxdigit('0'))
DEF_BOOL_TEST(ctype_xdigit_f, isxdigit('f'))
DEF_BOOL_TEST(ctype_xdigit_F, isxdigit('F'))
DEF_BOOL_TEST(ctype_xdigit_g_false, !isxdigit('g'))
DEF_INT_TEST(ctype_tolower_A, 'a', tolower('A'))
DEF_INT_TEST(ctype_toupper_z, 'Z', toupper('z'))

/* ---- formatting ------------------------------------------------------- */

DEF_SPRINTF0_TEST(fmt_percent, "%", "%%")
DEF_SPRINTF_TEST(fmt_string_width, "   hi", "%5s", "hi")
DEF_SPRINTF_TEST(fmt_string_left, "hi   ", "%-5s", "hi")
DEF_SPRINTF_TEST(fmt_int_zero, "0", "%d", 0)
DEF_SPRINTF_TEST(fmt_int_width, "   42", "%5d", 42)
DEF_SPRINTF_TEST(fmt_neg_zero, "0", "%d", -0)
DEF_SPRINTF_TEST(fmt_oct_plain, "123", "%o", 0123)
DEF_SPRINTF_TEST(fmt_oct_short, "123", "%ho", (unsigned short)0123)
DEF_SPRINTF_TEST(fmt_oct_char, "123", "%hho", (unsigned char)0123)
DEF_SPRINTF_TEST(fmt_hex_upper, "BEEF", "%X", 0xBEEF)
DEF_SPRINTF_TEST(fmt_hex_lower, "beef", "%x", 0xBEEF)
DEF_SPRINTF_TEST(fmt_long_dec, "123456", "%ld", 123456L)
DEF_SPRINTF_TEST(fmt_long_hex, "1abc", "%lx", 0x1abcl)
DEF_SPRINTF_TEST(fmt_i_plain, "-77", "%i", -77)
DEF_SPRINTF_TEST(fmt_i_short, "-77", "%hi", (short)-77)
DEF_SPRINTF_TEST(fmt_i_char, "-7", "%hhi", (signed char)-7)
DEF_SPRINTF_TEST(fmt_u_short, "65535", "%hu", (unsigned short)65535U)
DEF_SPRINTF_TEST(fmt_u_char, "255", "%hhu", (unsigned char)255U)
DEF_SPRINTF_TEST(fmt_x_char, "ab", "%hhx", (unsigned char)0xAB)
DEF_SPRINTF_TEST(fmt_X_short, "ABC", "%hX", (unsigned short)0x0ABC)
DEF_SPRINTF_TEST(fmt_char_width, "  A", "%3c", 'A')
DEF_SPRINTF_TEST(fmt_string_null, "(null)", "%s", (char *)NULL)
DEF_SPRINTF_TEST(fmt_empty_string, "", "%s", "")

TEST(fmt_two_values) {
    char buf[64];
    sprintf(buf, "%d:%x", 7, 0x2a);
    EXPECT_EQ_STR("7:2a", buf);
}

TEST(fmt_literal_prefix) {
    char buf[64];
    sprintf(buf, "v=%d", 9);
    EXPECT_EQ_STR("v=9", buf);
}

DEF_SPRINTF_TEST(fmt_long_u, "70000", "%lu", 70000UL)
DEF_SPRINTF_TEST(fmt_long_o, "34567", "%lo", 034567L)
DEF_SPRINTF_TEST(fmt_long_X, "BEEF", "%lX", 0xBEEFL)
DEF_SPRINTF_TEST(fmt_short_d_neg, "-123", "%hd", (short)-123)
DEF_SPRINTF_TEST(fmt_short_x, "2a", "%hx", (unsigned short)0x2a)
DEF_SPRINTF_TEST(fmt_short_o, "52", "%ho", (unsigned short)052)
DEF_SPRINTF_TEST(fmt_char_d_neg, "-12", "%hhd", (signed char)-12)
DEF_SPRINTF_TEST(fmt_char_u, "200", "%hhu", (unsigned char)200)
DEF_SPRINTF_TEST(fmt_char_X, "F0", "%hhX", (unsigned char)0xF0)
DEF_SPRINTF_TEST(fmt_zero_width_char, "Q", "%c", 'Q')
DEF_SPRINTF_TEST(fmt_zero_width_str, "abc", "%s", "abc")
DEF_SPRINTF_TEST(fmt_zero_pad_long, "00042", "%05ld", 42L)
DEF_SPRINTF_TEST(fmt_zero_pad_hex, "002a", "%04x", 0x2a)
DEF_SPRINTF_TEST(fmt_left_pad_int, "42   ", "%-5d", 42)
DEF_SPRINTF_TEST(fmt_left_pad_str, "x    ", "%-5s", "x")

TEST(fmt_combo_inttypes1) {
    char buf[64];
    sprintf(buf, "%" PRId8 " %" PRIu16 " %" PRIx32,
        (int8_t)-5, (uint16_t)17, (uint32_t)0x1234ul);
    EXPECT_EQ_STR("-5 17 1234", buf);
}

TEST(fmt_combo_inttypes2) {
    char buf[64];
    sprintf(buf, "%" PRIi16 " %" PRIo8 " %" PRIXMAX,
        (int16_t)-123, (uint8_t)012, (uintmax_t)0xBEEFul);
    EXPECT_EQ_STR("-123 12 BEEF", buf);
}

DEF_SPRINTF_TEST(fmt_large_u16, "65535", "%u", 65535U)
DEF_SPRINTF_TEST(fmt_large_x32, "dead", "%lx", 0xdeadul)
DEF_SPRINTF_TEST(fmt_small_o, "7", "%o", 7)
DEF_SPRINTF_TEST(fmt_pad_zero_short, "0021", "%04hu", (unsigned short)21)
DEF_SPRINTF_TEST(fmt_pad_zero_char, "007", "%03hhu", (unsigned char)7)

TEST(fmt_three_chars) {
    char buf[64];
    sprintf(buf, "%c%c%c", 'a', 'b', 'c');
    EXPECT_EQ_STR("abc", buf);
}

TEST(fmt_string_and_int) {
    char buf[64];
    sprintf(buf, "%s=%d", "n", 5);
    EXPECT_EQ_STR("n=5", buf);
}

DEF_SPRINTF_TEST(fmt_short_u_zero, "0", "%hu", (unsigned short)0)

TEST(fmt_return_len) {
    char buf[64];
    EXPECT_EQ_INT(6, helper_vsprintf(buf, "%s %d", "abc", 12));
    EXPECT_EQ_STR("abc 12", buf);
}

int main(void)
{
    puts("TEXTRAA: extra ctype/stdio tests");

    RUN_TEST(ctype_alpha_a);
    RUN_TEST(ctype_alpha_Z);
    RUN_TEST(ctype_alpha_digit_false);
    RUN_TEST(ctype_alpha_punct_false);
    RUN_TEST(ctype_alnum_A);
    RUN_TEST(ctype_alnum_9);
    RUN_TEST(ctype_alnum_space_false);
    RUN_TEST(ctype_digit_0);
    RUN_TEST(ctype_digit_9);
    RUN_TEST(ctype_digit_slash_false);
    RUN_TEST(ctype_digit_colon_false);
    RUN_TEST(ctype_space_tab);
    RUN_TEST(ctype_space_cr);
    RUN_TEST(ctype_space_A_false);
    RUN_TEST(ctype_punct_bang);
    RUN_TEST(ctype_punct_tilde);
    RUN_TEST(ctype_punct_A_false);
    RUN_TEST(ctype_cntrl_nul);
    RUN_TEST(ctype_cntrl_lf);
    RUN_TEST(ctype_cntrl_A_false);
    RUN_TEST(ctype_graph_A);
    RUN_TEST(ctype_graph_tilde);
    RUN_TEST(ctype_graph_space_false);
    RUN_TEST(ctype_lower_a);
    RUN_TEST(ctype_lower_Z_false);
    RUN_TEST(ctype_upper_Z);
    RUN_TEST(ctype_upper_a_false);
    RUN_TEST(ctype_print_space);
    RUN_TEST(ctype_print_tilde);
    RUN_TEST(ctype_print_lf_false);
    RUN_TEST(ctype_xdigit_0);
    RUN_TEST(ctype_xdigit_f);
    RUN_TEST(ctype_xdigit_F);
    RUN_TEST(ctype_xdigit_g_false);
    RUN_TEST(ctype_tolower_A);
    RUN_TEST(ctype_toupper_z);

    RUN_TEST(fmt_percent);
    RUN_TEST(fmt_string_width);
    RUN_TEST(fmt_string_left);
    RUN_TEST(fmt_int_zero);
    RUN_TEST(fmt_int_width);
    RUN_TEST(fmt_neg_zero);
    RUN_TEST(fmt_oct_plain);
    RUN_TEST(fmt_oct_short);
    RUN_TEST(fmt_oct_char);
    RUN_TEST(fmt_hex_upper);
    RUN_TEST(fmt_hex_lower);
    RUN_TEST(fmt_long_dec);
    RUN_TEST(fmt_long_hex);
    RUN_TEST(fmt_i_plain);
    RUN_TEST(fmt_i_short);
    RUN_TEST(fmt_i_char);
    RUN_TEST(fmt_u_short);
    RUN_TEST(fmt_u_char);
    RUN_TEST(fmt_x_char);
    RUN_TEST(fmt_X_short);
    RUN_TEST(fmt_char_width);
    RUN_TEST(fmt_string_null);
    RUN_TEST(fmt_empty_string);
    RUN_TEST(fmt_two_values);
    RUN_TEST(fmt_literal_prefix);
    RUN_TEST(fmt_long_u);
    RUN_TEST(fmt_long_o);
    RUN_TEST(fmt_long_X);
    RUN_TEST(fmt_short_d_neg);
    RUN_TEST(fmt_short_x);
    RUN_TEST(fmt_short_o);
    RUN_TEST(fmt_char_d_neg);
    RUN_TEST(fmt_char_u);
    RUN_TEST(fmt_char_X);
    RUN_TEST(fmt_zero_width_char);
    RUN_TEST(fmt_zero_width_str);
    RUN_TEST(fmt_zero_pad_long);
    RUN_TEST(fmt_zero_pad_hex);
    RUN_TEST(fmt_left_pad_int);
    RUN_TEST(fmt_left_pad_str);
    RUN_TEST(fmt_combo_inttypes1);
    RUN_TEST(fmt_combo_inttypes2);
    RUN_TEST(fmt_large_u16);
    RUN_TEST(fmt_large_x32);
    RUN_TEST(fmt_small_o);
    RUN_TEST(fmt_pad_zero_short);
    RUN_TEST(fmt_pad_zero_char);
    RUN_TEST(fmt_three_chars);
    RUN_TEST(fmt_string_and_int);
    RUN_TEST(fmt_short_u_zero);
    RUN_TEST(fmt_return_len);

    if (g_failures == 0) {
        printf("PASS all %d tests\r\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\r\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
