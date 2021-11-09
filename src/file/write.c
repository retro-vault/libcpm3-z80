/*
 * write.c
 *
 * Posix C file write function!
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

#include <sys/bdos.h>
#include <sys/types.h>
#include <file/fcb.h>
#include <file/fd.h>

#define DEBUG

#ifdef DEBUG
#include <stdio.h>
#endif 

ssize_t write(int fd, void *buf, size_t count) {

    /* We'll need bytes */
    uint8_t *bbuf=(uint8_t*)buf;

    /* Get fd block, and verify it. */
    fd_t *fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* 0 bytes */
    if (count==0) {
        errno = 0;
        return 0;
    }

    /* Fetch the data sequentially! */
    size_t bwrite=0;
    while (bwrite < count) {

        /* If block not read, we can still write into it
           so declare it as valid. */
        if (fdblk->dmapos==DMA_INVALID_POS)
            fdblk->dmapos = 0;

        /* If there are more bytes left to write 
           then what is available in the DMA:
           set left to length that we can write! 
           And write it! */
        size_t left = count - bwrite;
        if (left > (DMA_SIZE - fdblk->dmapos)) {
            left = DMA_SIZE - fdblk->dmapos;

            /* Populate DMA. */
            memcpy
                (&(fdblk->dma[fdblk->dmapos]),  /* copy to DMA */
                &(bbuf[bwrite]),                /* from buffer */
                left );                         /* whatever is left */

            /* First set the DMA address to our block! */
            bdos(F_DMAOFF,(uint16_t)&(fdblk->dma));

            /* Now write. */
            bdos_ret_t result;
            bdosret(F_WRITE, (uint16_t)&(fdblk->dma),&result);
            if (result.reta!=BDOS_SUCCESS) {
                errno=EIO;
                return -1;
            }

            /* Finally, set DMA to clean, and invalid. */
            fdblk->dmadirty = false;
            fdblk->dmapos = DMA_INVALID_POS;

        } else { /* Just write to DMA and mark it as dirty. */
        
            /* Populate DMA. */
            memcpy
                (&(fdblk->dma[fdblk->dmapos]),  /* copy to DMA */
                &(bbuf[bwrite]),                /* from buffer */
                left );                         /* whatever is left */

            /* Update DMA. */
            fdblk->dmadirty=true;
            fdblk->dmapos += left;

        }

         /* Advance pointers. */
        fdblk->fpos+=left;
        bwrite += left;   
    }
    /* If we did not read anything, and it is an eof
       return 0. Else return bytes read. */
    errno=0;
    return bwrite;
}