/*
 * _print.c
 *
 * Internal formatting core implementing _vsprintf() and helper
 * routines used by the printf family.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

/* Max digits for unsigned long decimal (10) + sign + null.
   SDCC on Z80: long = 32-bit, no long long type. */
#define PRINT_BUF_LEN 12

extern int putchar(int c);

enum flags {
    PAD_ZERO  = 1,
    PAD_RIGHT = 2,
};

static void _outputchar(char **out, char c)
{
    if (out) {
        **out = c;
        ++(*out);
    } else {
        putchar((int)c);
    }
}

static int _prints(char **out, const char *string, int width, int flags)
{
    int pc = 0;
    int len;
    char padchar;

    if (!string)
        string = "(null)";

    if (width < 0)
        width = 0;

    if (flags & PAD_RIGHT)
        flags &= ~PAD_ZERO;

    padchar = (flags & PAD_ZERO) ? '0' : ' ';
    len = (int)strlen(string);

    if (len < width)
        width -= len;
    else
        width = 0;

    if (!(flags & PAD_RIGHT)) {
        while (width > 0) {
            _outputchar(out, padchar);
            ++pc;
            --width;
        }
    }

    while (*string) {
        _outputchar(out, *string);
        ++pc;
        ++string;
    }

    while (width > 0) {
        _outputchar(out, ' ');
        ++pc;
        --width;
    }

    return pc;
}

/* SDCC on Z80 has no long long; long (32-bit) is the widest integer type. */
static int _outputi(char **out, long value, int base, int sign,
                    int width, int flags, int letbase)
{
    char print_buf[PRINT_BUF_LEN];
    char *s;
    unsigned long u;
    int digit;
    int neg;
    int pc;

    s = print_buf + PRINT_BUF_LEN - 1;
    *s = '\0';
    neg = 0;
    pc = 0;

    if (flags & PAD_RIGHT)
        flags &= ~PAD_ZERO;

    u = (unsigned long)value;

    if (sign && base == 10 && value < 0) {
        neg = 1;
        u = 0UL - u;
    }

    if (u == 0) {
        *--s = '0';
    } else {
        while (u != 0) {
            digit = (int)(u % (unsigned long)base);
            if (digit >= 10)
                *--s = (char)(digit - 10 + letbase);
            else
                *--s = (char)(digit + '0');
            u /= (unsigned long)base;
        }
    }

    if (neg) {
        if ((flags & PAD_ZERO) && width > 0) {
            _outputchar(out, '-');
            ++pc;
            --width;
        } else {
            *--s = '-';
        }
    }

    return pc + _prints(out, s, width, flags);
}

int _vsprintf(char **out, const char *format, va_list ap)
{
    int width;
    int flags;
    int pc;
    char scr[2];

    pc = 0;

    while (*format) {
        if (*format != '%') {
            _outputchar(out, *format);
            ++pc;
            ++format;
            continue;
        }

        ++format;
        width = 0;
        flags = 0;

        if (*format == '\0')
            break;

        if (*format == '%') {
            _outputchar(out, '%');
            ++pc;
            ++format;
            continue;
        }

        if (*format == '-') {
            flags |= PAD_RIGHT;
            ++format;
        }

        while (*format == '0') {
            flags |= PAD_ZERO;
            ++format;
        }

        if (*format == '*') {
            width = va_arg(ap, int);
            ++format;
            if (width < 0) {
                flags |= PAD_RIGHT;
                width = -width;
            }
        } else {
            while (*format >= '0' && *format <= '9') {
                width = width * 10 + (*format - '0');
                ++format;
            }
        }

        switch (*format) {
            case 'd':
            case 'i':
                pc += _outputi(out, (long)va_arg(ap, int),
                    10, 1, width, flags, 'a');
                break;

            case 'o':
                pc += _outputi(out, (long)va_arg(ap, unsigned int),
                    8, 0, width, flags, 'a');
                break;

            case 'u':
                pc += _outputi(out, (long)va_arg(ap, unsigned int),
                    10, 0, width, flags, 'a');
                break;

            case 'x':
                pc += _outputi(out, (long)va_arg(ap, unsigned int),
                    16, 0, width, flags, 'a');
                break;

            case 'X':
                pc += _outputi(out, (long)va_arg(ap, unsigned int),
                    16, 0, width, flags, 'A');
                break;

            case 'c':
                scr[0] = (char)va_arg(ap, int);
                scr[1] = '\0';
                pc += _prints(out, scr, width, flags);
                break;

            case 's':
                pc += _prints(out, va_arg(ap, char *), width, flags);
                break;

            case 'l':
                ++format;
                switch (*format) {
                    case 'd':
                    case 'i':
                        pc += _outputi(out, va_arg(ap, long),
                            10, 1, width, flags, 'a');
                        break;

                    case 'o':
                        pc += _outputi(out, (long)va_arg(ap, unsigned long),
                            8, 0, width, flags, 'a');
                        break;

                    case 'u':
                        pc += _outputi(out, (long)va_arg(ap, unsigned long),
                            10, 0, width, flags, 'a');
                        break;

                    case 'x':
                        pc += _outputi(out, (long)va_arg(ap, unsigned long),
                            16, 0, width, flags, 'a');
                        break;

                    case 'X':
                        pc += _outputi(out, (long)va_arg(ap, unsigned long),
                            16, 0, width, flags, 'A');
                        break;

                    default:
                        _outputchar(out, '%');
                        _outputchar(out, 'l');
                        ++pc;
                        ++pc;
                        if (*format) {
                            _outputchar(out, *format);
                            ++pc;
                        }
                        break;
                }
                break;

            case 'h':
                ++format;
                if (*format == 'h') {
                    ++format;
                    switch (*format) {
                        case 'd':
                        case 'i':
                            pc += _outputi(out,
                                (long)(signed char)va_arg(ap, int),
                                10, 1, width, flags, 'a');
                            break;

                        case 'o':
                            pc += _outputi(out,
                                (long)(unsigned char)
                                va_arg(ap, unsigned int),
                                8, 0, width, flags, 'a');
                            break;

                        case 'u':
                            pc += _outputi(out,
                                (long)(unsigned char)
                                va_arg(ap, unsigned int),
                                10, 0, width, flags, 'a');
                            break;

                        case 'x':
                            pc += _outputi(out,
                                (long)(unsigned char)
                                va_arg(ap, unsigned int),
                                16, 0, width, flags, 'a');
                            break;

                        case 'X':
                            pc += _outputi(out,
                                (long)(unsigned char)
                                va_arg(ap, unsigned int),
                                16, 0, width, flags, 'A');
                            break;

                        default:
                            _outputchar(out, '%');
                            _outputchar(out, 'h');
                            _outputchar(out, 'h');
                            pc += 3;
                            if (*format) {
                                _outputchar(out, *format);
                                ++pc;
                            }
                            break;
                    }
                } else {
                    switch (*format) {
                        case 'd':
                        case 'i':
                            pc += _outputi(out,
                                (long)(short)va_arg(ap, int),
                                10, 1, width, flags, 'a');
                            break;

                        case 'o':
                            pc += _outputi(out,
                                (long)(unsigned short)
                                va_arg(ap, unsigned int),
                                8, 0, width, flags, 'a');
                            break;

                        case 'u':
                            pc += _outputi(out,
                                (long)(unsigned short)
                                va_arg(ap, unsigned int),
                                10, 0, width, flags, 'a');
                            break;

                        case 'x':
                            pc += _outputi(out,
                                (long)(unsigned short)
                                va_arg(ap, unsigned int),
                                16, 0, width, flags, 'a');
                            break;

                        case 'X':
                            pc += _outputi(out,
                                (long)(unsigned short)
                                va_arg(ap, unsigned int),
                                16, 0, width, flags, 'A');
                            break;

                        default:
                            _outputchar(out, '%');
                            _outputchar(out, 'h');
                            pc += 2;
                            if (*format) {
                                _outputchar(out, *format);
                                ++pc;
                            }
                            break;
                    }
                }
                break;

            default:
                _outputchar(out, '%');
                ++pc;
                if (*format) {
                    _outputchar(out, *format);
                    ++pc;
                }
                break;
        }

        if (*format)
            ++format;
    }

    if (out)
        **out = '\0';

    return pc;
}
