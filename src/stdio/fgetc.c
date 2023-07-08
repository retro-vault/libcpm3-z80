/*
 * fgetc.c
 *
 * fgetc function (see:stdio.h)
 *
 * 05.07.2023   tstih
 *
 */
#include <stdio/_stdio.h>

int fgetc(FILE *fp) {

    /* Reset errno. */
    errno = 0;

    /* Check file descriptor. */
    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    /* If eof, don't proceed. */
    if (fp->eof) return 0;
    
    /* Read char. */
    char ch;
    int rd = read(fp->fd, &ch, 1);
    if (rd == 0) {
        fp->eof = true;
        return 0;
    }
    else if (rd == -1) 
        return -1; /* errno is propagated. */
    else if (rd == 1) {
        /* If text mode file, check eof... */
        if (memchr(&fp->flags, 'b', 3) == NULL && ch==EOF) {
            fp->eof = true;
            return 0;
        } 
    }
    return ch;
}