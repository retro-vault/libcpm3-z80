/*
 * fcb.h
 *
 * CP/M file control block.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 10.08.2021   tstih
 *
 */
#ifndef __FCB_H__
#define __FCB_H__

#include <stdint.h>

typedef struct fcb_s {
	uint8_t drive;              /* 0 -> Searches in default disk drive */
	char filename[8];           /* file name ('?' means any char) */
	char filetype[3];           /* file type */
	uint8_t ex;                 /* extent */
   	uint16_t resv;              /* reserved for CP/M */
	uint8_t rc;                 /* records used in extent */
	uint8_t alb[16];            /* allocation blocks used */
	uint8_t seqreq;             /* sequential records to read/write */
	uint16_t rrec;              /* rand record to read/write */ 
	uint8_t rrecob;             /* rand record overflow byte (MS) */
} fcb_t; /* File Control Block */

extern void _to_fcb_name(char *dst, char *src, uint8_t maxlen);

#endif /* __FCB_H__ */