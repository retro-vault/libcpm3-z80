/*
 * platform.c
 *
 * Empty platform (specific functions).
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.08.2012   tstih
 *
 */
#include <util/platform.h>

#if PLATFORM == 0

void set_time(
    uint8_t year, 
    uint8_t month, 
    uint8_t day,
    uint8_t hour, 
    uint8_t minute, 
    uint8_t second,
    uint8_t clocks) { 

    /* Prevent unreferenced args. warning */
    year; month; day; hour; minute; second; clocks;

}

void get_time(
    uint8_t* year, 
    uint8_t* month, 
    uint8_t* day,
    uint8_t* hour, 
    uint8_t* minute, 
    uint8_t* second,
    uint8_t* clocks) { 
    
    /* 1.1.2021 */
    *year=21; *month=*day=1;
    /* 00:00:00.00 */
    *hour=*minute=*second=*clocks=0;
}

#endif