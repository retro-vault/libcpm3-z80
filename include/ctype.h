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
#ifndef __CTYPE_H__
#define __CTYPE_H__

#include <stdbool.h>

/* True if char is a letter. */
extern bool isalpha(int c);

/* True if char is white space. */
extern bool isspace(int c);

/* True if char is punctuation. */
extern bool ispunct(int c);

/* Returns char, converted to lowercase. */
extern int tolower(int c);

/* Return char converted to uppercase. */
extern int toupper(int c);

/* True if char is a digit. */
extern bool isdigit(int c);

#endif /* __CTYPE_H__ */