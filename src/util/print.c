/*
 * print.c
 *
 * Standard C printf, fprintf, vfprintf functions.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 02.05.2021   tstih
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

void _outputchar(char **str, char c)
{
	if (str) {
		**str = c;
		++(*str);
	} else {
		putchar(c);
	}
}

enum flags {
	PAD_ZERO	= 1,
	PAD_RIGHT	= 2,
};

int _prints(char **out, const char *string, int width, int flags)
{
	int pc = 0, padchar = ' ';

	if (width > 0) {
		int len = (int)strlen(string);
		if (len >= width) width = 0;
		else width -= len;
		if (flags & PAD_ZERO)
			padchar = '0';
	}
	if (!(flags & PAD_RIGHT)) {
		for ( ; width > 0; --width) {
			_outputchar(out, padchar);
			++pc;
		}
	}
	for ( ; *string ; ++string) {
		_outputchar(out, *string);
		++pc;
	}
	for ( ; width > 0; --width) {
		_outputchar(out, padchar);
		++pc;
	}

	return pc;
}

/* SDCC on Z80 has no long long; long (32-bit) is the widest integer type. */
int _outputi(char **out, long i, int base, int sign, int width, int flags, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	char *s;
	int t, neg = 0, pc = 0;
	unsigned long u = (unsigned long)i;

	if (i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return _prints(out, print_buf, width, flags);
	}

	if (sign && base == 10 && i < 0) {
		neg = 1;
		u = (unsigned long)(-(long)i);
	}

	s = print_buf + PRINT_BUF_LEN - 1;
	*s = '\0';

	while (u) {
		t = (int)(u % (unsigned long)base);
		if (t >= 10)
			t += letbase - '0' - 10;
		*--s = t + '0';
		u /= (unsigned long)base;
	}

	if (neg) {
		if (width && (flags & PAD_ZERO)) {
			_outputchar(out, '-');
			++pc;
			--width;
		} else {
			*--s = '-';
		}
	}

	return pc + _prints(out, s, width, flags);
}

int _vsprintf(char **out, char *format, va_list ap)
{
	int width, flags;
	int pc = 0;
	char scr[2];
	union {
		char c;
		char *s;
		int i;
		unsigned int u;
		short hi;
		unsigned short hu;
		signed char hhi;
		unsigned char hhu;
		long li;
		unsigned long lu;
	} v;

	for (; *format != 0; format++) {
		if (*format == '%') {
			++format;
			width = flags = 0;
			if (*format == '\0')
				break;
			if (*format == '%')
				goto out;
			if (*format == '-') {
				++format;
				flags = PAD_RIGHT;
			}
			while (*format == '0') {
				++format;
				flags |= PAD_ZERO;
			}
			if (*format == '*') {
				width = va_arg(ap, int);
				format++;
			} else {
				for ( ; *format >= '0' && *format <= '9'; ++format) {
					width *= 10;
					width += *format - '0';
				}
			}
			switch (*format) {
				case 'd':
					v.i = va_arg(ap, int);
					pc += _outputi(out, v.i, 10, 1, width, flags, 'a');
					break;

				case 'u':
					v.u = va_arg(ap, unsigned int);
					pc += _outputi(out, v.u, 10, 0, width, flags, 'a');
					break;

				case 'x':
					v.u = va_arg(ap, unsigned int);
					pc += _outputi(out, v.u, 16, 0, width, flags, 'a');
					break;

				case 'X':
					v.u = va_arg(ap, unsigned int);
					pc += _outputi(out, v.u, 16, 0, width, flags, 'A');
					break;

				case 'c':
					v.c = (char)va_arg(ap, int);
					scr[0] = v.c;
					scr[1] = '\0';
					pc += _prints(out, scr, width, flags);
					break;

				case 's':
					v.s = va_arg(ap, char *);
                    #pragma disable_warning 196
					pc += _prints(out, v.s ? v.s : "(null)", width, flags);
					break;

				case 'l':
					++format;
					switch (*format) {
						case 'd':
							v.li = va_arg(ap, long);
							pc += _outputi(out, v.li, 10, 1, width, flags, 'a');
							break;
						case 'u':
							v.lu = va_arg(ap, unsigned long);
							pc += _outputi(out, v.lu, 10, 0, width, flags, 'a');
							break;
						case 'x':
							v.lu = va_arg(ap, unsigned long);
							pc += _outputi(out, v.lu, 16, 0, width, flags, 'a');
							break;
						case 'X':
							v.lu = va_arg(ap, unsigned long);
							pc += _outputi(out, v.lu, 16, 0, width, flags, 'A');
							break;
						default:
							break;
					}
					break;

				case 'h':
					++format;
					if (*format == 'h') {
						++format;
						switch (*format) {
							case 'd':
								v.hhi = (signed char)va_arg(ap, int);
								pc += _outputi(out, v.hhi, 10, 1, width, flags, 'a');
								break;
							case 'u':
								v.hhu = (unsigned char)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hhu, 10, 0, width, flags, 'a');
								break;
							case 'x':
								v.hhu = (unsigned char)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hhu, 16, 0, width, flags, 'a');
								break;
							case 'X':
								v.hhu = (unsigned char)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hhu, 16, 0, width, flags, 'A');
								break;
							default:
								break;
						}
					} else {
						switch (*format) {
							case 'd':
								v.hi = (short)va_arg(ap, int);
								pc += _outputi(out, v.hi, 10, 1, width, flags, 'a');
								break;
							case 'u':
								v.hu = (unsigned short)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hu, 10, 0, width, flags, 'a');
								break;
							case 'x':
								v.hu = (unsigned short)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hu, 16, 0, width, flags, 'a');
								break;
							case 'X':
								v.hu = (unsigned short)va_arg(ap, unsigned int);
								pc += _outputi(out, v.hu, 16, 0, width, flags, 'A');
								break;
							default:
								break;
						}
					}
					break;

				default:
					break;
			}
		} else {
out:
			_outputchar(out, *format);
			++pc;
		}
	}
	if (out) **out = '\0';
	return pc;
}
