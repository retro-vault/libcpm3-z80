/*
 * fopen.c
 *
 * Open a stream on a CP/M file using the requested mode string.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

FILE *fopen(const char *path, const char *mode)
{
    int fd, oflags;
    FILE *f;

    /* Reset errno. */
    errno = 0;

    /* Initialize oflags. */
    oflags=0;

    /* Extract mode. */
    if (strncmp(mode, "r", 1) == 0) {
        oflags = O_RDONLY;
    }

    if (strncmp(mode, "w", 1) == 0) {
        oflags = O_WRONLY | O_CREAT | O_TRUNC;
    }

    if (strncmp(mode, "r+", 2) == 0) {
        oflags = O_RDWR;
    }

    if (strncmp(mode, "w+", 2) == 0) {
        oflags = O_RDWR | O_CREAT | O_TRUNC;
    }

    /* Open file. */
    fd = open(path, oflags);
    if (fd < 0) return NULL; /* errno is set by open... */

    /* Create FILE * structure. */
    f=malloc(sizeof(FILE));
    if (f==NULL) {
        close(fd);
        errno=ENOMEM;
        return NULL;
    }
    f->fd=fd;
    f->eof=false;
    f->err=false;
    f->ungot=-1;
    memset(f->flags, 0, 4);
    strncpy(f->flags, mode, 3);

    /* And return. */
    return f;
}
