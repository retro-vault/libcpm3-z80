/*
 * _stdio.h
 *
 * Internal stdio.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#ifndef LIBCPM3_INT_STDIO_H
#define LIBCPM3_INT_STDIO_H

#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/bdos.h>

#include <_impl/print/_print.h>
#include <_impl/print/_nltype.h>

#include <file/_fd.h>

/* EOF and positions */
#define EOF         0x1A	
#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

/* FILE type. */
typedef struct _iobuf {
  char      flags[4];
  int       fd;
  bool      eof;
  bool      err;
  int       ungot;
} FILE; 

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* is file pointer valid? */
extern bool _check_fp(FILE *fp);

/* stdio helpers used internally */
extern FILE *fopen(const char *path, const char *mode);
extern int fclose(FILE *fp);
extern void clearerr(FILE *fp);
extern int ferror(FILE *fp);
extern int fgetc(FILE *fp);
extern int getc(FILE *fp);
extern int fputc(int c, FILE *fp);
extern int getchar(void);
extern int sprintf(char *buf, char *fmt, ...);
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);
extern int fseek(FILE *fp, long offset, int whence);
extern int vfprintf(FILE *fp, const char *fmt, va_list ap);

/* write single char */
extern int putchar(int c);

#endif /* LIBCPM3_INT_STDIO_H */
