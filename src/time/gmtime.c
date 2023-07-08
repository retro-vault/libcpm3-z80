/*
 * gmtime.c
 *
 * gmtime function (see: time.h).
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

static struct tm _tmi;

/* Get Greenwich mean time (politically correct: UTC) */
struct tm *gmtime(const time_t *timer) {

    time_t time=*timer;

    long days, rem;
    int y;
    const int *ip;
   
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

#endif /* !LEAN_AND_MEAN */