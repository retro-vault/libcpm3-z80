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

#define O_RDONLY    0
#define O_WRONLY    1
#define O_RDWR      2

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

/* open file, return file descriptor */
extern int open(const char *pathname, int flags);

/* create file, return file descriptor */
extern int creat(const char *pathname);

#endif /* __FCNTL_H__ */