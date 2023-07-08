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
#ifndef ___STDIO_H__
#define ___STDIO_H__

#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/bdos.h>

#include <util/print.h>

#include <file/fd.h>

/* How console functions interpret \n? As \n or as \r\n? */
#define NL_LF       0
#define NL_CRLF     1
#define NL_LFCR     2
extern char nltype;

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
} FILE; 

/* is file pointer valid? */
extern bool _check_fp(FILE *fp);

/* write single char */
extern int putchar(int c);

#endif /* ___STDIO_H___ */