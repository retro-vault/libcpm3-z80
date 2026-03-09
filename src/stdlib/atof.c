/*
 * atof.c
 *
 * Convert a character string to a floating-point value.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib.h>
#include <ctype.h>

float atof(const char *str)
{
    float result;
    float frac;
    int sign;

    while (isspace(*str))
        ++str;

    sign = 1;
    if (*str == '-') {
        sign = -1;
        ++str;
    } else if (*str == '+') {
        ++str;
    }

    result = (float)strtol((char *)str, (char **)&str, 10);
    if (*str == '.') {
        ++str;
        frac = 0.1f;
        while (isdigit(*str)) {
            result += (*str - '0') * frac;
            frac *= 0.1f;
            ++str;
        }
    }

    return sign < 0 ? -result : result;
}
