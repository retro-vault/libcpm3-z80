/*
 * limits.h
 *
 * Standard C Limits.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 19.06.2021   tstih
 *
 */
#ifndef __LIMITS_H__
#define __LIMITS_H__

#define CHAR_BIT    8                   /* Bits in char. */
#define SCHAR_MIN   -128
#define SCHAR_MAX   +127
#define UCHAR_MAX   255
#define CHAR_MIN    -128
#define CHAR_MAX    +127
#define MB_LEN_MAX  8                   /* Max. bytes in multi byte char. */
#define SHRT_MIN    -128
#define SHRT_MAX    +127
#define USHRT_MAX   255
#define INT_MIN     -32768
#define INT_MAX     +32767
#define UINT_MAX    65535
#define LONG_MIN    -2147483648
#define LONG_MAX    +2147483647
#define ULONG_MAX   4294967295
#define SSIZE_MAX   65535               /* Max bytes for file read */

#endif /* __LIMITS_H__ */