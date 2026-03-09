/*
 * _dow.c
 *
 * Compute the weekday index (0=Sunday) for a broken-down calendar date.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <time/_time.h>


/* Service function to calculates day of week */
uint8_t _dow(struct tm * ptim) {
    int d=ptim->tm_mday, m=ptim->tm_mon + 1, y=YEAR0 + ptim->tm_year;
    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;  
    return weekday;
}

