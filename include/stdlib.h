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

/* How console functions interpret \n? As \n or as \r\n? */
#define NL_LF       0
#define NL_CRLF     1
#define NL_LFCR     2
extern char nltype;

/* Non standard extension, the name of the platform on
   which library was build i.e. z80-none or z80-partner.
   This is changed when adding PLATFORM=name to make call. */
extern char *libplatform;

/* Non standard extension, running program name.
   Used for argv[0]. */
extern char *progname;

/* Exit application. */
extern void exit(int status);

/* Absolute value. */
extern int abs (int i);

/* Covert ascii to integer. */
extern int atoi(const char *str);

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
extern void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*));

/* Non standard extension, this is a hook, called just
   after intialization of the Standard library */
extern void libinit();

/* Non standard extension: path parser. 
   Supported path formats are:
   [<drive>:]filename.typ[[g]<user area>]
   Returns 0 for success */
#define MAX_DRIVE   1
#define MAX_FNAME   8
#define MAX_EXT     3
extern int splitpath(
   const char *path,
   char *drive,
   int *user,
   char *fname,
   char *ext
);

#endif /* __STDLIB_H__ */