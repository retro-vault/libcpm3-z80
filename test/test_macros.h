#ifndef LIBCPM3_TEST_MACROS_H
#define LIBCPM3_TEST_MACROS_H

#include <stdio.h>
#include <string.h>

extern int g_failures;
extern int g_tests_run;
extern int g_tests_failed;
extern const char *g_current_test;

#define TEST(name) static void test_##name(void)

#define RUN_TEST(name) \
    do { \
        int _fail_before = g_failures; \
        g_current_test = #name; \
        ++g_tests_run; \
        test_##name(); \
        if (g_failures == _fail_before) { \
            printf("PASS %s\r\n", #name); \
        } else { \
            ++g_tests_failed; \
            printf("FAIL %s (%d failures)\r\n", #name, g_failures - _fail_before); \
        } \
    } while (0)

#define EXPECT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL %s: %s:%d EXPECT_TRUE(%s)\r\n", g_current_test, __FILE__, __LINE__, #cond); \
            ++g_failures; \
        } \
    } while (0)

#define ASSERT_TRUE(cond) \
    do { \
        if (!(cond)) { \
            printf("FAIL %s: %s:%d ASSERT_TRUE(%s)\r\n", g_current_test, __FILE__, __LINE__, #cond); \
            ++g_failures; \
            return; \
        } \
    } while (0)

#define EXPECT_EQ_INT(exp, got) \
    do { \
        int _e = (int)(exp); \
        int _g = (int)(got); \
        if (_e != _g) { \
            printf("FAIL %s: %s:%d EXPECT_EQ_INT(%s,%s) expected=%d got=%d\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
        } \
    } while (0)

#define ASSERT_EQ_INT(exp, got) \
    do { \
        int _e = (int)(exp); \
        int _g = (int)(got); \
        if (_e != _g) { \
            printf("FAIL %s: %s:%d ASSERT_EQ_INT(%s,%s) expected=%d got=%d\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
            return; \
        } \
    } while (0)

#define EXPECT_EQ_LONG(exp, got) \
    do { \
        long _e = (long)(exp); \
        long _g = (long)(got); \
        if (_e != _g) { \
            printf("FAIL %s: %s:%d EXPECT_EQ_LONG(%s,%s) expected=%ld got=%ld\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
        } \
    } while (0)

#define ASSERT_EQ_LONG(exp, got) \
    do { \
        long _e = (long)(exp); \
        long _g = (long)(got); \
        if (_e != _g) { \
            printf("FAIL %s: %s:%d ASSERT_EQ_LONG(%s,%s) expected=%ld got=%ld\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
            return; \
        } \
    } while (0)

#define EXPECT_EQ_STR(exp, got) \
    do { \
        const char *_e = (exp); \
        const char *_g = (got); \
        if (strcmp(_e, _g) != 0) { \
            printf("FAIL %s: %s:%d EXPECT_EQ_STR(%s,%s) expected=\"%s\" got=\"%s\"\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
        } \
    } while (0)

#define ASSERT_EQ_STR(exp, got) \
    do { \
        const char *_e = (exp); \
        const char *_g = (got); \
        if (strcmp(_e, _g) != 0) { \
            printf("FAIL %s: %s:%d ASSERT_EQ_STR(%s,%s) expected=\"%s\" got=\"%s\"\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got, _e, _g); \
            ++g_failures; \
            return; \
        } \
    } while (0)

/* Compare two floats within a tolerance. Avoids %f in printf since
   the library printf does not support floating-point formatting. */
#define EXPECT_EQ_FLOAT(exp, got, tol) \
    do { \
        float _e = (float)(exp); \
        float _g = (float)(got); \
        float _d = _g - _e; \
        if (_d < 0.0f) _d = -_d; \
        if (_d > (float)(tol)) { \
            printf("FAIL %s: %s:%d EXPECT_EQ_FLOAT(%s, %s)\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got); \
            ++g_failures; \
        } \
    } while (0)

#define ASSERT_EQ_FLOAT(exp, got, tol) \
    do { \
        float _e = (float)(exp); \
        float _g = (float)(got); \
        float _d = _g - _e; \
        if (_d < 0.0f) _d = -_d; \
        if (_d > (float)(tol)) { \
            printf("FAIL %s: %s:%d ASSERT_EQ_FLOAT(%s, %s)\r\n", \
                g_current_test, __FILE__, __LINE__, #exp, #got); \
            ++g_failures; \
            return; \
        } \
    } while (0)

#endif
