/*
 * time.c
 *
 * Time functions: asctime(), clock(), ctime(), difftime(), 
 * gmtime(), mktime(), time(), settimmeofday().
 * 
 * NOTES:
 *  The clock modification is problematic.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 22.05.2021   tstih
 *
 */
#include <stdint.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#include <util/leanmean.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

/* Partner ports */
#define THOUS_S 0xa0
#define HUNDR_S 0xa1
#define SECOND  0xa2
#define MINUTE  0xa3
#define HOUR    0xa4
#define WDAY    0xa5
#define MDAY    0xa6
#define MONTH   0xa7
#define YEAR    0xa9 /* fake 2 digit year, from CMOS memory */

#define YEAR0           1900
#define EPOCH_YR        1970
#define SEC_IN_MINUTE   60L
#define SEC_IN_HOUR     3600L
#define SEC_IN_DAY      86400L

/* days before month (sum), feb=28 */
static int _bmdays[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/* days in month (for non-leap and leap years) */
static int _mdays[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* Set by firsta call to clock(). Subsequent calls are delta to
   this value. */
static time_t _first_clk = 0;

/* days in month */
#define _dim(x,dfeb) ((x == 1) ? dfeb : mdays[x])
/* days in year */
#define _diy(year) (_leap(year) ? 366 : 365)

/* day names */
static const char *_days[7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

/* month names */
static const char *_months[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

/* buffers for functions returning pointers */
static char _at[26]; 
static struct tm _tmi;

/* leap year=1, otherwise 0 */
uint8_t _leap(int y) {
	if ( 
		(((y%4)==0) && ((y%100)!=0))	/* divisible by 4 but not by 100 ... */
		|| ((y%400)==0)					/* or divisible by 400 */
	) return 1;
	else return 0;
}

/* Service function to calculates day of week */
uint8_t _dow(struct tm * ptim) {
    int d=ptim->tm_mday, m=ptim->tm_mon + 1, y=YEAR0 + ptim->tm_year;
    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;  
    return weekday;
}

/* Service function to calculate day of year */
int _doy(struct tm * ptim) {
    int days = ptim->tm_mday - 1; /* day of month 1 based */
    days += _bmdays[ptim->tm_mon]; /* plus days before month */
    if (ptim->tm_mon > 1 && _diy(ptim->tm_year) == 366)
        days++; /* adjust for february */
    /* compute day of the year, and return */
    return days;
}

/* Converts given calendar time tm to a textual representation of 
the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy\n */
char* asctime(const struct tm* pt) {

    char www[4], mmm[4];

    /* copy Www first... */
    strncpy(www,_days[pt->tm_wday],3);

    /* Now Mmm */
    strncpy(mmm,_months[pt->tm_mon],3);

    /* and now format... */
    sprintf(_at,"%s %s %02d %02d:%02d:%02d %04d", www, mmm, pt->tm_mday,
        pt->tm_hour, pt->tm_min, pt->tm_sec,
        1900 +  pt->tm_year
        );

    return &(_at[0]); /* return ptr to internal buffer (unsafe, I know) */
}

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

/* Convert current time to textual representation using the following
format Www Mmm dd hh:mm:ss yyyy (uses asctime...)*/
char* ctime(const time_t* ptt) {
    return asctime(localtime(ptt));
}

/* Returns difference between two time points in seconds! */
long difftime(time_t time_end,time_t time_beg) {
    return time_end-time_beg;
}

/* Get Greenwich mean time (politically correct: UTC) */
struct tm *gmtime(const time_t *timer) {

    time_t time=*timer;

    long days, rem;
    int y;
    int *ip;
   
    days = ((long)time) / SEC_IN_DAY;
    rem = ((long)time) % SEC_IN_DAY;

    while (rem < 0)  { rem += SEC_IN_DAY; --days; }
    while (rem >= SEC_IN_DAY) { rem -= SEC_IN_DAY; ++days; }
 
    /* compute hour, min, and sec */  
    _tmi.tm_hour = (int) (rem / SEC_IN_HOUR);
    rem %= SEC_IN_HOUR;
    _tmi.tm_min = (int) (rem / SEC_IN_MINUTE);
    _tmi.tm_sec = (int) (rem % SEC_IN_MINUTE);

    /* compute day of week */
    if ((_tmi.tm_wday = ((4 + days) % 7)) < 0)
        _tmi.tm_wday = _tmi.tm_wday +  7;

    /* compute year & day of year */
    y = EPOCH_YR;
    if (days >= 0) {
        for (;;) {
            if (days < _diy(y))
                break;
            y++;
            days -= _diy(y);
        }
    } else {
        do {
            --y;
            days += _diy(y);
        } while (days < 0);
    }

    _tmi.tm_year = y - YEAR0;
    _tmi.tm_yday = days;
    ip = _mdays[_leap(y)];
    for (_tmi.tm_mon = 0; days >= ip[_tmi.tm_mon]; ++(_tmi.tm_mon))
        days = days - ip[_tmi.tm_mon];
        
    _tmi.tm_mday = days + 1 + _leap(y);

    /* return internal static structure */
    return &_tmi;
}


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

#endif /* LEAN_AND_MEAN */