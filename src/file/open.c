/*
 * open.c
 *
 * Posix C file open function
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#include <errno.h>
#include <stdlib.h>
#include <stdlib.h>

#include <sys/bdos.h>
#include <file/fcb.h>
#include <file/fd.h>

int open(const char *pathname, int flags)
{
    /* First parse the filename. */
    char fname[MAX_FNAME + 1];
    char ext[MAX_EXT + 1];
    char drive;
    int user;
    if (splitpath(pathname,&drive, &user, fname, ext)<0) {
        errno=ENOENT;
        return -1;
    }

    /* Get free file descriptor. */
    int fd=_fd_reserve();
    if (fd < 0) {
        errno = ENFILE; /* No free file descriptor */
        return -1;
    }

    /* fcb will need drive number, not drive letter. */
    drive = drive - 'A' + 1;

    /* Allocate new file descriptor block. */
    fd_t *fdblk=calloc(1, sizeof(fd_t));
    if (fdblk==NULL) {
        errno=ENOMEM;
        return -1;
    }
    _fd_set(fd,fdblk);

    /* Populate fcb block */
    fdblk->oflags=flags;
    _to_fcb_name(fdblk->fcb.filename, fname, MAX_FNAME);
    _to_fcb_name(fdblk->fcb.filetype, ext, MAX_EXT);
    fdblk->fcb.drive=drive;

    /* And open file. No magic here. */
    bdos_ret_t result;
    bdosret(F_OPEN,(uint16_t)&(fdblk->fcb),&result);
    if (result.reta==0xff) {
        /* TODO: Is O_CREAT on? */
        errno=EIO;
        return -1;
    }
    
    /* If we are here, we're good.*/
    errno=0;
    return fd;
}