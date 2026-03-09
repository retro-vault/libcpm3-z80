/*
 * _leap.c
 *
 * Test whether a calendar year is a leap year; returns 1 or 0.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <time/_time.h>


/* leap year=1, otherwise 0 */
uint8_t _leap(int y) {
	if ( 
		(((y%4)==0) && ((y%100)!=0))	/* divisible by 4 but not by 100 ... */
		|| ((y%400)==0)					/* or divisible by 400 */
	) return 1;
	else return 0;
}

