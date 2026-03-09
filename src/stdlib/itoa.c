/*
 * itoa.c
 *
 * Convert an integer value to text in the requested numeric base.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdlib/_stdlib.h>

char *itoa(int num, char *str, int base) {
    unsigned int value;
    unsigned int rem;
    int i = 0;
    int isneg = 0;

    if (base < 2 || base > 16) {
        str[0] = '\0';
        return str;
    }

    if (num == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    if (base == 10 && num < 0) {
        isneg = 1;
        value = (unsigned int)(-(num + 1)) + 1u;
    } else {
        value = (unsigned int)num;
    }

    while (value != 0u) {
        rem = value % (unsigned int)base;
        str[i++] = (char)((rem > 9u) ? ((rem - 10u) + 'a') : (rem + '0'));
        value /= (unsigned int)base;
    }

    if (isneg) {
        str[i++] = '-';
    }
    str[i] = '\0';
    strrev(str, (size_t)i);
    return str;
}
