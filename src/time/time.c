/*
 * time.c
 *
 * Return the current time as a time_t value read from the CP/M clock.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <time/_time.h>


/* Get current time. */
time_t time(time_t *arg) {

    /* Read clock from platform */
    struct timeval tv;
    gettimeofday(&tv);

    /* copy to arg if not NULL? */
    if (arg!=NULL)
        *arg=tv.tv_sec;

    /* and return it */
    return tv.tv_sec;
}

