/*
 * putchar.c
 *
 * Write one byte to standard output, expanding newlines
 * according to the current nltype setting.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdio/_stdio.h>

int putchar(int c) {
    /* Extend newline if DOS. */
    if (c=='\n') {
        switch(nltype) {
            case NL_LF:
                bdos(C_WRITE,'\n');
                break;
            case NL_CRLF:
                bdos(C_WRITE,'\r');
                bdos(C_WRITE,'\n');
                break;
            case NL_LFCR:
                bdos(C_WRITE,'\n');
                bdos(C_WRITE,'\r');
                break;
        }
    } else bdos(C_WRITE,c);
    return c;
}
