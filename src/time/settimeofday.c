/*
 * settimeofday.c
 *
 * Set system time via CP/M 3 BDOS T_SET (function 104).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 17.02.2026   tstih
 *
 */
#include <stdint.h>
#include <errno.h>
#include <time/_time.h>
#include <sys/bdos.h>

/* CP/M 3 date/time record written by T_SET (BDOS 104).
   Day 1 = 1 January 1978.  Hours and minutes are BCD-encoded. */
typedef struct {
    uint16_t days;      /* days since 1 Jan 1978, 1-based */
    uint8_t  hour;      /* hours,   BCD (0x00-0x23) */
    uint8_t  min;       /* minutes, BCD (0x00-0x59) */
} cpm_time_t;

/* Days between the Unix epoch (1 Jan 1970) and the CP/M epoch
   (1 Jan 1978): 8 years with leap years 1972 and 1976. */
#define CPM_EPOCH_OFFSET  2922L

static uint8_t bin2bcd(uint8_t bin) {
    return (uint8_t)(((bin / 10) << 4) | (bin % 10));
}

int settimeofday(const struct timeval *tv) {
    if (tv == NULL) {
        errno = EINVAL;
        return -1;
    }

    long unix_days = tv->tv_sec / SEC_IN_DAY;
    long remaining = tv->tv_sec % SEC_IN_DAY;
    int  hours     = (int)(remaining / SEC_IN_HOUR);
    int  minutes   = (int)((remaining % SEC_IN_HOUR) / SEC_IN_MINUTE);

    long cpm_days = unix_days - CPM_EPOCH_OFFSET + 1L;
    if (cpm_days < 1L || cpm_days > 65535L) {
        errno = EINVAL;
        return -1;
    }

    cpm_time_t ct;
    ct.days = (uint16_t)cpm_days;
    ct.hour = bin2bcd((uint8_t)hours);
    ct.min  = bin2bcd((uint8_t)minutes);

    bdos(T_SET, (uint16_t)&ct);
    return 0;
}
