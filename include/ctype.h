/*
 * ctype.h
 *
 * Standard C header.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 02.05.2021   tstih
 *
 */
#ifndef LIBCPM3_CTYPE_H
#define LIBCPM3_CTYPE_H

#include <stdbool.h>

/* True if char is a letter. */
extern bool isalpha(int c);

/* True if char is alphanumeric. */
extern bool isalnum(int c);

/* True if char is control. */
extern bool iscntrl(int c);

/* True if char is graphical. */
extern bool isgraph(int c);

/* True if char is lowercase. */
extern bool islower(int c);

/* True if char is printable. */
extern bool isprint(int c);

/* True if char is white space. */
extern bool isspace(int c);

/* True if char is punctuation. */
extern bool ispunct(int c);

/* Returns char, converted to lowercase. */
extern int tolower(int c);

/* Return char converted to uppercase. */
extern int toupper(int c);

/* True if char is uppercase. */
extern bool isupper(int c);

/* True if char is a digit. */
extern bool isdigit(int c);

/* True if char is hexadecimal digit. */
extern bool isxdigit(int c);

#endif /* LIBCPM3_CTYPE_H */
