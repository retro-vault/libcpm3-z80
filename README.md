![status.badge] [![language.badge]][language.url] [![standard.badge]][standard.url] [![license.badge]][license.url]

# Standard C library for CP/M 3 Z80

## Table of content

- [Introduction](#introduction)
- [Compiling the libcpm3-z80](#compiling-the-libcpm3-z80)
- [Compiling your CP/M program](#compiling-your-cpm-program)
- [Advanced libcpm3-z80 features](#advanced-libcpm3-z80-features)
  * [Platform dependant functions](#platform-dependant-functions)
      + [Injecting your platform dependant functions](#injecting-your-platform-dependant-functions)
- [What is implemented?](#what-is-implemented-)
    * [Non-standard extensions](#non-standard-extensions)
- [To Do](#to-do)

## Introduction

**libcpm3-z80** is a **portable**, **readable**, and **minimal** [ISO/IEC 9899:TC2](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf) *Standard C Library* for Digital Research's CP/M 3.

Implementing a standard library shouldn't be a daunting task. Unless the library immoderately aspires to target all architectures and all compilers by using sophisticated preprocessor directives and tricks, 
only known to god and a few earthlings.

**libcpm3-z80** is an attempt to provide a library, written in purest *C*, with a clear separation of platform independent and platform dependent code. To port it to your architecture you need to provide a handful of well documented platform specific functions that the standard requires and are not available in *CP/M*'s *BDOS*.


## Compiling the libcpm3-z80

You need a Linux with the **latest** version of *SDCC* development tools intalled.

Then get the repository by executing 

`git clone https://github.com/tstih/libcpm3-z80.git --recurse-submodules`

This will download *libcpm3-z80* and submodule [libsdcc-z80](https://github.com/tstih/libsdcc-z80). 

After that you can compile a basic version of *libcpm3-z80* by issuing a `make` command in root folder.

Make will produce three files in the `bin` folder.
 * `crt0cpm3-z80.rel` This is the C runtime start-up file.
 * `libcpm3-z80.lib` This is the CP/M 3 standard C library.
 * `libsdcc-z80.lib` This is the SDCC bare metal library.

You need to link all three with your CP/M program.

## Compiling your CP/M program

Check the `Makefile` in the `hello` sample folder.

## Advanced libcpm3-z80 features

The library was designed for *CP/M 3*, and uses *BDOS* system calls to implement most features. But some are not covered by the *BDOS*. An example is reading and writing system time. The library still implements almost complete `time.h`. By providing your own platform dependant functions you can unlock full features of the *libcpm3-z80*.

To compile the platform dependant library add your platform name to the arguments. 

~~~
make PLATFORM=partner
~~~

 > The value `partner` is an example, use the name of your
 > platform instead. 
 
The system will then ignore the existing basic *(proxy!)* platform dependant code and expect that the missing functions are found at link time in another library or object file.

 > If platform dependant functions are not linked with your program 
 > the linker will not be able to resolve them and will throw errors.

### Platform dependant functions

The platform dependant functions are defined with empty bodies
by the *libcpm3-z80*. If you compile a basic *libcpm3-z80* version
you should not only avoid platform dependant functions, but also
following standard C because they depend on platform dependant
functions.


| Header     | Platform dependant function    |
|------------|--------------------------------| 
| time.h     | clock()                        |
| time.h     | time()                         |
| stdarg.h   | argv[0]                        |


#### Injecting your platform dependant functions

If you compile with the `make PLATFORM=<name>` command then
the empty functions are not compiled with the library. 

You can provide implementations for these functions in another
library or object file and link with your program. Here is a list
of functions you need to provide.

~~~cpp
/* Non standard function to get system date and time.
   Declared in: time.h */
extern int gettimeofday(struct timeval *tv);

/* Non standard function to set system date and time 
   Declared in: time.h*/
extern int settimeofday(const struct timeval *tv);

/* Sleep in milliseconds
   Declared in: unistd.h */
extern void msleep(int millisec);

/* Called just after the libcpm3-z80 library initializes!
   Implement this to initialize your own libraries at the same time.
   Declared in: stdlib.h */
extern void libinit();
~~~

There is also one platform dependant variable: `progname`, defined
in `stdlib.h`. By default it is empty, but if you implement the
`libinit()` and set it to name of your running program, then the
`argv[0]` will be populated correctly. Otherwise the `argv[0]` 
will be an empty string. Other arguments are picked up from the 
program tail correctly.

 > We just didn't know how to implement the `argv[0]` safely.
 > If you do please send us a message via github **Issues**.

## What is implemented?

Click on the header name to see the scope of its implementation.

<details><summary>ctype.h/</summary>

~~~cpp
/* True if char is a letter. */
extern bool isalpha(int c);

/* True if char is white space. */
extern bool isspace(int c);

/* True if char is punctuation. */
extern bool ispunct(int c);

/* True if char is a digit */
extern bool isdigit(int c);

/* Returns char, converted to lowercase. */
extern int tolower(int c);

/* Return char converted to uppercase */
extern int toupper(int c);
~~~
</details>  

<details><summary>errno.h/</summary>

~~~cpp
#define ENOENT      2       /* no such file or directory */
#define	EIO         5       /* I/O error */
#define	E2BIG       7       /* argument list too long */
#define EBADF       9       /* bad file descriptor */
#define	EAGAIN      11      /* try again */
#define EWOULDBLOCK EAGAIN  /* -"- */
#define	ENOMEM      12      /* out of memory */
#define EINVAL      22      /* negative offset or offset beyond end of file? Invalid address */
#define ENFILE      23      /* too many open files (file table overflow) */
#define	ENOTTY      25      /* not a typewriter */
#define	EPIPE       32      /* broken pipe */

/* global error code */
extern int errno;
~~~
</details>  

<details><summary>fcntl.h/</summary>

~~~cpp
#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2
#define O_TRUNC     4

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2
~~~
</details>  

<details><summary>limits.h/</summary>

~~~cpp
#define CHAR_BIT    8                /* number of bits in byte */
#define SCHAR_MIN   -128
#define SCHAR_MAX   +127
#define UCHAR_MAX   255
#define CHAR_MIN    -128
#define CHAR_MAX    +127
#define SHRT_MIN    -128
#define SHRT_MAX    +127
#define USHRT_MAX   255
#define INT_MIN     -32768
#define INT_MAX     +32767
#define UINT_MAX    65535
#define LONG_MIN    -2147483648
#define LONG_MAX    +2147483647
#define ULONG_MAX   4294967295
~~~
</details>  

<details><summary>stdarg.h/</summary>

~~~cpp
/* Standard C var arg macros */
#define va_list                 unsigned char *
#define va_start(marker, last)  { marker = (va_list)&last + sizeof(last); }
#define va_arg(marker, type)    *((type *)((marker += sizeof(type)) - sizeof(type)))
#define va_end(marker)          marker = (va_list) 0;
~~~
</details>  

<details><summary>stdbool.h/</summary>

~~~cpp
#define bool int

#define false 0
#define FALSE 0
#define true 1
#define TRUE 1
~~~
</details>  

<details><summary>stddef.h/</summary>

~~~cpp
typedef unsigned int    size_t;
typedef long            ssize_t;
typedef long            off_t;
~~~
</details>  

<details><summary>stdint.h/</summary>

~~~cpp
typedef signed char     int8_t;
typedef unsigned char   uint8_t;
typedef int             int16_t;
typedef unsigned int    uint16_t;
typedef long            int32_t;
typedef unsigned long   uint32_t;
~~~
</details>  

<details><summary>stdio.h/</summary>

~~~cpp
#define EOF         0x1A	
#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

#define FILE        void
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* Open file. */
extern FILE *fopen(const char *path, const char *mode);

/* Move to fpos. */
extern int fseek(FILE *stream, long offset, int whence);

/* Read a record. */
extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

/* EOF reached? */
extern int feof(FILE *stream);

/* Close a file. */
extern int fclose(FILE *stream);

/* Get file position. */
extern long ftell(FILE *stream);

/* Write a record. */
extern size_t fwrite(
    const void *ptr, 
    size_t size, 
    size_t nmemb, 
    FILE *stream);

/* Prints a string. */
extern int puts(const char *s);

/* Print formatted string to stdout. */
extern int printf(char *fmt, ...);

/* Prints formated string to a string. */
extern int sprintf(char *buf, char *fmt, ...);

/* Prints a char. */
extern int putchar(int c);

/* Reads a char (blocks. */
extern int getchar(void);
~~~
</details>  

<details><summary>stdlib.h/</summary>

~~~cpp
/* Standard requires it here. */
#ifndef NULL
#define NULL 0
#endif /* NULL */

/* Non standard extension, the name of the platform on
   which library was build i.e. z80-none or z80-partner.
   This is changed when adding PLATFORM=name to make call. */
extern char *libplatform;

/* Non standard extension: running program name.
   Used by argv[0]. */
extern char *progname;

/* Exit application. */
extern void exit(int status);

/* String to long using base. */
extern long strtol(char *nptr, char **endptr, int base);

/* Covert ascii to integer. */
extern int atoi(const char *str);

/* Strin to unsigned long using base, */
extern unsigned long int strtoul(const char *nptr, char **endptr, int base);

/* Absolute value. */
extern int abs (int i);

/* Return random number */
extern int rand(void);

/* Set random seed. */
extern void srand(unsigned int seed);

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
   [<drive>:]filename.typ[[g]<user area>] */
#define MAX_DRIVE   1
#define MAX_FNAME   8
#define MAX_EXT     3
extern void splitpath(
   const char *path,
   char *drive,
   int *user,
   char *fname,
   char *ext
);
~~~
</details>  

<details><summary>string.h/</summary>

~~~cpp
#ifndef NULL
#define NULL ( (void *) 0)
#endif /* NULL */

/* Set n bytes in memory block to the value c, */
extern void *memset(void *s, int c, size_t n);

/* Copy memory block, */
extern void *memcpy(const void *dest, const void *src, size_t n);

/* Searches for the first occurrence of the character c 
(an unsigned char) in the first n bytes. */
extern void *memchr(const void *s, int c, size_t n);

/* Compare memory blocks. 0=equal. */
extern int memcmp(const void *s1, const void *s2, size_t n);

/* Zero terminated string length. */
extern size_t strlen(const char *s);

/* Copy string to another string */
extern char *strcpy(char *dest, const char *src);

/* Copy max num chars to another string. */
extern char* strncpy(char* dst, const char* src, size_t num);

/* Compare strings, 0=match. */
extern int strcmp(const char *s1, const char *s2);

/* Compare first n chars of string. */
extern int strncmp(const char *s1, const char *s2, size_t n);

/* Find first occurence of c in s. */
extern char *strchr(const char *s, int c);

/* Find first occurence of c in s frin the right (=last occurence). */
extern char *strrchr(const char *s, int c);

/* Non standard (unix) tokenizer. */
extern char *strsep(char **stringp, const char *delim);

/* The length of the number of characters before the 1st occurrence 
of character present in both the string. */
extern size_t strcspn(const char *s1, const char *s2); 

/* Tokenize string s using delimiters delim. */
extern char *strtok(char *s, const char *delim);

/* Return text of the errnum system error. */
extern char *strerror(int errnum);

/* Non standard extension: stoupper */
extern void stoupper(char *s);

/* Non standard extension: stolower */
extern void stolower(char *s);
~~~
</details>  

<details><summary>time.h/</summary>

~~~cpp
/* idp clock has a resolution of 1/100 sec */
#define CLOCKS_PER_SEC  100
typedef long clock_t;

/* Std C defines this as number of seconds since  00:00, Jan 1 1970 UTC */
typedef long time_t;

/* Std C tm struct */
struct tm {
    /* seconds,  range 0 to 59 */
    int tm_sec;
    /* minutes, range 0 to 59 */
    int tm_min;
    /* hours, range 0 to 23 */
    int tm_hour;
    /* day of the month, range 1 to 31 */
    int tm_mday;
    /* month, range 0 to 11 */
    int tm_mon;
    /* The number of years since 1900 */
    int tm_year;
    /* day of the week, range 0 to 6 */
    int tm_wday;
    /* day in the year, range 0 to 365 */
    int tm_yday;
    /* daylight saving time */
    int tm_isdst;
};

/* non standard for settimeofday and gettimeofday functions */
struct timeval { 
    time_t tv_sec;                      /* seconds since Jan. 1, 1970 */ 
    int tv_msec;                        /* and milliseconds */ 
}; 

/* Converts given calendar time tm to a textual representation of 
the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy. */
extern char* asctime(const struct tm* time_ptr);

/* Return current clock in 1/1000 seconds */
extern clock_t clock(void);

/* Convert current time to textual representation using the following
format Www Mmm dd hh:mm:ss yyyy (uses asctime...).*/
extern char* ctime(const time_t* ptt);

/* Returns difference between two time points in seconds! */
extern long difftime(time_t time_end,time_t time_beg);

/* Get Greenwich mean time (politically correct: UTC), make localtime
equal to UTC. */
#define localtime gmtime
extern struct tm *gmtime(const time_t *timer);

/* Create time_t given tm structure. */
extern time_t mktime(struct tm *tme);
	
/* Get current time. */
extern time_t time(time_t *arg);

/* Non standard function to get system date and time. */
extern int gettimeofday(struct timeval *tv);

/* Non standard function to set system date and time */
extern int settimeofday(const struct timeval *tv);

~~~
</details>  


<details><summary>unistd.h/</summary>

~~~cpp
/* Non standard function to sleep (in milliseconds).
   NOTE: The libcpm3-z80 only provides an empty proxy 
   to this function. If you want to use it you need to
   compile the libcpm3-z80 with the PLATFORM switch and
   inject your own implementation.  */
extern void msleep(int millisec);
~~~
</details>  


### Non-standard extensions

Following functions and variables in *libcpm3-z80* are not part of the *Standard C library*.

| Header     | Function                                            |
|------------|-----------------------------------------------------| 
| sys/bdos.h | bdos(), bdosret()                                   |
| time.h     | gettimeofday(), settimeofday()                      |
| unistd.h   | mslee(), lseek(), close(), read(), write()          |
| fcntl.h    | open(), creat(), fcntl()                            |
| stdlib.h   | libplatform, progname, libinit(), splitpath()       |
| string.h   | stoupper(), stolower()                              |


## To Do

The library is in beta test. The only remaining feature 
in implementation are file functions from `stdio.h` (also:
`fcntl.h` and `unistd.h` for Posix versions)

`dirent.h` is not documented yet.

`types.h` is not documented yet.

[language.url]:   https://en.wikipedia.org/wiki/ANSI_C
[language.badge]: https://img.shields.io/badge/language-C-blue.svg

[standard.url]:   https://en.wikipedia.org/wiki/C89/
[standard.badge]: https://img.shields.io/badge/standard-C89-blue.svg

[license.url]:    https://github.com/tstih/libcpm3-z80/blob/main/LICENSE
[license.badge]:  https://img.shields.io/badge/license-MIT-blue.svg

[status.badge]:  https://img.shields.io/badge/status-beta-orange.svg