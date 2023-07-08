/*
 * _time.h
 *
 * Internal time.h.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#ifndef ___TIME_H__
#define ___TIME_H__

#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <util/leanmean.h>

#define YEAR0           1900
#define EPOCH_YR        1970
#define SEC_IN_MINUTE   60L
#define SEC_IN_HOUR     3600L
#define SEC_IN_DAY      86400L

/* We need a resolution of 1/100 sec. */
#define CLOCKS_PER_SEC  100L
typedef long clock_t;

/* Std C defines this as number of seconds since  00:00, Jan 1 1970 UTC */
typedef long time_t;

/* Std C tm struct */
struct tm {
    /* seconds,  range 0 to 59 */
    int tm_sec;
    /* minutes, range 0 to 59 */
    int tm_min;
    /* hours, range 0 to 23 */
    int tm_hour;
    /* day of the month, range 1 to 31 */
    int tm_mday;
    /* month, range 0 to 11 */
    int tm_mon;
    /* The number of years since 1900 */
    int tm_year;
    /* day of the week, range 0 to 6 */
    int tm_wday;
    /* day in the year, range 0 to 365 */
    int tm_yday;
    /* daylight saving time */
    int tm_isdst;
};

/* Non standard for settimeofday and gettimeofday functions */
struct timeval { 
    time_t tv_sec;                      /* seconds since Jan. 1, 1970 */ 
    int tv_hsec;                        /* and 1/100 sec */ 
}; 

/* days before month (sum), feb=28 */
extern const int _bmdays[];
/* days in month (for non-leap and leap years) */
extern const int _mdays[2][12];
/* month names */
extern const char *_months[];
/* day names */
extern const char *_days[];

/* days in month */
#define _dim(x,dfeb) ((x == 1) ? dfeb : mdays[x])
/* days in year */
#define _diy(year) (_leap(year) ? 366 : 365)

/* local time struct */
#define localtime gmtime
extern struct tm *gmtime(const time_t *timer);

/* Non standard function to get system date and time. */
extern int gettimeofday(struct timeval *tv);

/* Converts given calendar time tm to a textual representation of 
the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy. */
extern char* asctime(const struct tm* time_ptr);

/* is leap year? */
extern uint8_t _leap(int y);

/* day of year */
extern int _doy(struct tm * ptim);

#endif /* ___TIME_H___ */