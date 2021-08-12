/*
 * fcntl.h
 *
 * Nonstandard (but common) C library header.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.08.2021   tstih
 *
 */
#ifndef __FCNTL_H__
#define __FCNTL_H__

#define O_RDONLY    0x0000      /* Read only. */
#define O_WRONLY    0x0001      /* Write only. */
#define O_RDWR      0x0002      /* Read and write. */
#define	O_CREAT		0x0200		/* Create if nonexistant */
#define	O_TRUNC		0x0400		/* Truncate to zero length */

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

/* Open file, return file descriptor. */
extern int open(const char *pathname, int flags);

/* Create file, return file descriptor. */
extern int creat(const char *pathname);

#endif /* __FCNTL_H__ */