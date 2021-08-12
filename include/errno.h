/*
 * errno.h
 *
 * Standard C library header.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 27.04.2021   tstih
 *
 */
#ifndef __ERRNO_H__
#define __ERRNO_H__

#define ENOENT      2       /* No such file or directory. */
#define	EIO         5       /* I/O error. */
#define EBADF       9       /* Bad file descriptor. */
#define	EAGAIN      11      /* Try again. */
#define EWOULDBLOCK EAGAIN  /* -"- */
#define	ENOMEM      12      /* Out of memory */
#define EINVAL      22      /* Negative offset or offset beyond end of file? Invalid address. */
#define ENFILE      23      /* Too many open files (file table overflow). */

/* Global error code. */
extern int errno;

#endif /* __ERRNO_H__ */