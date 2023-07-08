/*
 * mktime.c
 *
 * mktime function (see: time.h).
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

/* Create time_t given tm structure */
time_t mktime(struct tm *ptim) {
    /* update tm_yday */
    ptim->tm_yday=_doy(ptim);
    /* and return... */
    return 
        ptim->tm_sec 
        + ptim->tm_min*SEC_IN_MINUTE 
        + ptim->tm_hour*SEC_IN_HOUR 
        + ptim->tm_yday*SEC_IN_DAY 
        + (ptim->tm_year-70)*31536000 
        + ((ptim->tm_year-69)/4)*SEC_IN_DAY 
        - ((ptim->tm_year-1)/100)*SEC_IN_DAY 
        + ((ptim->tm_year+299)/400)*SEC_IN_DAY;
}

#endif /* !LEAN_AND_MEAN */