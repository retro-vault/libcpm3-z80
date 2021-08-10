/*
 * close.c
 *
 * Posix C file close function
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

int close(int fd) {

    /* Get the descriptor. */
    fd_t* fdblk=_fd_get(fd);
    if (fdblk==NULL) {
        errno = EBADF;
        return -1;
    }

    /* Call file close on BDOS 
       TODO: Manage hardware error. */
    if (bdos(F_CLOSE,(uint16_t)&(fdblk->fcb))==0xff) {
        errno=EIO;
        return -1;
    }

    /* Finally, release the file descriptor. */
    _fd_set(fd,NULL);

    /* And return success. */
    errno = 0;
    return 0;
}