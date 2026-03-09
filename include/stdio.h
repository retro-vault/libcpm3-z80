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
  bool      err;
  int       ungot;
} FILE; 

extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

/* Open file. */
extern FILE *fopen(const char *path, const char *mode);

/* Close a file. */
extern int fclose(FILE *fp);

/* Flush file buffers. */
extern int fflush(FILE *fp);

/* Write a record. */
extern size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *fp);

/* Read a record. */
extern size_t fread(void *ptr, size_t size, size_t nmemb, FILE *fp);

/* Move to fpos. */
extern int fseek(FILE *fp, long offset, int whence);

/* EOF reached? */
extern int feof(FILE *fp);

/* Error on stream? */
extern int ferror(FILE *fp);

/* Clear EOF/error state. */
extern void clearerr(FILE *fp);

/* Get file position. */
extern long ftell(FILE *fp);

/* Get char. */
extern int fgetc(FILE *fp);

/* Get line. */
extern char *fgets(char *str, int n, FILE *fp);

/* Put char. */
extern int fputc(int c, FILE *fp);

/* Put string. */
extern int fputs(const char *s, FILE *fp);

/* Prints a string. */
extern int puts(const char *s);

/* Reads a string */
extern char *gets(char *str);

/* Print formatted string to stdout. */
extern int printf(char *fmt, ...);

/* Print formatted string to stream. */
extern int fprintf(FILE *fp, char *fmt, ...);

/* Print formatted string using va_list to stdout. */
extern int vprintf(const char *fmt, va_list ap);

/* Print formatted string using va_list to stream. */
extern int vfprintf(FILE *fp, const char *fmt, va_list ap);

/* Print formatted string using va_list to buffer. */
extern int vsprintf(char *buf, const char *fmt, va_list ap);

/* Prints formated string to a string. */
extern int sprintf(char *buf, char *fmt, ...);

/* Prints a char. */
extern int putchar(int c);

/* Reads a char (blocks). */
extern int getchar(void);

/* stdio wrappers */
extern int getc(FILE *fp);
extern int getc_unlocked(FILE *fp);
extern int putc(int c, FILE *fp);
extern int getw(FILE *fp);
extern FILE *tmpfile(void);
extern char *tmpnam(char *s);
extern void rewind(FILE *fp);
extern int ungetc(int c, FILE *fp);
extern void perror(const char *s);
extern void setbuf(FILE *fp, char *buf);
extern int setvbuf(FILE *fp, char *buf, int mode, size_t size);

/* Remove file. */
extern int remove(const char *path);

#endif /* LIBCPM3_STDIO_H */
