/*
 * stdlib.h
 *
 * standard C header file
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.05.2021   tstih
 *
 */
#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <stddef.h>

/* Standard requires it here. */
#ifndef NULL
#define NULL 0
#endif /* NULL */

/* Exit application. */
extern void exit(int status);

/* Absolute value. */
extern int abs (int i);

/* Covert ascii to integer. */
extern int atoi(const char *str);

/* Return random number */
extern int rand(void);

/* Set random seed. */
extern void srand(unsigned int seed);

/* String to long using base. */
extern long strtol(char *nptr, char **endptr, int base);

/* String to unsigned long using base, */
extern unsigned long strtoul(const char *nptr, char **endptr, int base);

/* Memory allocation. */
extern void *malloc(size_t size);

/* Allocate zero initialized block. */
extern void *calloc (size_t num, size_t size);

/* Free allocated memory block. */
extern void free(void *ptr);

/* Quick sort */
extern void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

#endif /* __STDLIB_H__ */