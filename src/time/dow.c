#include <time/_time.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

/* Service function to calculates day of week */
uint8_t _dow(struct tm * ptim) {
    int d=ptim->tm_mday, m=ptim->tm_mon + 1, y=YEAR0 + ptim->tm_year;
    int weekday  = (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;  
    return weekday;
}

#endif /* !LEAN_AND_MEAN */