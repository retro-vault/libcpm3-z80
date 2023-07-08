#include <time/_time.h>

/* Exclude all for LEAN_AND_MEAN */
#ifndef LEAN_AND_MEAN

/* days before month (sum), feb=28 */
const int _bmdays[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

/* days in month (for non-leap and leap years) */
const int _mdays[2][12] = {
  {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

#endif /* !LEAN_AND_MEAN */