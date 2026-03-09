/*
 * ctime.c
 *
 * Convert a time_t value to a fixed 25-character text string.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <time/_time.h>


/* Convert current time to textual representation using the following
format Www Mmm dd hh:mm:ss yyyy (uses asctime...)*/
char* ctime(const time_t* ptt) {
    return asctime(localtime(ptt));
}

