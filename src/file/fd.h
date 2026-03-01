/*
 * fd.h
 *
 * Posix file descriptors.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#ifndef LIBCPM3_FILE_FD_H
#define LIBCPM3_FILE_FD_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/types.h>

#include <file/fcb.h>

/* Reserve 16 spaces for file descriptors. */
#define MAX_FILES       16
#define DMA_SIZE        128
#define DMA_INVALID_POS 0xff    /* Signals the DMA is invalid */

typedef struct fd_s {
    long fpos;                  /* Current file position */
    uint8_t dmapos;             /* Current position in DMA */
    bool dmadirty;              /* Write DMA on close? */
    uint8_t dma[DMA_SIZE];      /* DMA for this descriptor */
    uint8_t lrb;                /* Last record byte count */
    int oflags;                 /* File flags */
    fcb_t fcb;                  /* fcb for this descriptor */
} fd_t;

/* File descriptor table */
extern fd_t* _fds[];

/* Initialize */
extern void _init_fds(void);

/* Get first free file descriptor. */
extern int _fd_reserve(void);

/* Set it back to null. */
extern void _fd_free(int fd);

/* Populate file descriptor placeholder with pointer */
extern void _fd_set(int fd, fd_t *fdblk);

/* Return file descriptor block. */
extern fd_t* _fd_get(int fd);

#endif /* LIBCPM3_FILE_FD_H */
