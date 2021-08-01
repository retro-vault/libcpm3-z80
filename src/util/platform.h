/*
 * platform.h
 *
 * Platform specific functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.08.2021   tstih
 *
 */
#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <stdint.h>

/* Set system date and time. */
extern void set_time(
    uint8_t year, 
    uint8_t month, 
    uint8_t day,
    uint8_t hour, 
    uint8_t minute, 
    uint8_t second,
    uint8_t clocks);

/* Get system date and time. */
extern void get_time(
    uint8_t* year, 
    uint8_t* month, 
    uint8_t* day,
    uint8_t* hour, 
    uint8_t* minute, 
    uint8_t* second,
    uint8_t* clocks);

#endif /* __PLATFORM_H__ */