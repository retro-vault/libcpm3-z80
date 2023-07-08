/*
 * ctime.c
 *
 * ctime function (see: time.h).
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

/* Convert current time to textual representation using the following
format Www Mmm dd hh:mm:ss yyyy (uses asctime...)*/
char* ctime(const time_t* ptt) {
    return asctime(localtime(ptt));
}

#endif /* !LEAN_AND_MEAN */