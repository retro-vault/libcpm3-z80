;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12391 (Linux)
;--------------------------------------------------------
	.module ctype
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _strchr
	.globl _isalpha
	.globl _isspace
	.globl _ispunct
	.globl _tolower
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
Lctype.ispunct$punct$1_0$25==.
_ispunct_punct_65536_25:
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
	G$ispunct$0$0	= .
	.globl	G$ispunct$0$0
	C$ctype.c$28$1_0$25	= .
	.globl	C$ctype.c$28$1_0$25
;ctype.c:28: static const char *punct = ".;!?...";
	ld	hl, #___str_0+0
	ld	(_ispunct_punct_65536_25), hl
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	G$isalpha$0$0	= .
	.globl	G$isalpha$0$0
	C$ctype.c$16$0_0$21	= .
	.globl	C$ctype.c$16$0_0$21
;ctype.c:16: bool isalpha(int c)
;	---------------------------------
; Function isalpha
; ---------------------------------
_isalpha::
	C$ctype.c$18$1_0$21	= .
	.globl	C$ctype.c$18$1_0$21
;ctype.c:18: return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	ld	iy, #2
	add	iy, sp
	ld	a, 0 (iy)
	sub	a, #0x61
	ld	a, 1 (iy)
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	C, 00108$
	ld	a, #0x7a
	cp	a, 0 (iy)
	ld	a, #0x00
	sbc	a, 1 (iy)
	jp	PO, 00122$
	xor	a, #0x80
00122$:
	jp	P, 00104$
00108$:
	ld	iy, #2
	add	iy, sp
	ld	a, 0 (iy)
	sub	a, #0x41
	ld	a, 1 (iy)
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	C, 00103$
	ld	a, #0x5a
	cp	a, 0 (iy)
	ld	a, #0x00
	sbc	a, 1 (iy)
	jp	PO, 00123$
	xor	a, #0x80
00123$:
	jp	P, 00104$
00103$:
	ld	l, #0x00
;	spillPairReg hl
;	spillPairReg hl
	jr	00105$
00104$:
	ld	l, #0x01
;	spillPairReg hl
;	spillPairReg hl
00105$:
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	C$ctype.c$19$1_0$21	= .
	.globl	C$ctype.c$19$1_0$21
;ctype.c:19: }
	C$ctype.c$19$1_0$21	= .
	.globl	C$ctype.c$19$1_0$21
	XG$isalpha$0$0	= .
	.globl	XG$isalpha$0$0
	ret
	G$isspace$0$0	= .
	.globl	G$isspace$0$0
	C$ctype.c$21$1_0$23	= .
	.globl	C$ctype.c$21$1_0$23
;ctype.c:21: bool isspace(int c)
;	---------------------------------
; Function isspace
; ---------------------------------
_isspace::
	C$ctype.c$23$1_0$23	= .
	.globl	C$ctype.c$23$1_0$23
;ctype.c:23: return c == ' ' || c == '\t'; // || whatever other char you consider space
	ld	iy, #2
	add	iy, sp
	ld	a, 0 (iy)
	sub	a, #0x20
	or	a, 1 (iy)
	jr	Z, 00104$
	ld	a, 0 (iy)
	sub	a, #0x09
	or	a, 1 (iy)
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
	ld	l, #0x00
	jr	NZ, 00105$
00104$:
	ld	l, #0x01
00105$:
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	C$ctype.c$24$1_0$23	= .
	.globl	C$ctype.c$24$1_0$23
;ctype.c:24: }
	C$ctype.c$24$1_0$23	= .
	.globl	C$ctype.c$24$1_0$23
	XG$isspace$0$0	= .
	.globl	XG$isspace$0$0
	ret
	G$ispunct$0$0	= .
	.globl	G$ispunct$0$0
	C$ctype.c$26$1_0$25	= .
	.globl	C$ctype.c$26$1_0$25
;ctype.c:26: bool ispunct(int c)
;	---------------------------------
; Function ispunct
; ---------------------------------
_ispunct::
	C$ctype.c$29$1_0$25	= .
	.globl	C$ctype.c$29$1_0$25
;ctype.c:29: return strchr(punct, c) == NULL ? FALSE : TRUE; // you can make this shorter
	pop	de
	pop	hl
	push	hl
	push	de
	push	hl
	ld	hl, (_ispunct_punct_65536_25)
	push	hl
	call	_strchr
	pop	af
	pop	af
	ld	a, h
	or	a, l
	jr	NZ, 00103$
	ld	hl, #0x0000
	ret
00103$:
	ld	hl, #0x0001
	C$ctype.c$30$1_0$25	= .
	.globl	C$ctype.c$30$1_0$25
;ctype.c:30: }
	C$ctype.c$30$1_0$25	= .
	.globl	C$ctype.c$30$1_0$25
	XG$ispunct$0$0	= .
	.globl	XG$ispunct$0$0
	ret
Fctype$__str_0$0_0$0 == .
___str_0:
	.ascii ".;!?..."
	.db 0x00
	G$tolower$0$0	= .
	.globl	G$tolower$0$0
	C$ctype.c$32$1_0$27	= .
	.globl	C$ctype.c$32$1_0$27
;ctype.c:32: int tolower(int c)
;	---------------------------------
; Function tolower
; ---------------------------------
_tolower::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$ctype.c$34$1_0$27	= .
	.globl	C$ctype.c$34$1_0$27
;ctype.c:34: if ( !isalpha(c) ) return c;
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	call	_isalpha
	pop	af
	ld	a, h
	or	a, l
	jr	NZ, 00102$
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	jr	00103$
00102$:
	C$ctype.c$35$1_0$27	= .
	.globl	C$ctype.c$35$1_0$27
;ctype.c:35: return (c >= 'A' && c <= 'Z') ? c + 32 : c;
	ld	a, 4 (ix)
	sub	a, #0x41
	ld	a, 5 (ix)
	rla
	ccf
	rra
	sbc	a, #0x80
	jr	C, 00105$
	ld	a, #0x5a
	cp	a, 4 (ix)
	ld	a, #0x00
	sbc	a, 5 (ix)
	jp	PO, 00124$
	xor	a, #0x80
00124$:
	jp	M, 00105$
	ld	l, 4 (ix)
	ld	h, 5 (ix)
	ld	de, #0x0020
	add	hl, de
	jr	00106$
00105$:
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
00106$:
00103$:
	C$ctype.c$36$1_0$27	= .
	.globl	C$ctype.c$36$1_0$27
;ctype.c:36: }
	pop	ix
	C$ctype.c$36$1_0$27	= .
	.globl	C$ctype.c$36$1_0$27
	XG$tolower$0$0	= .
	.globl	XG$tolower$0$0
	ret
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
