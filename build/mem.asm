;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12391 (Linux)
;--------------------------------------------------------
	.module mem
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl __mem_top
	.globl __match_free_block
	.globl __merge_with_next
	.globl __split
	.globl __memory_init
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
G$_mem_top$0_0$0==.
__mem_top::
	.ds 2
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _INITIALIZED
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$_match_free_block$0$0	= .
	.globl	G$_match_free_block$0$0
	C$mem.c$17$0_0$54	= .
	.globl	C$mem.c$17$0_0$54
;util/mem.c:17: uint8_t _match_free_block(list_header_t *p, uint16_t size)
;	---------------------------------
; Function _match_free_block
; ---------------------------------
__match_free_block::
	C$mem.c$19$1_0$54	= .
	.globl	C$mem.c$19$1_0$54
;util/mem.c:19: block_t *b = (block_t *)p;
	pop	hl
	pop	bc
	push	bc
	push	hl
	C$mem.c$20$1_0$54	= .
	.globl	C$mem.c$20$1_0$54
;util/mem.c:20: return !(b->stat & ALLOCATED) && b->size >= size;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	ld	a, (hl)
	and	a,#0x01
	jr	NZ, 00103$
	ld	hl, #3
	add	hl, bc
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	hl, #4
	add	hl, sp
	ld	a, c
	sub	a, (hl)
	inc	hl
	ld	a, b
	sbc	a, (hl)
	jr	NC, 00104$
00103$:
	ld	l, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ret
00104$:
	ld	l, #0x01
;	spillPairReg hl
;	spillPairReg hl
	C$mem.c$21$1_0$54	= .
	.globl	C$mem.c$21$1_0$54
;util/mem.c:21: }
	C$mem.c$21$1_0$54	= .
	.globl	C$mem.c$21$1_0$54
	XG$_match_free_block$0$0	= .
	.globl	XG$_match_free_block$0$0
	ret
	G$_merge_with_next$0$0	= .
	.globl	G$_merge_with_next$0$0
	C$mem.c$23$1_0$56	= .
	.globl	C$mem.c$23$1_0$56
;util/mem.c:23: void _merge_with_next(block_t *b)
;	---------------------------------
; Function _merge_with_next
; ---------------------------------
__merge_with_next::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$mem.c$25$1_0$56	= .
	.globl	C$mem.c$25$1_0$56
;util/mem.c:25: block_t *bnext = b->hdr.next;
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	de
	pop	iy
	C$mem.c$26$1_0$56	= .
	.globl	C$mem.c$26$1_0$56
;util/mem.c:26: b->size += (BLK_SIZE + bnext->size);
	ld	hl, #0x0003
	add	hl, bc
	ex	(sp), hl
	pop	hl
	push	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	push	iy
	pop	hl
	inc	hl
	inc	hl
	inc	hl
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	inc	hl
	inc	hl
	inc	hl
	add	hl, de
	ex	de, hl
	pop	hl
	push	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
	C$mem.c$27$1_0$56	= .
	.globl	C$mem.c$27$1_0$56
;util/mem.c:27: b->hdr.next = bnext->hdr.next;
	ld	a, 0 (iy)
	ld	d, 1 (iy)
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
	C$mem.c$28$1_0$56	= .
	.globl	C$mem.c$28$1_0$56
;util/mem.c:28: }
	ld	sp, ix
	pop	ix
	C$mem.c$28$1_0$56	= .
	.globl	C$mem.c$28$1_0$56
	XG$_merge_with_next$0$0	= .
	.globl	XG$_merge_with_next$0$0
	ret
	G$_split$0$0	= .
	.globl	G$_split$0$0
	C$mem.c$30$1_0$58	= .
	.globl	C$mem.c$30$1_0$58
;util/mem.c:30: void _split(block_t *b, uint16_t size)
;	---------------------------------
; Function _split
; ---------------------------------
__split::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-6
	add	hl, sp
	ld	sp, hl
	C$mem.c$33$1_0$58	= .
	.globl	C$mem.c$33$1_0$58
;util/mem.c:33: nw = (block_t *)((uint16_t)(b->data) + size);
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	hl, #0x0005
	add	hl, bc
	ex	de, hl
	ld	l, 6 (ix)
	ld	h, 7 (ix)
	add	hl, de
	ex	(sp), hl
	C$mem.c$34$1_0$58	= .
	.globl	C$mem.c$34$1_0$58
;util/mem.c:34: nw->hdr.next = b->hdr.next;
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	pop	hl
	push	hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
	C$mem.c$35$1_0$58	= .
	.globl	C$mem.c$35$1_0$58
;util/mem.c:35: nw->size = b->size - (size + BLK_SIZE);
	ld	a, -6 (ix)
	add	a, #0x03
	ld	-4 (ix), a
	ld	a, -5 (ix)
	adc	a, #0x00
	ld	-3 (ix), a
	ld	hl, #0x0003
	add	hl, bc
	ld	-2 (ix), l
	ld	-1 (ix), h
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, 6 (ix)
	add	a, #0x05
	ld	e, a
	ld	a, 7 (ix)
	adc	a, #0x00
	ld	d, a
	cp	a, a
	sbc	hl, de
	ex	de, hl
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	(hl), e
	inc	hl
	ld	(hl), d
	C$mem.c$36$1_0$58	= .
	.globl	C$mem.c$36$1_0$58
;util/mem.c:36: nw->stat = b->stat;
	pop	de
	push	de
	inc	de
	inc	de
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	ld	a, (hl)
	ld	(de), a
	C$mem.c$39$1_0$58	= .
	.globl	C$mem.c$39$1_0$58
;util/mem.c:39: b->size = size;
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, 6 (ix)
	ld	(hl), a
	inc	hl
	ld	a, 7 (ix)
	ld	(hl), a
	C$mem.c$40$1_0$58	= .
	.globl	C$mem.c$40$1_0$58
;util/mem.c:40: b->hdr.next = nw;
	pop	de
	push	de
	ld	a, e
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
	C$mem.c$41$1_0$58	= .
	.globl	C$mem.c$41$1_0$58
;util/mem.c:41: }
	ld	sp, ix
	pop	ix
	C$mem.c$41$1_0$58	= .
	.globl	C$mem.c$41$1_0$58
	XG$_split$0$0	= .
	.globl	XG$_split$0$0
	ret
	G$_memory_init$0$0	= .
	.globl	G$_memory_init$0$0
	C$mem.c$50$1_0$59	= .
	.globl	C$mem.c$50$1_0$59
;util/mem.c:50: void _memory_init()
;	---------------------------------
; Function _memory_init
; ---------------------------------
__memory_init::
	C$mem.c$53$1_0$59	= .
	.globl	C$mem.c$53$1_0$59
;util/mem.c:53: _mem_top = (uint16_t *)0x0006;
	ld	hl, #0x0006
	ld	(__mem_top), hl
	C$mem.c$56$1_1$60	= .
	.globl	C$mem.c$56$1_1$60
;util/mem.c:56: uint16_t size=(uint16_t)(*_mem_top) - (uint16_t)&_heap;
	ld	c, (hl)
	inc	hl
	ld	b, (hl)
	ld	a, c
	sub	a, #<(__heap)
	ld	c, a
	ld	a, b
	sbc	a, #>(__heap)
	ld	b, a
	C$mem.c$59$1_1$60	= .
	.globl	C$mem.c$59$1_1$60
;util/mem.c:59: block_t *first = (block_t *)&_heap;
	C$mem.c$60$1_1$60	= .
	.globl	C$mem.c$60$1_1$60
;util/mem.c:60: first->hdr.next = NULL;
	ld	hl, #0x0000
	ld	(__heap), hl
	C$mem.c$61$1_1$60	= .
	.globl	C$mem.c$61$1_1$60
;util/mem.c:61: first->size = size - BLK_SIZE;
	ld	a, c
	add	a, #0xfb
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	ld	((__heap + 3)), bc
	C$mem.c$62$1_1$60	= .
	.globl	C$mem.c$62$1_1$60
;util/mem.c:62: first->stat = NEW;
	ld	hl, #(__heap + 2)
	ld	(hl), #0x00
	C$mem.c$63$1_1$59	= .
	.globl	C$mem.c$63$1_1$59
;util/mem.c:63: }
	C$mem.c$63$1_1$59	= .
	.globl	C$mem.c$63$1_1$59
	XG$_memory_init$0$0	= .
	.globl	XG$_memory_init$0$0
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
