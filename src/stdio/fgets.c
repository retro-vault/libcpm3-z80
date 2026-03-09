/*
 * fgets.c
 *
 * Read a line from a stream into a caller-supplied buffer.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

char *fgets(char *str, int n, FILE *fp)
{
    int c;
    int i;

    if (str == NULL || n <= 0)
        return NULL;

    if (!_check_fp(fp)) {
        errno = EBADF;
        return NULL;
    }

    i = 0;
    while (i < (n - 1)) {
        c = fgetc(fp);
        if (c == -1 || c == EOF) {
            if (i == 0)
                return NULL;
            break;
        }

        if (c == '\r') {
            str[i++] = '\n';
            break;
        }

        str[i++] = (char)c;
        if (c == '\n')
            break;
    }

    str[i] = '\0';
    return str;
}
