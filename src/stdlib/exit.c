#include <stdlib/_stdlib.h>

void exit(int status)
{
    status;
    /* Unfortunately, the status is lost in CP/M. */
    bdos(P_TERMCPM, 0);
}