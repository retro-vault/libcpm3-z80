/*
 * time.h
 *
 * Standard C header file for time functions.
 * Implemented functions are: asctime(), clock(), ctime(),
 * difftime(), gmtime(), mktime(), time().
 * 
 * NOTES:
 *  - daylight setting is not known so tm_isdst member of struct tm
 *    is set to -1
 *  - strftime() is not immplemented
 *  - non-standard: function settimmeofday() can be used to set Partners' 
 *    date and time (resolution = 1 second).
 *  - non-standard: difftime is long because SDCC does not impelement double
 *  - local time and gmtime are the same (WHAT?! i live in London...)
 *  - fixed resolution
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 22.05.2021   tstih
 *
 */
#ifndef __TIME_H__
#define __TIME_H__

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

/* Converts given calendar time tm to a textual representation of 
the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy. */
extern char* asctime(const struct tm* time_ptr);

/* Return current clock in 1/1000 seconds */
extern clock_t clock(void);

/* Convert current time to textual representation using the following
format Www Mmm dd hh:mm:ss yyyy (uses asctime...).*/
extern char* ctime(const time_t* ptt);

/* Returns difference between two time points in seconds! */
extern long difftime(time_t time_end,time_t time_beg);

/* Get Greenwich mean time (politically correct: UTC), make localtime
equal to UTC. */
#define localtime gmtime
extern struct tm *gmtime(const time_t *timer);

/* Create time_t given tm structure. */
extern time_t mktime(struct tm *tme);
	
/* Get current time. */
extern time_t time(time_t *arg);

/* Non standard function to get system date and time. */
extern int gettimeofday(struct timeval *tv);

/* Non standard function to set system date and time */
extern int settimeofday(const struct timeval *tv);

#endif /* __TIME_H__ */