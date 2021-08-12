/*
 * stat.h
 *
 * Minimal Posix C library header.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 11.08.2021   tstih
 *
 */
#ifndef __STAT_H__
#define __STAT_H__

#include <stdint.h>
#include <sys/types.h>

struct stat {
    char        st_drive;               /* A - P */
    uint8_t     st_user;                /* 0 - 15 */
    off_t       st_size;                /* Total size, in bytes */
    uint16_t    st_blksize;             /* Block size */
    uint16_t    st_blocks;              /* Number of blocks */
    uint8_t     st_lrb;                 /* Last record byte count */
};

/* Read file stat. */
extern int stat(char *pathname, struct stat *statbuf);

#endif /* __STAT_H__ */