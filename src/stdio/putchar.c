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