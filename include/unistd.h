/*
 * unistd.h
 *
 * A non-standard extension header to the Standard C library,
 * common on unix. Contains system and block file functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 07.08.2021   tstih
 *
 */
#ifndef __UNISTD_H__
#define __UNISTD_H__

#include <sys/types.h>
#include <stddef.h>

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

#endif /* __UNISTD_H__ */