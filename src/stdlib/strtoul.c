#include <stdlib/_stdlib.h>

#ifndef LEAN_AND_MEAN

const static char _cvt_in[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,           /* '0' - '9' */
    100, 100, 100, 100, 100, 100, 100,      /* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, /* 'A' - 'Z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35,
    100, 100, 100, 100, 100, 100,           /* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, /* 'a' - 'z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35};

unsigned long strtoul(char *string, char **end_ptr, int base)
{
    register char *p;
    register unsigned long int result = 0;
    register unsigned digit;
    int any_digits = 0;

    /* Skip any leading blanks. */
    p = string;
    while (isspace(*p))
    {
        p += 1;
    }
    if (base == 0)
    {
        if (*p == '0')
        {
            p += 1;
            if (*p == 'x')
            {
                p += 1;
                base = 16;
            }
            else
            {
                any_digits = 1;
                base = 8;
            }
        }
        else
            base = 10;
    }
    else if (base == 16)
    {
        if ((p[0] == '0') && (p[1] == 'x'))
        {
            p += 2;
        }
    }

    if (base == 8)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > 7)
            {
                break;
            }
            result = (result << 3) + digit;
            any_digits = 1;
        }
    }
    else if (base == 10)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > 9)
            {
                break;
            }
            result = (10 * result) + digit;
            any_digits = 1;
        }
    }
    else if (base == 16)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > ('z' - '0'))
            {
                break;
            }
            digit = _cvt_in[digit];
            if (digit > 15)
            {
                break;
            }
            result = (result << 4) + digit;
            any_digits = 1;
        }
    }
    else
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > ('z' - '0'))
            {
                break;
            }
            digit = _cvt_in[digit];
            if (digit >= base)
            {
                break;
            }
            result = result * base + digit;
            any_digits = 1;
        }
    }

    if (!any_digits)
        p = string;
    if (end_ptr != 0)
        *end_ptr = p;
    return result;
}

#endif /* LEAN_AND_MEAN */