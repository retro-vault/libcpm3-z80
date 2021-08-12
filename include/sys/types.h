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
#ifndef __TYPES_H__
#define __TYPES_H__

/* This should be signed size, but it is too short. */
typedef long ssize_t;

/* Used to represent file sizes. */
typedef long off_t;

#endif /* __TYPES_H__ */