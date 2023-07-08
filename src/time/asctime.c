#include <time/_time.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

/* buffers for functions returning pointers */
static char _at[26]; 

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

#endif /* !LEAN_AND_MEAN */