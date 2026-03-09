/*
 * gettimeofday.c
 *
 * Read the current CP/M 3 clock via BDOS T_GET and fill a timeval struct.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <stdint.h>
#include <time/_time.h>
#include <sys/bdos.h>

/* CP/M 3 date/time record as returned by T_GET (BDOS 105).
   Day 1 = 1 January 1978.  Hours and minutes are BCD-encoded. */
typedef struct _cpm_time_s {
    uint16_t days;      /* days since 1 Jan 1978, 1-based */
    uint8_t  hour;      /* hours,   BCD (0x00-0x23) */
    uint8_t  min;       /* minutes, BCD (0x00-0x59) */
} _cpm_time_t;

/* Days between the Unix epoch (1 Jan 1970) and the CP/M epoch
   (1 Jan 1978): 8 years with leap years 1972 and 1976. */
#define CPM_EPOCH_OFFSET  2922L

static uint8_t _bcd2bin(uint8_t bcd) {
    return (uint8_t)(((bcd >> 4) * 10) + (bcd & 0x0f));
}

int gettimeofday(struct timeval *tv) {
    _cpm_time_t ct;
    /* T_GET returns seconds (BCD) in register A */
    uint8_t sec_bcd = bdos(T_GET, (uint16_t)&ct);

    long unix_days = (long)(ct.days - 1) + CPM_EPOCH_OFFSET;
    int  hours     = _bcd2bin(ct.hour);
    int  minutes   = _bcd2bin(ct.min);
    int  seconds   = _bcd2bin(sec_bcd);

    tv->tv_sec  = unix_days * SEC_IN_DAY
                + (long)hours   * SEC_IN_HOUR
                + (long)minutes * SEC_IN_MINUTE
                + (long)seconds;
    tv->tv_hsec = 0;
    return 0;
}
