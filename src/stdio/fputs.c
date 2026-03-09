/*
 * fputs.c
 *
 * Write a string to a stream without adding a newline.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int fputs(const char *s, FILE *fp)
{
    size_t len;
    size_t i;

    if (s == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (!_check_fp(fp)) {
        errno = EBADF;
        return -1;
    }

    if (fp->fd == 1 || fp->fd == 2) {
        for (i = 0; s[i] != '\0'; ++i) {
            if (putchar((unsigned char)s[i]) == -1)
                return -1;
        }
        return 0;
    }

    len = strlen(s);
    if (fwrite(s, 1, len, fp) != len)
        return -1;

    return 0;
}
