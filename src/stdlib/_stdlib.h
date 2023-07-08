/*
 * _stdlib.h
 *
 * Internal stdlib.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#ifndef ___STDLIB_H__
#define ___STDLIB_H__

#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <mem/mem.h>
#include <util/leanmean.h>

#include <sys/bdos.h>

/* How console functions interpret \n? As \n or as \r\n? */
#define NL_LF       0
#define NL_CRLF     1
#define NL_LFCR     2
extern char nltype;

/* CP/M file limitations */
#define MAX_DRIVE   1
#define MAX_FNAME   8
#define MAX_EXT     3

#ifndef LEAN_AND_MEAN
extern unsigned long _next;
#else 
extern unsigned int _next;
#endif /* LEAN_AND_MEAN */

#endif /* ___STDLIB_H___ */