/*
 * unistd.h
 *
 * A non-standard extension header to the Standard C library,
 * common on unix. Contains system and block file functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 07.08.2021   tstih
 *
 */
#ifndef __UNISTD_H__
#define __UNISTD_H__

/* Non standard function to sleep (in milliseconds).
   NOTE: The libcpm3-z80 only provides an empty proxy 
   to this function. If you want to use it you need to
   compile the libcpm3-z80 with the PLATFORM switch and
   inject your own implementation.  */
extern void msleep(int millisec);

#endif /* __UNISTD_H__ */