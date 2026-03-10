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
#ifndef LIBCPM3_STDLIB_H
#define LIBCPM3_STDLIB_H

#include <stddef.h>

typedef struct {
    int quot;
    int rem;
} div_t;

typedef struct {
    long quot;
    long rem;
} ldiv_t;

/* Standard requires it here. */
#ifndef NULL
#define NULL 0
#endif /* NULL */

/* Exit application. */
extern void exit(int status);

/* Abort application. */
extern void abort(void);

/* Register exit handler. */
extern int atexit(void (*func)(void));

/* Absolute value. */
extern int abs (int i);

/* Covert ascii to integer. */
extern int atoi(const char *str);

/* Convert ascii to long. */
extern long atol(const char *str);

/* Convert ascii to float. */
extern float atof(const char *str);

/* Convert integer to ascii. */
extern char *itoa(int num, char *str, int base);

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
extern void qsort(void *base, size_t nitems, size_t size,
    int (*compar)(const void *, const void *));

/* Binary search */
extern void *bsearch(const void *key, const void *base, size_t nitems, size_t size,
    int (*compar)(const void *, const void *));

/* Long absolute value. */
extern long labs(long i);

/* Integer division. */
extern div_t div(int numer, int denom);

/* Long division. */
extern ldiv_t ldiv(long numer, long denom);

/* Non standard extension: path parser.
   Supported path formats are:
   [<drive>:]filename.typ[[g]<user area>]
   Returns 0 for success */
#define MAX_DRIVE   1
#define MAX_FNAME   8
#define MAX_EXT     3
extern int _splitpath(
   const char *path,
   char *drive,
   int *user,
   char *fname,
   char *ext
);

#endif /* LIBCPM3_STDLIB_H */
