/*
 * types.h
 *
 * Minimal Posix C library header.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#ifndef LIBCPM3_SYS_TYPES_H
#define LIBCPM3_SYS_TYPES_H

/* This should be signed size, but it is too short. */
typedef long ssize_t;

/* Used to represent file sizes. */
typedef long off_t;

#endif /* LIBCPM3_SYS_TYPES_H */