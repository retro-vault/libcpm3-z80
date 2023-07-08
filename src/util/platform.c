/*
 * platform.c
 *
 * Empty platform functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.08.2012   tstih
 *
 */
#include <stddef.h>
#include <stdlib.h>
#include <time.h>

#include <util/leanmean.h>

/* If platform is defined but has no value 
   I modified hack from here
   https://stackoverflow.com/questions/3781520/how-to-test-if-preprocessor-symbol-is-defined-but-has-no-value */
#if !defined(PLATFORM) || (EXPAND(PLATFORM) == 1) 

/* Identified platform */
char *libplatform="z80-none";

/* init hook */
void libinit() {}

/* mem top */
size_t _memtop() {
    /* Default top is BDOS. */
    size_t *ptr=(size_t *)0x0006;
    return *ptr;
}

/* Non standard function to sleep (in milliseconds) */
void msleep(int millisec) {
    millisec;
}

#ifndef LEAN_AND_MEAN

/* Non standard function to set system date and time */
int settimeofday(const struct timeval *tv) {
    tv;
    return 0;
}

/* Non standard function to get system date and time,
   return 1.1.2021, zone 0, daylight saving 0. */
#define TV_SEC_20210101 1609459200      /* 1.1.2021 00:00:00 */
int gettimeofday(struct timeval *tv) {
    tv->tv_sec=TV_SEC_20210101;
    tv->tv_hsec=0;
    return 0;
}

#endif /* LEAN_AND_MEAN */

#else

/* hack: https://stackoverflow.com/questions/240353/convert-a-preprocessor-token-to-a-string */
#define STRINGIFY(VAL)  #VAL
#define TOSTRING(VAL)   STRINGIFY(VAL)
#define PLAT_NAME "z80-" TOSTRING(PLATFORM)
char *libplatform=PLAT_NAME;

#endif