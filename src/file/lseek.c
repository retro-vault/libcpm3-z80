/*
 * lseek.c
 *
 * Posix C file lseek function. 
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#include <sys/bdos.h>
#include <sys/types.h>
#include <file/fcb.h>
#include <file/fd.h>

off_t lseek(int fd, off_t offset, int whence) {
    whence;

    /* If dirty, write. */
    fsync(fd);

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Calculate random offset */
    long rec=offset/DMA_SIZE;
    long dmaoffs=offset%DMA_SIZE;
    fdblk->fcb.rrec=rec;

    /* And move */
    bdos_ret_t result;
    bdosret(F_READRAND,(uint16_t)&(fdblk->fcb),&result);
    if (result.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* Set file pointers. */
    fdblk->fpos=offset;
    fdblk->dmapos=dmaoffs;

    /* Assume success */
    errno = 0;
    return offset;

}