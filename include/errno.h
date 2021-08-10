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

#define ENOENT      2       /* no such file or directory */
#define	EIO         5       /* I/O error */
#define EBADF       9       /* bad file descriptor */
#define	EAGAIN      11      /* try again */
#define EWOULDBLOCK EAGAIN  /* -"- */
#define	ENOMEM      12      /* out of memory */
#define EINVAL      22      /* negative offset or offset beyond end of file? Invalid address */
#define ENFILE      23      /* too many open files (file table overflow) */

/* global error code */
extern int errno;

#endif /* __ERRNO_H__ */