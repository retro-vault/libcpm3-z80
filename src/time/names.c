/*
 * names.c
 *
 * Names for days and months.
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

/* day names */
const char *_days[7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

/* month names */
const char *_months[12] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};

#endif /* !LEAN_AND_MEAN */