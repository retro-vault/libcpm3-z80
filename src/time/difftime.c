/*
 * difftime.c
 *
 * difftime function (see: time.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <time/_time.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

/* Returns difference between two time points in seconds! */
long difftime(time_t time_end,time_t time_beg) {
    return time_end-time_beg;
}

#endif /* !LEAN_AND_MEAN */