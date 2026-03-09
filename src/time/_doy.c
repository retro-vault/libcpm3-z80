/*
 * _doy.c
 *
 * Compute the zero-based day-of-year index for a calendar date.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <time/_time.h>


/* Service function to calculate day of year */
int _doy(struct tm * ptim) {
    int days = ptim->tm_mday - 1; /* day of month 1 based */
    days += _bmdays[ptim->tm_mon]; /* plus days before month */
    if (ptim->tm_mon > 1 && _diy(ptim->tm_year) == 366)
        days++; /* adjust for february */
    /* compute day of the year, and return */
    return days;
}

