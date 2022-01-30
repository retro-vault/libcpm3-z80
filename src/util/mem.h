/*
 * mem.h
 *
 * Memory management utility functions.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 25.05.2012   tstih
 *
 */
#ifndef __MEM_H__
#define __MEM_H__

#include <stdint.h>
#include <string.h>

#include <util/list.h>

#ifndef NONE
#define NONE 0
#endif

#define BLK_SIZE        (sizeof(struct block_s) - sizeof(uint8_t[1]))
#define MIN_CHUNK_SIZE  4

/* block status, use as bit operations */
#define NEW             0x00
#define ALLOCATED       0x01

typedef struct block_s {
    list_header_t   hdr;
    uint8_t         stat;
    uint16_t        size;
    uint8_t         data[1];
} block_t;

/* Must be defined in crt0 */
extern void _heap;

/* Mem top. By convention this is start of BDOS, retreived from
   the 0x0005 address (BDOS call). This function can be "overrriden"
   by the PLATFORM= parameter. */
extern uint16_t* _memtop();

/* find first free block of appropriate size */
extern uint8_t _match_free_block(list_header_t *p, uint16_t size);

/* merge block with the next block */
extern void _merge_with_next(block_t *b);

/* split memory block into two blocks */
extern void _split(block_t *b, uint16_t size);

/* initialize memory management */
extern void _memory_init();

#endif /* __MEM_H__ */