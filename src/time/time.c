#include <time/_time.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

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

#endif /* !LEAN_AND_MEAN */