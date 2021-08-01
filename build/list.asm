;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12391 (Linux)
;--------------------------------------------------------
	.module list
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl __list_match_eq
	.globl __list_find
	.globl __list_insert
	.globl __list_append
	.globl __list_remove
	.globl __list_remove_first
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
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
	G$_list_match_eq$0$0	= .
	.globl	G$_list_match_eq$0$0
	C$list.c$14$0_0$21	= .
	.globl	C$list.c$14$0_0$21
;util/list.c:14: uint8_t _list_match_eq(list_header_t *p, uint16_t arg) {
;	---------------------------------
; Function _list_match_eq
; ---------------------------------
__list_match_eq::
	C$list.c$15$1_0$21	= .
	.globl	C$list.c$15$1_0$21
;util/list.c:15: return ( ((uint16_t)p) == arg );
	pop	hl
	pop	bc
	push	bc
	push	hl
	ld	iy, #4
	add	iy, sp
	ld	l, 0 (iy)
	ld	h, 1 (iy)
	cp	a, a
	sbc	hl, bc
	ld	a, #0x01
	jr	Z, 00104$
	xor	a, a
00104$:
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	C$list.c$16$1_0$21	= .
	.globl	C$list.c$16$1_0$21
;util/list.c:16: }
	C$list.c$16$1_0$21	= .
	.globl	C$list.c$16$1_0$21
	XG$_list_match_eq$0$0	= .
	.globl	XG$_list_match_eq$0$0
	ret
	G$_list_find$0$0	= .
	.globl	G$_list_find$0$0
	C$list.c$18$1_0$24	= .
	.globl	C$list.c$18$1_0$24
;util/list.c:18: list_header_t* _list_find(
;	---------------------------------
; Function _list_find
; ---------------------------------
__list_find::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$list.c$25$1_0$24	= .
	.globl	C$list.c$25$1_0$24
;util/list.c:25: *prev=NULL;
	ld	c, 6 (ix)
	ld	b, 7 (ix)
	ld	l, c
	ld	h, b
	xor	a, a
	ld	(hl), a
	inc	hl
	ld	(hl), a
	C$list.c$26$1_0$24	= .
	.globl	C$list.c$26$1_0$24
;util/list.c:26: while (first && !match(first,the_arg)) {
00102$:
	ld	a, 5 (ix)
	or	a, 4 (ix)
	jr	Z, 00104$
	push	bc
	ld	l, 10 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 11 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, 8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	call	___sdcc_call_hl
	pop	af
	pop	af
	ld	a, l
	pop	bc
	or	a, a
	jr	NZ, 00104$
	C$list.c$27$2_0$25	= .
	.globl	C$list.c$27$2_0$25
;util/list.c:27: *prev=first;
	ld	l, c
	ld	h, b
	ld	a, 4 (ix)
	ld	(hl), a
	inc	hl
	ld	a, 5 (ix)
	ld	(hl), a
	C$list.c$28$2_0$25	= .
	.globl	C$list.c$28$2_0$25
;util/list.c:28: first=first->next;
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	a, (hl)
	inc	hl
	ld	e, (hl)
	ld	4 (ix), a
	ld	5 (ix), e
	jr	00102$
00104$:
	C$list.c$31$1_0$24	= .
	.globl	C$list.c$31$1_0$24
;util/list.c:31: return first; 
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	C$list.c$32$1_0$24	= .
	.globl	C$list.c$32$1_0$24
;util/list.c:32: }
	pop	ix
	C$list.c$32$1_0$24	= .
	.globl	C$list.c$32$1_0$24
	XG$_list_find$0$0	= .
	.globl	XG$_list_find$0$0
	ret
	G$_list_insert$0$0	= .
	.globl	G$_list_insert$0$0
	C$list.c$34$1_0$27	= .
	.globl	C$list.c$34$1_0$27
;util/list.c:34: list_header_t *_list_insert(list_header_t** first, list_header_t *el) {
;	---------------------------------
; Function _list_insert
; ---------------------------------
__list_insert::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$list.c$35$1_0$27	= .
	.globl	C$list.c$35$1_0$27
;util/list.c:35: el->next=*first;
	ld	e, 6 (ix)
	ld	d, 7 (ix)
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	l, c
	ld	h, b
	inc	hl
	ld	a, (hl)
	dec	hl
	ld	l, (hl)
;	spillPairReg hl
	ld	-2 (ix), l
	ld	-1 (ix), a
	ld	l, e
	ld	h, d
	ld	a, -2 (ix)
	ld	(hl), a
	inc	hl
	ld	a, -1 (ix)
	ld	(hl), a
	C$list.c$36$1_0$27	= .
	.globl	C$list.c$36$1_0$27
;util/list.c:36: *first=el;
	ld	a, e
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
	C$list.c$37$1_0$27	= .
	.globl	C$list.c$37$1_0$27
;util/list.c:37: return el;
	ex	de, hl
	C$list.c$38$1_0$27	= .
	.globl	C$list.c$38$1_0$27
;util/list.c:38: }
	ld	sp, ix
	pop	ix
	C$list.c$38$1_0$27	= .
	.globl	C$list.c$38$1_0$27
	XG$_list_insert$0$0	= .
	.globl	XG$_list_insert$0$0
	ret
	G$_list_append$0$0	= .
	.globl	G$_list_append$0$0
	C$list.c$40$1_0$29	= .
	.globl	C$list.c$40$1_0$29
;util/list.c:40: list_header_t *_list_append(list_header_t** first, list_header_t *el) {
;	---------------------------------
; Function _list_append
; ---------------------------------
__list_append::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$list.c$44$1_0$29	= .
	.globl	C$list.c$44$1_0$29
;util/list.c:44: el->next=NULL;		/* it's always the last element */
	ld	c, 6 (ix)
	ld	b, 7 (ix)
	ld	l, c
	ld	h, b
	xor	a, a
	ld	(hl), a
	inc	hl
	ld	(hl), a
	C$list.c$46$1_0$29	= .
	.globl	C$list.c$46$1_0$29
;util/list.c:46: if (*first==NULL)	/* empty list? */
	ld	e, 4 (ix)
	ld	d, 5 (ix)
	ld	a, (de)
	ld	-2 (ix), a
	inc	de
	ld	a, (de)
	ld	-1 (ix), a
	dec	de
	ld	a, -1 (ix)
	or	a, -2 (ix)
	jr	NZ, 00105$
	C$list.c$47$1_0$29	= .
	.globl	C$list.c$47$1_0$29
;util/list.c:47: *first=el;
	ld	a, c
	ld	(de), a
	inc	de
	ld	a, b
	ld	(de), a
	jr	00106$
00105$:
	C$list.c$49$2_0$30	= .
	.globl	C$list.c$49$2_0$30
;util/list.c:49: current=*first;
	pop	hl
	push	hl
	C$list.c$50$2_0$30	= .
	.globl	C$list.c$50$2_0$30
;util/list.c:50: while (current->next) current=current->next;
00101$:
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	dec	hl
	ld	a, d
	or	a, e
	jr	Z, 00103$
	ex	de, hl
	jr	00101$
00103$:
	C$list.c$51$2_0$30	= .
	.globl	C$list.c$51$2_0$30
;util/list.c:51: current->next=el;
	ld	a, 6 (ix)
	ld	e, 7 (ix)
	ld	(hl), a
	inc	hl
	ld	(hl), e
00106$:
	C$list.c$53$1_0$29	= .
	.globl	C$list.c$53$1_0$29
;util/list.c:53: return el;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	C$list.c$54$1_0$29	= .
	.globl	C$list.c$54$1_0$29
;util/list.c:54: }
	ld	sp, ix
	pop	ix
	C$list.c$54$1_0$29	= .
	.globl	C$list.c$54$1_0$29
	XG$_list_append$0$0	= .
	.globl	XG$_list_append$0$0
	ret
	G$_list_remove$0$0	= .
	.globl	G$_list_remove$0$0
	C$list.c$56$1_0$32	= .
	.globl	C$list.c$56$1_0$32
;util/list.c:56: list_header_t *_list_remove(list_header_t **first, list_header_t *el) {
;	---------------------------------
; Function _list_remove
; ---------------------------------
__list_remove::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	C$list.c$58$1_0$32	= .
	.globl	C$list.c$58$1_0$32
;util/list.c:58: if (el==*first) {
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	C$list.c$59$1_0$32	= .
	.globl	C$list.c$59$1_0$32
;util/list.c:59: *first=el->next;
	ld	a, 6 (ix)
	ld	-2 (ix), a
	ld	a, 7 (ix)
	ld	-1 (ix), a
	C$list.c$58$1_0$32	= .
	.globl	C$list.c$58$1_0$32
;util/list.c:58: if (el==*first) {
	ld	l, 6 (ix)
	ld	h, 7 (ix)
	cp	a, a
	sbc	hl, de
	jr	NZ, 00105$
	C$list.c$59$2_0$33	= .
	.globl	C$list.c$59$2_0$33
;util/list.c:59: *first=el->next;
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
	jr	00106$
00105$:
	C$list.c$61$2_0$34	= .
	.globl	C$list.c$61$2_0$34
;util/list.c:61: if (!_list_find(*first, &prev, _list_match_eq, (uint16_t) el))
	ld	c, 6 (ix)
	ld	b, 7 (ix)
	ld	hl, #0
	add	hl, sp
	push	bc
	ld	bc, #__list_match_eq
	push	bc
	push	hl
	push	de
	call	__list_find
	pop	af
	pop	af
	pop	af
	pop	af
	ld	a, h
	or	a, l
	jr	NZ, 00102$
	C$list.c$62$2_0$34	= .
	.globl	C$list.c$62$2_0$34
;util/list.c:62: return NULL;
	ld	hl, #0x0000
	jr	00107$
00102$:
	C$list.c$64$2_0$34	= .
	.globl	C$list.c$64$2_0$34
;util/list.c:64: prev->next=el->next;
	pop	bc
	push	bc
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	ld	(bc), a
	inc	bc
	ld	a, d
	ld	(bc), a
00106$:
	C$list.c$66$1_0$32	= .
	.globl	C$list.c$66$1_0$32
;util/list.c:66: return el;
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
00107$:
	C$list.c$67$1_0$32	= .
	.globl	C$list.c$67$1_0$32
;util/list.c:67: }
	ld	sp, ix
	pop	ix
	C$list.c$67$1_0$32	= .
	.globl	C$list.c$67$1_0$32
	XG$_list_remove$0$0	= .
	.globl	XG$_list_remove$0$0
	ret
	G$_list_remove_first$0$0	= .
	.globl	G$_list_remove_first$0$0
	C$list.c$69$1_0$36	= .
	.globl	C$list.c$69$1_0$36
;util/list.c:69: list_header_t *_list_remove_first(list_header_t **first) {
;	---------------------------------
; Function _list_remove_first
; ---------------------------------
__list_remove_first::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$list.c$71$1_0$36	= .
	.globl	C$list.c$71$1_0$36
;util/list.c:71: if (*first==NULL) return NULL; /* empty list */
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	l, c
	ld	h, b
	ld	a, (hl)
	inc	hl
	ld	h, (hl)
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
	ld	l,a
	or	a,h
	jr	NZ, 00102$
	ld	hl, #0x0000
	jr	00103$
00102$:
	C$list.c$72$1_0$36	= .
	.globl	C$list.c$72$1_0$36
;util/list.c:72: result=*first;
	ld	e, l
	ld	d, h
	C$list.c$73$1_0$36	= .
	.globl	C$list.c$73$1_0$36
;util/list.c:73: *first = (list_header_t*) ((*first)->next);
	ld	a, (hl)
	inc	hl
	ld	l, (hl)
;	spillPairReg hl
	ld	-2 (ix), a
	ld	-1 (ix), l
	ld	a, -2 (ix)
	ld	(bc), a
	inc	bc
	ld	a, -1 (ix)
	ld	(bc), a
	C$list.c$74$1_0$36	= .
	.globl	C$list.c$74$1_0$36
;util/list.c:74: return result;
	ex	de, hl
00103$:
	C$list.c$75$1_0$36	= .
	.globl	C$list.c$75$1_0$36
;util/list.c:75: }
	ld	sp, ix
	pop	ix
	C$list.c$75$1_0$36	= .
	.globl	C$list.c$75$1_0$36
	XG$_list_remove_first$0$0	= .
	.globl	XG$_list_remove_first$0$0
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
