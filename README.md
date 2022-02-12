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

You need a Linux with the **latest** version of *SDCC* development tools installed.

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

<details><summary>sys/bdos.h/</summary>

~~~cpp
/* The usual exit codes. */
#define BDOS_SUCCESS 0
#define BDOS_FAILURE 0xff

/* CP/M 3 BDOS function codes
 * See here: https://www.seasip.info/Cpm/bdos.html
 */

/* Process commands */
#define P_TERMCPM       0               /* Process terminate */
#define P_CODE          108             /* Set process return code */
/* Console commands */
#define C_READ          1               /* Console read */
#define C_WRITE         2               /* Console write */
#define C_RAWIO         6               /* Console raw input */
#define C_DELIMIT       110             /* Get or set delimiter $ */
#define C_WRITEBLK      111             /* Send block of text to console */
/* Drive commands */
#define DRV_SET         14              /* Set drive */
#define DRV_LOGINVEC    24              /* Enumerate drives */
#define DRV_GET         25              /* Get current drive */
#define DRV_DPB         31              /* Get drive info block */
/* File commands */
#define F_OPEN          15              /* Open file */
#define F_CLOSE         16              /* Close file */
#define F_READ          20              /* Read from file */
#define F_WRITE         21              /* Write to file */
#define F_MAKE          22              /* Create file */
#define F_DMAOFF        26              /* Set DMA offset */
#define F_USERNUM       32              /* Get/set user area */
#define F_READRAND      33              /* Read random record */
#define F_WRITERAND     34              /* Write random record */
#define F_SIZE          35              /* Get file size in blocks */
#define F_RANDREC       36              /* Store current pos. */
#define F_TRUNCATE      99              /* Truncate a file */
#define F_PARSE         152             /* Parse filename into FCB. */

/* BDOS return code */
typedef struct bdos_ret_s {
    uint8_t reta;                       /* return code in reg A */
    uint8_t retb;                       /* return code in reg B */
    uint16_t rethl;                     /* return code in HL */
} bdos_ret_t;


/* Hadrware errors, returned in the H register. */
#define HWERR_SOFTWARE  0               /* Software error (i.e. file not found)*/
#define HWERR_DRV_SEL   1               /* Cant access drive */
#define HWERR_DISK_RO   2               /* Disk is read only */
#define HWERR_FILE_RO   3               /* File is read only */
#define HWERR_INV_DRV   4               /* Invalid drive */
#define HWERR_FOPEN     5               /* File is already open */
#define HWERR_CHECKSUM  6               /* FCB checksum error */
#define HWERR_PASSWORD  7               /* Password error */
#define HWERR_FEXISTS   8               /* File already exists */
#define HWERR_INV_FNME  9               /* Name contains ? */


/* Call bdos, return register A. */
extern uint8_t bdos(uint8_t fn, uint16_t param);

/* Call bdos, return results. */
extern bdos_ret_t *bdosret(uint8_t fn, uint16_t param, bdos_ret_t *p);
~~~
</details>  

<details><summary>sys/stat.h/</summary>

~~~cpp
struct stat {
    char        st_drive;               /* A - P */
    uint8_t     st_user;                /* 0 - 15 */
    off_t       st_size;                /* Total size, in bytes */
    uint16_t    st_blksize;             /* Block size */
    uint16_t    st_blocks;              /* Number of blocks */
    uint8_t     st_lrb;                 /* Last record byte count */
};

/* Read file stat. */
extern int stat(char *pathname, struct stat *statbuf);
~~~
</details>  

<details><summary>sys/types.h/</summary>

~~~cpp
/* This should be signed size, but it is too short. */
typedef long ssize_t;

/* Used to represent file sizes. */
typedef long off_t;
~~~
</details>


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
#define O_RDONLY    0x0000      /* Read only. */
#define O_WRONLY    0x0001      /* Write only. */
#define O_RDWR      0x0002      /* Read and write. */
#define	O_CREAT     0x0200      /* Create if nonexistant */
#define	O_TRUNC     0x0400      /* Truncate to zero length */

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

/* Open file, return file descriptor. */
extern int open(const char *pathname, int flags);

/* Create file, return file descriptor. */
extern int creat(const char *pathname);
~~~
</details>  

<details><summary>float.h/</summary>

~~~cpp
#define FLT_RADIX       2
#define FLT_MANT_DIG    24
#define FLT_EPSILON     1.192092896E-07F
#define FLT_DIG         6
#define FLT_MIN_EXP     (-125)
#define FLT_MIN         1.175494351E-38F
#define FLT_MIN_10_EXP  (-37)
#define FLT_MAX_EXP     (+128)
#define FLT_MAX         3.402823466E+38F
#define FLT_MAX_10_EXP  (+38)
~~~
</details>  


<details><summary>limits.h/</summary>

~~~cpp
#define CHAR_BIT    8                   /* Bits in char. */
#define SCHAR_MIN   -128
#define SCHAR_MAX   +127
#define UCHAR_MAX   255
#define CHAR_MIN    -128
#define CHAR_MAX    +127
#define MB_LEN_MAX  8                   /* Max. bytes in multi byte char. */
#define SHRT_MIN    -128
#define SHRT_MAX    +127
#define USHRT_MAX   255
#define INT_MIN     -32768
#define INT_MAX     +32767
#define UINT_MAX    65535
#define LONG_MIN    -2147483648
#define LONG_MAX    +2147483647
#define ULONG_MAX   4294967295
#define SSIZE_MAX   65535               /* Max bytes for file read */
~~~
</details>  


<details><summary>math.h/</summary>

~~~cpp
/* constants */
#define HUGE_VAL    3.402823466e+38

/* functions */
extern float ceil(float x);
extern float cos(float x);
extern float cot(float x);
extern float exp(float x);
extern float fabs(float x);
extern float frexp(float x, int *pw2);
extern float floor(float x);
extern float ldexp(float x, int pw2);
extern float log(float x);
extern float log10(float x);
extern float modf(float x, float * y);
extern float pow(float x, float y);
extern float sin(float f);
extern float sqrt(float x);
extern float tan(float x);
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
typedef uint16_t    ptrdiff_t;          /* Result of sub. two pointers. */
typedef uint16_t    size_t;             /* sizeof type */
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

/* FILE type. */
typedef struct _iobuf {
  char      flags[4];
  int       fd;
  bool      eof;
} FILE; 

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* Open file. */
extern FILE *fopen(const char *path, const char *mode);

/* Close a file. */
extern int fclose(FILE *fp);

/* Write a record. */
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);

/* Read a record. */
extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);

/* Move to fpos. */
extern int fseek(FILE *fp, long offset, int whence);

/* EOF reached? */
extern int feof(FILE *fp);

/* Get file position. */
extern long ftell(FILE *fp);

/* Get char. */
extern int fgetc(FILE *fp);

/* Prints a string. */
extern int puts(const char *s);

/* Reads a string */
extern char *gets(char *str);

/* Print formatted string to stdout. */
extern int printf(char *fmt, ...);

/* Prints formated string to a string. */
extern int sprintf(char *buf, char *fmt, ...);

/* Prints a char. */
extern int putchar(int c);

/* Reads a char (blocks). */
extern int getchar(void);
~~~
</details>  

<details><summary>stdlib.h/</summary>

~~~cpp
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

/* Reverse a string. */
extern void strrev(char *s, register size_t n);

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
/* Posix read. */
extern ssize_t read(int fd, void *buf, size_t count);

/* Posix close. */
extern int close(int fd);

/* Posix flush. */
extern int fsync(int fd);

/* Posix write. */
ssize_t write(int fd, const void *buf, size_t count); 

/* Posix lseek function */
off_t lseek(int fd, off_t offset, int whence);

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

| Header      | Function                                            |
|-------------|-----------------------------------------------------| 
| sys/bdos.h  | bdos(), bdosret()                                   |
| sys/stat.h  | stat()                                              |
| time.h      | gettimeofday(), settimeofday()                      |
| unistd.h    | msleep(), lseek(), close(), read(), write()         |
| fcntl.h     | open(), creat(), fcntl()                            |
| stdlib.h    | libplatform, libinit(), splitpath(), nl             |
| string.h    | stoupper(), stolower(), strrev()                    |


## To Do

`dirent.h` has no implementation.

CP/M 3 Plus has date and time sys calls and the library should 
use them as default implementation.

[language.url]:   https://en.wikipedia.org/wiki/ANSI_C
[language.badge]: https://img.shields.io/badge/language-C-blue.svg

[standard.url]:   https://en.wikipedia.org/wiki/C89/
[standard.badge]: https://img.shields.io/badge/standard-C89-blue.svg

[license.url]:    https://github.com/tstih/libcpm3-z80/blob/main/LICENSE
[license.badge]:  https://img.shields.io/badge/license-MIT-blue.svg

[status.badge]:  https://img.shields.io/badge/status-stable-green.svg