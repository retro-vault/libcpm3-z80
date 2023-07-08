/*
 * leap.c
 *
 * Leap year test.
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

/* leap year=1, otherwise 0 */
uint8_t _leap(int y) {
	if ( 
		(((y%4)==0) && ((y%100)!=0))	/* divisible by 4 but not by 100 ... */
		|| ((y%400)==0)					/* or divisible by 400 */
	) return 1;
	else return 0;
}

#endif /* !LEAN_AND_MEAN */