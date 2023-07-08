/*
 * fopen.c
 *
 * fopen function (see:stdio.h)
 *
 * 05.07.2023   tstih
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
        oflags = O_WRONLY | O_TRUNC;
    }

    if (strncmp(mode, "r+", 2) == 0) {
        oflags = O_RDWR;
    }

    if (strncmp(mode, "w+", 2) == 0) {
        oflags = O_RDWR | O_TRUNC;
    }

    /* Open file. */
    fd = open(path, oflags);
    if (fd < 0) return NULL; /* errno is set by open... */

    /* Create FILE * structure. */
    f=malloc(sizeof(FILE));
    f->fd=fd;
    f->eof=false;
    memset(f->flags, 0, 4);
    strncpy((const char *) f->flags, (const char *) mode, 3);

    /* And return. */
    return f;
}
