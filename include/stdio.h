/*
 * stdio.h
 *
 * Standard C I/O header.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.05.2021   tstih
 *
 */
#ifndef LIBCPM3_STDIO_H
#define LIBCPM3_STDIO_H

#include <stdbool.h>
#include <stddef.h>
#include <stdarg.h>

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

#endif /* LIBCPM3_STDIO_H */