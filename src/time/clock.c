/*
 * clock.c
 *
 * clock function (see: time.h).
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

/* Set by firsta call to clock(). Subsequent calls are delta to
   this value. */
static time_t _first_clk = 0;

/* Return current clock in ticks 
   NOTE: Only works if CLOCKS_PER_SEC is in milliseconds! */
clock_t clock(void) {
    /* Read clock from platform */
    struct timeval tv;
    gettimeofday(&tv);
    if (_first_clk==0) {
        _first_clk=tv.tv_sec;
        return 0;
    } else 
        return (tv.tv_sec - _first_clk) * CLOCKS_PER_SEC 
            + tv.tv_hsec * (CLOCKS_PER_SEC / 100);
}

#endif /* !LEAN_AND_MEAN */