/*
 * sys/bdos.h
 *
 * bdos calls for cp/m
 * 
 * NOTES:
 *  From http://www.tassos-oak.com/NB2/toolbook.html
 *  The BDOS is located at some address in high storage; that is, it begins at an address higher than the end of our program.
 *  We don't know what that address is. It varies from system to system, and it can vary from one command to the next in a single
 *  system, although it normally doesn't. However, there is always a jump instruction at location 5 (address 0005h) which is
 *  aimed at the lowest instruction in the BDOS.
 *  To call upon the BDOS, we need only place the correct arguments in registers and call location 5.
 *  One BDOS argument is a service number that specifies what we want done. It is always passed in register C.
 *  The other argument depends on the service being requested, but if it's a byte, it is passed in register E, and if a word, in DE.
 *  The second argument is the byte to be typed; it's passed in register E.
 *
 * Copyright (C) Douglas W. Goodall
 * For Non-Commercial use by N8VEM
 * 5/10/2011 dwg - initial version
 * hkzlab - modified version
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 27.04.2021   tstih
 *
 */
#ifndef __BDOS_H__
#define __BDOS_H__

#include <stdint.h>

/* exit codes */
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

/* CP/M 3 BDOS function codes
 * See here: https://www.seasip.info/Cpm/bdos.html
 */
#define P_TERMCPM       0
#define C_READ          1
#define C_WRITE         2
#define A_READ          3
#define A_WRITE         4
#define L_WRITE         5
#define C_RAWIO         6
#define DRV_SET         14
#define F_OPEN          15
#define F_CLOSE         16  
#define F_READ          20
#define DRV_LOGINVEC    24
#define DRV_GET         25
#define F_DMAOFF        26
#define DRV_DPB         31
#define F_USERNUM       32
#define SCB_GET         49
#define P_CODE          108             /* program ret code */

/* BDOS return code */
typedef struct bdos_ret_s {
    uint8_t reta;                       /* return code in reg A */
    uint8_t retb;                       /* return code in reg B */
    uint16_t rethl;                     /* return code in HL */
} bdos_ret_t;

/* call bdos, return register A */
extern uint8_t bdos(uint8_t fn, uint16_t param);

/* call bdos, return results */
extern bdos_ret_t *bdosret(uint8_t fn, uint16_t param, bdos_ret_t *p);

#endif /* __BDOS_H__ */