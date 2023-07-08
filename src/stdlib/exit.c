/*
 * exit.c
 *
 * exit function (see: stdlib.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <stdlib/_stdlib.h>

void exit(int status)
{
    status;
    /* Unfortunately, the status is lost in CP/M. */
    bdos(P_TERMCPM, 0);
}