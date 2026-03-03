/*
 * asctime.c
 *
 * asctime function (see: time.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
 *
 */
#include <time/_time.h>


/* buffers for functions returning pointers */
static char _at[26]; 

/* Converts given calendar time tm to a textual representation of 
the following fixed 25-character form: Www Mmm dd hh:mm:ss yyyy\n */
char* asctime(const struct tm* pt) {
    char www[4], mmm[4];
    const char *wday = "???";
    const char *mon = "???";

    if (pt->tm_wday >= 0 && pt->tm_wday < 7)
        wday = _days[pt->tm_wday];
    if (pt->tm_mon >= 0 && pt->tm_mon < 12)
        mon = _months[pt->tm_mon];

    /* copy Www first... */
    strncpy(www, wday, 3);
    www[3] = '\0';

    /* Now Mmm */
    strncpy(mmm, mon, 3);
    mmm[3] = '\0';

    /* and now format... */
    sprintf(_at,"%s %s %02d %02d:%02d:%02d %04d\n", www, mmm, pt->tm_mday,
        pt->tm_hour, pt->tm_min, pt->tm_sec,
        1900 +  pt->tm_year
        );

    return &(_at[0]); /* return ptr to internal buffer (unsafe, I know) */
}
