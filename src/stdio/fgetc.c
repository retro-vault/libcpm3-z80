/*
 * fgetc.c
 *
 * Read the next byte from a stream and return it as an int.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int fgetc(FILE *fp) {

    /* Reset errno. */
    errno = 0;

    /* Check file descriptor. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        if (fp)
            fp->err = true;
        return -1;
    }

    if (fp->ungot != -1) {
        int c = fp->ungot;
        fp->ungot = -1;
        fp->eof = false;
        return c;
    }

    /* If eof, don't proceed. */
    if (fp->eof)
        return EOF;

    /* Console input for stdin-style descriptor. */
    if (fp->fd == 0) {
        fp->err = false;
        return (int)(unsigned char)bdos(C_READ, 0);
    }
    
    /* Read char. */
    char ch;
    int rd = read(fp->fd, &ch, 1);
    if (rd == 0) {
        fp->eof = true;
        return EOF;
    }
    else if (rd == -1) {
        fp->err = true;
        return -1; /* errno is propagated. */
    }
    else if (rd == 1) {
        /* If text mode file, check eof... */
        if (memchr(&fp->flags, 'b', 3) == NULL && ch==EOF) {
            fp->eof = true;
            return EOF;
        } 
    }
    fp->err = false;
    return (int)(unsigned char)ch;
}
