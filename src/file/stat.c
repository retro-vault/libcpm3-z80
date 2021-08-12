/*
 * stat.c
 *
 * Posix C file read info
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <errno.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/bdos.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <file/fcb.h>
#include <file/fd.h>

/* Returns info about file. */
int stat(char *pathname, struct stat *statbuf) {
    
    /* First parse the filename. */
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    char drive;
    int user;
    if (splitpath(pathname,&drive, &user, fname, ext)<0) {
        errno=ENOENT;
        return -1;
    }

    /* Create the temporary FCB,
       and populate it. */
    fcb_t *fcb=calloc(sizeof(fcb_t),1);
    _to_fcb_name(fcb->filename, fname, MAX_FNAME);
    _to_fcb_name(fcb->filetype, ext, MAX_EXT);
    fcb->drive=drive - 'A' + 1;

    /* Gef file length */
    bdos_ret_t result;
    bdosret(F_SIZE,(uint16_t)fcb,&result);
    
    /* Error? */
    if (result.reta==BDOS_FAILURE) {
        free(fcb); /* Release allocated memory. */
        errno=EIO;
        return -1;    
    }

    /* Partially populate the stat buffer. */
    statbuf->st_drive=drive;
    statbuf->st_user=user;
    statbuf->st_blocks=fcb->rrec;
    statbuf->st_blksize=DMA_SIZE;

    /* Now open and close the same file. */
    fcb->seqreq=0xff; /* Get last byte read. */
    bdosret(F_OPEN,(uint16_t)fcb,&result);
    if (result.reta==BDOS_FAILURE) {
        free(fcb);
        errno=EIO;
        return -1;
    }

    /* Get last read bytes, and (just in case)
       test against invalid values. */
    if (fcb->seqreq==0 || fcb->seqreq>DMA_SIZE)
        statbuf->st_lrb=DMA_SIZE;
    else    
        statbuf->st_lrb=fcb->seqreq;

    bdosret(F_CLOSE,(uint16_t)fcb,&result);
    if (result.reta==BDOS_FAILURE) {
        errno=EIO;
        return -1;
    }

    /* Finally, accurately calculate size. 
       Cast one to long to let the compiler know
       to use longs. */
    statbuf->st_size=
        (long)statbuf->st_blksize
        * ( statbuf->st_blocks - 1 )
        + statbuf->st_lrb;

    /* We did it. */
    errno=0;
    free(fcb);
    return 0;
}