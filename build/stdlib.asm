;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12391 (Linux)
;--------------------------------------------------------
	.module stdlib
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _isspace
	.globl __split
	.globl __merge_with_next
	.globl __match_free_block
	.globl __list_find
	.globl __list_match_eq
	.globl _memset
	.globl __bdos
	.globl _exit
	.globl _abs
	.globl _atoi
	.globl _rand
	.globl _srand
	.globl _strtoul
	.globl _strtol
	.globl _malloc
	.globl _free
	.globl _calloc
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
Fstdlib$_next$0_0$0==.
__next:
	.ds 4
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
	G$exit$0$0	= .
	.globl	G$exit$0$0
	C$stdlib.c$20$0_0$45	= .
	.globl	C$stdlib.c$20$0_0$45
;stdlib.c:20: void exit(int status)
;	---------------------------------
; Function exit
; ---------------------------------
_exit::
	push	af
	dec	sp
	C$stdlib.c$24$2_0$46	= .
	.globl	C$stdlib.c$24$2_0$46
;stdlib.c:24: bdos_call_t bdc = { P_TERMCPM, { (uint16_t)0 } };
	ld	hl, #0
	add	hl, sp
	ld	(hl), #0x00
	ld	hl, #0
	add	hl, sp
	ex	de, hl
	ld	c, e
	ld	b, d
	inc	bc
	xor	a, a
	ld	(bc), a
	inc	bc
	ld	(bc), a
	C$stdlib.c$25$1_1$46	= .
	.globl	C$stdlib.c$25$1_1$46
;stdlib.c:25: _bdos(&bdc);
	push	de
	call	__bdos
	pop	af
	C$stdlib.c$26$1_1$45	= .
	.globl	C$stdlib.c$26$1_1$45
;stdlib.c:26: }
	pop	af
	inc	sp
	C$stdlib.c$26$1_1$45	= .
	.globl	C$stdlib.c$26$1_1$45
	XG$exit$0$0	= .
	.globl	XG$exit$0$0
	ret
	G$abs$0$0	= .
	.globl	G$abs$0$0
	C$stdlib.c$28$1_1$48	= .
	.globl	C$stdlib.c$28$1_1$48
;stdlib.c:28: int abs(int i)
;	---------------------------------
; Function abs
; ---------------------------------
_abs::
	C$stdlib.c$30$1_0$48	= .
	.globl	C$stdlib.c$30$1_0$48
;stdlib.c:30: return i < 0 ? -i : i;
	ld	hl, #0x3
	add	hl, sp
	bit	7, (hl)
	jr	Z, 00103$
	ld	hl, #2
	add	hl, sp
	xor	a, a
	sub	a, (hl)
	inc	hl
	ld	e, a
	sbc	a, a
	sub	a, (hl)
	ld	d, a
	jr	00104$
00103$:
	pop	hl
	pop	de
	push	de
	push	hl
00104$:
	ex	de, hl
	C$stdlib.c$31$1_0$48	= .
	.globl	C$stdlib.c$31$1_0$48
;stdlib.c:31: }
	C$stdlib.c$31$1_0$48	= .
	.globl	C$stdlib.c$31$1_0$48
	XG$abs$0$0	= .
	.globl	XG$abs$0$0
	ret
	G$atoi$0$0	= .
	.globl	G$atoi$0$0
	C$stdlib.c$33$1_0$50	= .
	.globl	C$stdlib.c$33$1_0$50
;stdlib.c:33: int atoi(const char *str)
;	---------------------------------
; Function atoi
; ---------------------------------
_atoi::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$stdlib.c$35$2_0$50	= .
	.globl	C$stdlib.c$35$2_0$50
;stdlib.c:35: int res = 0;
	C$stdlib.c$36$1_0$50	= .
	.globl	C$stdlib.c$36$1_0$50
;stdlib.c:36: for (int i = 0; str[i] != '\0'; ++i)
	ld	hl,#0x0000
	ld	e,l
	ld	d,h
00103$:
	ld	a, e
	add	a, 4 (ix)
	ld	c, a
	ld	a, d
	adc	a, 5 (ix)
	ld	b, a
	ld	a, (bc)
	ld	c, a
	or	a, a
	jr	Z, 00101$
	C$stdlib.c$37$2_0$51	= .
	.globl	C$stdlib.c$37$2_0$51
;stdlib.c:37: res = res * 10 + str[i] - '0';
	push	de
	ld	e, l
	ld	d, h
	add	hl, hl
	add	hl, hl
	add	hl, de
	add	hl, hl
	pop	de
	ld	b, #0x00
	add	hl, bc
	ld	a, l
	add	a, #0xd0
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, h
	adc	a, #0xff
	ld	h, a
;	spillPairReg hl
;	spillPairReg hl
	C$stdlib.c$36$2_0$51	= .
	.globl	C$stdlib.c$36$2_0$51
;stdlib.c:36: for (int i = 0; str[i] != '\0'; ++i)
	inc	de
	jr	00103$
00101$:
	C$stdlib.c$38$1_0$50	= .
	.globl	C$stdlib.c$38$1_0$50
;stdlib.c:38: return res;
	C$stdlib.c$39$1_0$50	= .
	.globl	C$stdlib.c$39$1_0$50
;stdlib.c:39: }
	pop	ix
	C$stdlib.c$39$1_0$50	= .
	.globl	C$stdlib.c$39$1_0$50
	XG$atoi$0$0	= .
	.globl	XG$atoi$0$0
	ret
	G$rand$0$0	= .
	.globl	G$rand$0$0
	C$stdlib.c$43$1_0$53	= .
	.globl	C$stdlib.c$43$1_0$53
;stdlib.c:43: int rand(void) /* RAND_MAX assumed to be 32767 */
;	---------------------------------
; Function rand
; ---------------------------------
_rand::
	C$stdlib.c$45$1_0$53	= .
	.globl	C$stdlib.c$45$1_0$53
;stdlib.c:45: _next = _next * 1103515245 + 12345;
	ld	hl, (__next + 2)
	push	hl
	ld	hl, (__next)
	push	hl
	ld	hl, #0x41c6
	push	hl
	ld	hl, #0x4e6d
	push	hl
	call	__mullong
	pop	af
	pop	af
	pop	af
	pop	af
	ld	c, l
	ld	b, h
	ld	a, c
	ld	hl, #__next
	add	a, #0x39
	ld	(hl), a
	inc	hl
	ld	a, b
	adc	a, #0x30
	ld	(hl), a
	inc	hl
	ld	a, e
	adc	a, #0x00
	ld	(hl), a
	inc	hl
	ld	a, d
	adc	a, #0x00
	ld	(hl), a
	C$stdlib.c$46$1_0$53	= .
	.globl	C$stdlib.c$46$1_0$53
;stdlib.c:46: return (unsigned int)(_next / 65536) % 32768;
	ld	hl, (__next + 2)
	res	7, h
	C$stdlib.c$47$1_0$53	= .
	.globl	C$stdlib.c$47$1_0$53
;stdlib.c:47: }
	C$stdlib.c$47$1_0$53	= .
	.globl	C$stdlib.c$47$1_0$53
	XG$rand$0$0	= .
	.globl	XG$rand$0$0
	ret
	G$srand$0$0	= .
	.globl	G$srand$0$0
	C$stdlib.c$49$1_0$55	= .
	.globl	C$stdlib.c$49$1_0$55
;stdlib.c:49: void srand(unsigned int seed)
;	---------------------------------
; Function srand
; ---------------------------------
_srand::
	C$stdlib.c$51$1_0$55	= .
	.globl	C$stdlib.c$51$1_0$55
;stdlib.c:51: _next = seed;
	ld	iy, #2
	add	iy, sp
	ld	a, 0 (iy)
	ld	(__next+0), a
	ld	a, 1 (iy)
	ld	(__next+1), a
	xor	a, a
	ld	(__next+2), a
	ld	(__next+3), a
	C$stdlib.c$52$1_0$55	= .
	.globl	C$stdlib.c$52$1_0$55
;stdlib.c:52: }
	C$stdlib.c$52$1_0$55	= .
	.globl	C$stdlib.c$52$1_0$55
	XG$srand$0$0	= .
	.globl	XG$srand$0$0
	ret
	G$strtoul$0$0	= .
	.globl	G$strtoul$0$0
	C$stdlib.c$65$1_0$57	= .
	.globl	C$stdlib.c$65$1_0$57
;stdlib.c:65: unsigned long strtoul(char *string, char **end_ptr, int base)
;	---------------------------------
; Function strtoul
; ---------------------------------
_strtoul::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-20
	add	hl, sp
	ld	sp, hl
	C$stdlib.c$68$2_0$57	= .
	.globl	C$stdlib.c$68$2_0$57
;stdlib.c:68: register unsigned long int result = 0;
	xor	a, a
	ld	-11 (ix), a
	ld	-10 (ix), a
	ld	-9 (ix), a
	ld	-8 (ix), a
	C$stdlib.c$70$2_0$57	= .
	.globl	C$stdlib.c$70$2_0$57
;stdlib.c:70: int any_digits = 0;
	xor	a, a
	ld	-13 (ix), a
	ld	-12 (ix), a
	C$stdlib.c$73$1_0$57	= .
	.globl	C$stdlib.c$73$1_0$57
;stdlib.c:73: p = string;
	ld	a, 4 (ix)
	ld	-16 (ix), a
	ld	a, 5 (ix)
	ld	-15 (ix), a
	C$stdlib.c$74$1_0$57	= .
	.globl	C$stdlib.c$74$1_0$57
;stdlib.c:74: while (isspace(*p))
	ld	a, -16 (ix)
	ld	-6 (ix), a
	ld	a, -15 (ix)
	ld	-5 (ix), a
00101$:
	ld	l, -6 (ix)
	ld	h, -5 (ix)
	ld	c, (hl)
	ld	b, #0x00
	push	bc
	call	_isspace
	pop	af
	C$stdlib.c$76$1_0$57	= .
	.globl	C$stdlib.c$76$1_0$57
;stdlib.c:76: p += 1;
	ld	a, -6 (ix)
	add	a, #0x01
	ld	-4 (ix), a
	ld	a, -5 (ix)
	adc	a, #0x00
	ld	-3 (ix), a
	C$stdlib.c$74$1_0$57	= .
	.globl	C$stdlib.c$74$1_0$57
;stdlib.c:74: while (isspace(*p))
	ld	a, h
	or	a, l
	jr	Z, 00177$
	C$stdlib.c$76$2_0$58	= .
	.globl	C$stdlib.c$76$2_0$58
;stdlib.c:76: p += 1;
	ld	a, -4 (ix)
	ld	-6 (ix), a
	ld	a, -3 (ix)
	ld	-5 (ix), a
	jr	00101$
00177$:
	ld	a, -6 (ix)
	ld	-2 (ix), a
	ld	a, -5 (ix)
	ld	-1 (ix), a
	C$stdlib.c$78$1_0$57	= .
	.globl	C$stdlib.c$78$1_0$57
;stdlib.c:78: if (base == 0)
	ld	a, 9 (ix)
	or	a, 8 (ix)
	jr	NZ, 00116$
	C$stdlib.c$80$2_0$59	= .
	.globl	C$stdlib.c$80$2_0$59
;stdlib.c:80: if (*p == '0')
	ld	l, -6 (ix)
	ld	h, -5 (ix)
	ld	a, (hl)
	sub	a, #0x30
	jr	NZ, 00108$
	C$stdlib.c$82$3_0$60	= .
	.globl	C$stdlib.c$82$3_0$60
;stdlib.c:82: p += 1;
	ld	a, -4 (ix)
	ld	-2 (ix), a
	ld	a, -3 (ix)
	ld	-1 (ix), a
	C$stdlib.c$83$3_0$60	= .
	.globl	C$stdlib.c$83$3_0$60
;stdlib.c:83: if (*p == 'x')
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, (hl)
	sub	a, #0x78
	jr	NZ, 00105$
	C$stdlib.c$85$4_0$61	= .
	.globl	C$stdlib.c$85$4_0$61
;stdlib.c:85: p += 1;
	inc	-2 (ix)
	jr	NZ, 00278$
	inc	-1 (ix)
00278$:
	C$stdlib.c$86$4_0$61	= .
	.globl	C$stdlib.c$86$4_0$61
;stdlib.c:86: base = 16;
	ld	8 (ix), #0x10
	ld	9 (ix), #0
	jr	00117$
00105$:
	C$stdlib.c$90$4_0$62	= .
	.globl	C$stdlib.c$90$4_0$62
;stdlib.c:90: any_digits = 1;
	ld	-13 (ix), #0x01
	ld	-12 (ix), #0
	C$stdlib.c$91$4_0$62	= .
	.globl	C$stdlib.c$91$4_0$62
;stdlib.c:91: base = 8;
	ld	8 (ix), #0x08
	ld	9 (ix), #0
	jr	00117$
00108$:
	C$stdlib.c$95$2_0$59	= .
	.globl	C$stdlib.c$95$2_0$59
;stdlib.c:95: base = 10;
	ld	8 (ix), #0x0a
	ld	9 (ix), #0
	jr	00117$
00116$:
	C$stdlib.c$97$1_0$57	= .
	.globl	C$stdlib.c$97$1_0$57
;stdlib.c:97: else if (base == 16)
	ld	a, 8 (ix)
	sub	a, #0x10
	or	a, 9 (ix)
	jr	NZ, 00117$
	C$stdlib.c$99$2_0$63	= .
	.globl	C$stdlib.c$99$2_0$63
;stdlib.c:99: if ((p[0] == '0') && (p[1] == 'x'))
	ld	l, -6 (ix)
	ld	h, -5 (ix)
	ld	a, (hl)
	sub	a, #0x30
	jr	NZ, 00117$
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	a, (hl)
	sub	a, #0x78
	jr	NZ, 00117$
	C$stdlib.c$101$3_0$64	= .
	.globl	C$stdlib.c$101$3_0$64
;stdlib.c:101: p += 2;
	ld	a, -6 (ix)
	add	a, #0x02
	ld	-2 (ix), a
	ld	a, -5 (ix)
	adc	a, #0x00
	ld	-1 (ix), a
00117$:
	C$stdlib.c$105$1_0$57	= .
	.globl	C$stdlib.c$105$1_0$57
;stdlib.c:105: if (base == 8)
	ld	a, 8 (ix)
	sub	a, #0x08
	or	a, 9 (ix)
	jr	NZ, 00141$
	ld	e, -2 (ix)
	ld	d, -1 (ix)
00147$:
	C$stdlib.c$109$4_0$67	= .
	.globl	C$stdlib.c$109$4_0$67
;stdlib.c:109: digit = *p - '0';
	ld	a, (de)
	ld	c, #0x00
	add	a, #0xd0
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, c
	adc	a, #0xff
	ld	h, a
;	spillPairReg hl
;	spillPairReg hl
	C$stdlib.c$110$4_0$67	= .
	.globl	C$stdlib.c$110$4_0$67
;stdlib.c:110: if (digit > 7)
	ld	a, #0x07
	cp	a, l
	ld	a, #0x00
	sbc	a, h
	jp	C,00142$
	C$stdlib.c$114$4_0$67	= .
	.globl	C$stdlib.c$114$4_0$67
;stdlib.c:114: result = (result << 3) + digit;
	ld	a, -11 (ix)
	ld	-4 (ix), a
	ld	a, -10 (ix)
	ld	-3 (ix), a
	ld	a, -9 (ix)
	ld	-2 (ix), a
	ld	a, -8 (ix)
	ld	-1 (ix), a
	ld	b, #0x03
00287$:
	sla	-4 (ix)
	rl	-3 (ix)
	rl	-2 (ix)
	rl	-1 (ix)
	djnz	00287$
	ld	bc, #0x0000
	ld	a, l
	add	a, -4 (ix)
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, h
	adc	a, -3 (ix)
	ld	h, a
;	spillPairReg hl
;	spillPairReg hl
	ld	a, c
	adc	a, -2 (ix)
	ld	c, a
	ld	a, b
	adc	a, -1 (ix)
	ld	b, a
	ld	-11 (ix), l
	ld	-10 (ix), h
	ld	-9 (ix), c
	ld	-8 (ix), b
	C$stdlib.c$115$4_0$67	= .
	.globl	C$stdlib.c$115$4_0$67
;stdlib.c:115: any_digits = 1;
	ld	-13 (ix), #0x01
	ld	-12 (ix), #0
	C$stdlib.c$107$3_0$66	= .
	.globl	C$stdlib.c$107$3_0$66
;stdlib.c:107: for (;; p += 1)
	inc	de
	jr	00147$
00141$:
	C$stdlib.c$118$1_0$57	= .
	.globl	C$stdlib.c$118$1_0$57
;stdlib.c:118: else if (base == 10)
	ld	a, 8 (ix)
	sub	a, #0x0a
	or	a, 9 (ix)
	jp	NZ,00138$
00149$:
	C$stdlib.c$122$4_0$71	= .
	.globl	C$stdlib.c$122$4_0$71
;stdlib.c:122: digit = *p - '0';
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	ld	-6 (ix), a
	ld	-5 (ix), #0x00
	ld	a, -6 (ix)
	add	a, #0xd0
	ld	-4 (ix), a
	ld	a, -5 (ix)
	adc	a, #0xff
	ld	-3 (ix), a
	C$stdlib.c$123$4_0$71	= .
	.globl	C$stdlib.c$123$4_0$71
;stdlib.c:123: if (digit > 9)
	ld	a, #0x09
	cp	a, -4 (ix)
	ld	a, #0x00
	sbc	a, -3 (ix)
	jp	C, 00179$
	C$stdlib.c$127$1_0$57	= .
	.globl	C$stdlib.c$127$1_0$57
;stdlib.c:127: result = (10 * result) + digit;
	ld	l, -9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, -11 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -10 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	hl, #0x0000
	push	hl
	ld	l, #0x0a
	push	hl
	call	__mullong
	pop	af
	pop	af
	pop	af
	pop	af
	ld	-14 (ix), l
	ld	-13 (ix), h
	ld	-12 (ix), e
	ld	-11 (ix), d
	ld	a, -4 (ix)
	ld	-10 (ix), a
	ld	a, -3 (ix)
	ld	-9 (ix), a
	xor	a, a
	ld	-8 (ix), a
	ld	-7 (ix), a
	ld	a, -14 (ix)
	add	a, -10 (ix)
	ld	-6 (ix), a
	ld	a, -13 (ix)
	adc	a, -9 (ix)
	ld	-5 (ix), a
	ld	a, -12 (ix)
	adc	a, -8 (ix)
	ld	-4 (ix), a
	ld	a, -11 (ix)
	adc	a, -7 (ix)
	ld	-3 (ix), a
	ld	hl, #9
	add	hl, sp
	ex	de, hl
	ld	hl, #14
	add	hl, sp
	ld	bc, #4
	ldir
	C$stdlib.c$128$4_0$71	= .
	.globl	C$stdlib.c$128$4_0$71
;stdlib.c:128: any_digits = 1;
	ld	-13 (ix), #0x01
	ld	-12 (ix), #0
	C$stdlib.c$120$3_0$70	= .
	.globl	C$stdlib.c$120$3_0$70
;stdlib.c:120: for (;; p += 1)
	inc	-2 (ix)
	jp	NZ,00149$
	inc	-1 (ix)
	jp	00149$
00138$:
	C$stdlib.c$131$1_0$57	= .
	.globl	C$stdlib.c$131$1_0$57
;stdlib.c:131: else if (base == 16)
	ld	a, 8 (ix)
	sub	a, #0x10
	or	a, 9 (ix)
	jp	NZ,00174$
00151$:
	C$stdlib.c$135$4_0$75	= .
	.globl	C$stdlib.c$135$4_0$75
;stdlib.c:135: digit = *p - '0';
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	ld	-4 (ix), a
	ld	-3 (ix), #0x00
	ld	a, -4 (ix)
	add	a, #0xd0
	ld	-6 (ix), a
	ld	a, -3 (ix)
	adc	a, #0xff
	ld	-5 (ix), a
	C$stdlib.c$136$4_0$75	= .
	.globl	C$stdlib.c$136$4_0$75
;stdlib.c:136: if (digit > ('z' - '0'))
	ld	a, #0x4a
	cp	a, -6 (ix)
	ld	a, #0x00
	sbc	a, -5 (ix)
	jp	C, 00180$
	C$stdlib.c$140$4_0$75	= .
	.globl	C$stdlib.c$140$4_0$75
;stdlib.c:140: digit = _cvt_in[digit];
	ld	a, #<(__cvt_in)
	add	a, -6 (ix)
	ld	-4 (ix), a
	ld	a, #>(__cvt_in)
	adc	a, -5 (ix)
	ld	-3 (ix), a
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	ld	-4 (ix), a
	ld	-3 (ix), #0x00
	C$stdlib.c$141$4_0$75	= .
	.globl	C$stdlib.c$141$4_0$75
;stdlib.c:141: if (digit > 15)
	ld	a, #0x0f
	cp	a, -4 (ix)
	ld	a, #0x00
	sbc	a, -3 (ix)
	jp	C, 00180$
	C$stdlib.c$145$4_0$75	= .
	.globl	C$stdlib.c$145$4_0$75
;stdlib.c:145: result = (result << 4) + digit;
	ld	a, -11 (ix)
	ld	-20 (ix), a
	ld	a, -10 (ix)
	ld	-19 (ix), a
	ld	a, -9 (ix)
	ld	-18 (ix), a
	ld	a, -8 (ix)
	ld	-17 (ix), a
	ld	b, #0x04
00294$:
	sla	-20 (ix)
	rl	-19 (ix)
	rl	-18 (ix)
	rl	-17 (ix)
	djnz	00294$
	ld	a, -4 (ix)
	ld	-10 (ix), a
	ld	a, -3 (ix)
	ld	-9 (ix), a
	xor	a, a
	ld	-8 (ix), a
	ld	-7 (ix), a
	ld	a, -20 (ix)
	add	a, -10 (ix)
	ld	-6 (ix), a
	ld	a, -19 (ix)
	adc	a, -9 (ix)
	ld	-5 (ix), a
	ld	a, -18 (ix)
	adc	a, -8 (ix)
	ld	-4 (ix), a
	ld	a, -17 (ix)
	adc	a, -7 (ix)
	ld	-3 (ix), a
	ld	hl, #9
	add	hl, sp
	ex	de, hl
	ld	hl, #14
	add	hl, sp
	ld	bc, #4
	ldir
	C$stdlib.c$146$4_0$75	= .
	.globl	C$stdlib.c$146$4_0$75
;stdlib.c:146: any_digits = 1;
	ld	-13 (ix), #0x01
	ld	-12 (ix), #0
	C$stdlib.c$133$3_0$74	= .
	.globl	C$stdlib.c$133$3_0$74
;stdlib.c:133: for (;; p += 1)
	inc	-2 (ix)
	jp	NZ,00151$
	inc	-1 (ix)
	jp	00151$
00174$:
00153$:
	C$stdlib.c$153$4_0$80	= .
	.globl	C$stdlib.c$153$4_0$80
;stdlib.c:153: digit = *p - '0';
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	ld	-4 (ix), a
	ld	-3 (ix), #0x00
	ld	a, -4 (ix)
	add	a, #0xd0
	ld	-6 (ix), a
	ld	a, -3 (ix)
	adc	a, #0xff
	ld	-5 (ix), a
	C$stdlib.c$154$4_0$80	= .
	.globl	C$stdlib.c$154$4_0$80
;stdlib.c:154: if (digit > ('z' - '0'))
	ld	a, #0x4a
	cp	a, -6 (ix)
	ld	a, #0x00
	sbc	a, -5 (ix)
	jp	C, 00181$
	C$stdlib.c$158$4_0$80	= .
	.globl	C$stdlib.c$158$4_0$80
;stdlib.c:158: digit = _cvt_in[digit];
	ld	a, #<(__cvt_in)
	add	a, -6 (ix)
	ld	-4 (ix), a
	ld	a, #>(__cvt_in)
	adc	a, -5 (ix)
	ld	-3 (ix), a
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	ld	-4 (ix), a
	ld	-3 (ix), #0x00
	C$stdlib.c$159$4_0$80	= .
	.globl	C$stdlib.c$159$4_0$80
;stdlib.c:159: if (digit >= base)
	ld	a, 8 (ix)
	ld	-6 (ix), a
	ld	a, 9 (ix)
	ld	-5 (ix), a
	ld	a, -4 (ix)
	sub	a, -6 (ix)
	ld	a, -3 (ix)
	sbc	a, -5 (ix)
	jp	NC, 00181$
	C$stdlib.c$163$4_0$80	= .
	.globl	C$stdlib.c$163$4_0$80
;stdlib.c:163: result = result * base + digit;
	ld	a, 8 (ix)
	ld	-20 (ix), a
	ld	a, 9 (ix)
	ld	-19 (ix), a
	rlca
	sbc	a, a
	ld	-18 (ix), a
	ld	-17 (ix), a
	pop	de
	pop	hl
	ex	de, hl
	push	de
	push	hl
	push	de
	push	hl
	ld	l, -9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, -11 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -10 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	call	__mullong
	pop	af
	pop	af
	pop	af
	pop	af
	ld	-14 (ix), l
	ld	-13 (ix), h
	ld	-12 (ix), e
	ld	-11 (ix), d
	ld	a, -4 (ix)
	ld	-10 (ix), a
	ld	a, -3 (ix)
	ld	-9 (ix), a
	xor	a, a
	ld	-8 (ix), a
	ld	-7 (ix), a
	ld	a, -14 (ix)
	add	a, -10 (ix)
	ld	-6 (ix), a
	ld	a, -13 (ix)
	adc	a, -9 (ix)
	ld	-5 (ix), a
	ld	a, -12 (ix)
	adc	a, -8 (ix)
	ld	-4 (ix), a
	ld	a, -11 (ix)
	adc	a, -7 (ix)
	ld	-3 (ix), a
	ld	hl, #9
	add	hl, sp
	ex	de, hl
	ld	hl, #14
	add	hl, sp
	ld	bc, #4
	ldir
	C$stdlib.c$164$4_0$80	= .
	.globl	C$stdlib.c$164$4_0$80
;stdlib.c:164: any_digits = 1;
	ld	-13 (ix), #0x01
	ld	-12 (ix), #0
	C$stdlib.c$151$3_0$79	= .
	.globl	C$stdlib.c$151$3_0$79
;stdlib.c:151: for (;; p += 1)
	inc	-2 (ix)
	jp	NZ,00153$
	inc	-1 (ix)
	C$stdlib.c$172$1_0$57	= .
	.globl	C$stdlib.c$172$1_0$57
;stdlib.c:172: return result;
	jp	00153$
	C$stdlib.c$151$1_0$57	= .
	.globl	C$stdlib.c$151$1_0$57
;stdlib.c:151: for (;; p += 1)
00179$:
	ld	e, -2 (ix)
	ld	d, -1 (ix)
	C$stdlib.c$172$1_0$57	= .
	.globl	C$stdlib.c$172$1_0$57
;stdlib.c:172: return result;
	jr	00142$
	C$stdlib.c$151$1_0$57	= .
	.globl	C$stdlib.c$151$1_0$57
;stdlib.c:151: for (;; p += 1)
00180$:
	ld	e, -2 (ix)
	ld	d, -1 (ix)
	C$stdlib.c$172$1_0$57	= .
	.globl	C$stdlib.c$172$1_0$57
;stdlib.c:172: return result;
	jr	00142$
	C$stdlib.c$151$1_0$57	= .
	.globl	C$stdlib.c$151$1_0$57
;stdlib.c:151: for (;; p += 1)
00181$:
	ld	e, -2 (ix)
	ld	d, -1 (ix)
00142$:
	C$stdlib.c$168$1_0$57	= .
	.globl	C$stdlib.c$168$1_0$57
;stdlib.c:168: if (!any_digits)
	ld	a, -12 (ix)
	or	a, -13 (ix)
	jr	NZ, 00144$
	C$stdlib.c$169$1_0$57	= .
	.globl	C$stdlib.c$169$1_0$57
;stdlib.c:169: p = string;
	ld	e, -16 (ix)
	ld	d, -15 (ix)
00144$:
	C$stdlib.c$170$1_0$57	= .
	.globl	C$stdlib.c$170$1_0$57
;stdlib.c:170: if (end_ptr != 0)
	ld	a, 7 (ix)
	or	a, 6 (ix)
	jr	Z, 00146$
	C$stdlib.c$171$1_0$57	= .
	.globl	C$stdlib.c$171$1_0$57
;stdlib.c:171: *end_ptr = p;
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	(hl), e
	inc	hl
	ld	(hl), d
00146$:
	C$stdlib.c$172$1_0$57	= .
	.globl	C$stdlib.c$172$1_0$57
;stdlib.c:172: return result;
	ld	l, -11 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -10 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	e, -9 (ix)
	ld	d, -8 (ix)
	C$stdlib.c$173$1_0$57	= .
	.globl	C$stdlib.c$173$1_0$57
;stdlib.c:173: }
	ld	sp, ix
	pop	ix
	C$stdlib.c$173$1_0$57	= .
	.globl	C$stdlib.c$173$1_0$57
	XG$strtoul$0$0	= .
	.globl	XG$strtoul$0$0
	ret
Fstdlib$_cvt_in$0_0$0 == .
__cvt_in:
	.db #0x00	; 0
	.db #0x01	; 1
	.db #0x02	; 2
	.db #0x03	; 3
	.db #0x04	; 4
	.db #0x05	; 5
	.db #0x06	; 6
	.db #0x07	; 7
	.db #0x08	; 8
	.db #0x09	; 9
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x0a	; 10
	.db #0x0b	; 11
	.db #0x0c	; 12
	.db #0x0d	; 13
	.db #0x0e	; 14
	.db #0x0f	; 15
	.db #0x10	; 16
	.db #0x11	; 17
	.db #0x12	; 18
	.db #0x13	; 19
	.db #0x14	; 20
	.db #0x15	; 21
	.db #0x16	; 22
	.db #0x17	; 23
	.db #0x18	; 24
	.db #0x19	; 25
	.db #0x1a	; 26
	.db #0x1b	; 27
	.db #0x1c	; 28
	.db #0x1d	; 29
	.db #0x1e	; 30
	.db #0x1f	; 31
	.db #0x20	; 32
	.db #0x21	; 33
	.db #0x22	; 34
	.db #0x23	; 35
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x64	; 100	'd'
	.db #0x0a	; 10
	.db #0x0b	; 11
	.db #0x0c	; 12
	.db #0x0d	; 13
	.db #0x0e	; 14
	.db #0x0f	; 15
	.db #0x10	; 16
	.db #0x11	; 17
	.db #0x12	; 18
	.db #0x13	; 19
	.db #0x14	; 20
	.db #0x15	; 21
	.db #0x16	; 22
	.db #0x17	; 23
	.db #0x18	; 24
	.db #0x19	; 25
	.db #0x1a	; 26
	.db #0x1b	; 27
	.db #0x1c	; 28
	.db #0x1d	; 29
	.db #0x1e	; 30
	.db #0x1f	; 31
	.db #0x20	; 32
	.db #0x21	; 33
	.db #0x22	; 34
	.db #0x23	; 35
	G$strtol$0$0	= .
	.globl	G$strtol$0$0
	C$stdlib.c$175$1_0$84	= .
	.globl	C$stdlib.c$175$1_0$84
;stdlib.c:175: long strtol(char *nptr, char **endptr, int base)
;	---------------------------------
; Function strtol
; ---------------------------------
_strtol::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-10
	add	hl, sp
	ld	sp, hl
	C$stdlib.c$178$2_0$84	= .
	.globl	C$stdlib.c$178$2_0$84
;stdlib.c:178: char *p = nptr;
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	C$stdlib.c$179$1_0$84	= .
	.globl	C$stdlib.c$179$1_0$84
;stdlib.c:179: while (isspace(*p))
00101$:
	ld	a, (bc)
	ld	d, #0x00
	push	bc
	ld	e, a
	push	de
	call	_isspace
	pop	af
	ex	de, hl
	pop	bc
	C$stdlib.c$181$1_0$84	= .
	.globl	C$stdlib.c$181$1_0$84
;stdlib.c:181: p++;
	ld	l, c
	ld	h, b
	inc	hl
	ld	-3 (ix), l
	ld	-2 (ix), h
	C$stdlib.c$179$1_0$84	= .
	.globl	C$stdlib.c$179$1_0$84
;stdlib.c:179: while (isspace(*p))
	ld	a, d
	or	a, e
	jr	Z, 00120$
	C$stdlib.c$181$2_0$85	= .
	.globl	C$stdlib.c$181$2_0$85
;stdlib.c:181: p++;
	ld	c, -3 (ix)
	ld	b, -2 (ix)
	jr	00101$
00120$:
	ld	-6 (ix), c
	ld	-5 (ix), b
	C$stdlib.c$183$1_0$84	= .
	.globl	C$stdlib.c$183$1_0$84
;stdlib.c:183: if (*p == '-')
	ld	a, (bc)
	ld	-1 (ix), a
	sub	a, #0x2d
	jr	NZ, 00107$
	C$stdlib.c$185$2_0$86	= .
	.globl	C$stdlib.c$185$2_0$86
;stdlib.c:185: p++;
	ld	a, -3 (ix)
	ld	-6 (ix), a
	ld	a, -2 (ix)
	ld	-5 (ix), a
	C$stdlib.c$186$2_0$86	= .
	.globl	C$stdlib.c$186$2_0$86
;stdlib.c:186: result = -strtoul(p, endptr, base);
	ld	l, 8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, -6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	call	_strtoul
	pop	af
	pop	af
	pop	af
	ex	(sp), hl
	ld	-8 (ix), e
	ld	-7 (ix), d
	xor	a, a
	sub	a, -10 (ix)
	ld	-4 (ix), a
	ld	a, #0x00
	sbc	a, -9 (ix)
	ld	-3 (ix), a
	ld	a, #0x00
	sbc	a, -8 (ix)
	ld	-2 (ix), a
	sbc	a, a
	sub	a, -7 (ix)
	ld	-1 (ix), a
	jr	00108$
00107$:
	C$stdlib.c$190$2_0$87	= .
	.globl	C$stdlib.c$190$2_0$87
;stdlib.c:190: if (*p == '+')
	ld	a, -1 (ix)
	sub	a, #0x2b
	jr	NZ, 00105$
	C$stdlib.c$191$2_0$87	= .
	.globl	C$stdlib.c$191$2_0$87
;stdlib.c:191: p++;
	ld	a, -3 (ix)
	ld	-6 (ix), a
	ld	a, -2 (ix)
	ld	-5 (ix), a
00105$:
	C$stdlib.c$192$2_0$87	= .
	.globl	C$stdlib.c$192$2_0$87
;stdlib.c:192: result = strtoul(p, endptr, base);
	ld	l, 8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	l, -6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	call	_strtoul
	pop	af
	pop	af
	pop	af
	ld	-4 (ix), l
	ld	-3 (ix), h
	ld	-2 (ix), e
	ld	-1 (ix), d
00108$:
	C$stdlib.c$194$1_0$84	= .
	.globl	C$stdlib.c$194$1_0$84
;stdlib.c:194: if (endptr != 0 && *endptr == p)
	ld	a, 7 (ix)
	or	a, 6 (ix)
	jr	Z, 00110$
	ld	c, 6 (ix)
	ld	b, 7 (ix)
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	l, -6 (ix)
	ld	h, -5 (ix)
	cp	a, a
	sbc	hl, de
	jr	NZ, 00110$
	C$stdlib.c$196$2_0$88	= .
	.globl	C$stdlib.c$196$2_0$88
;stdlib.c:196: *endptr = nptr;
	ld	a, 4 (ix)
	ld	(bc), a
	inc	bc
	ld	a, 5 (ix)
	ld	(bc), a
00110$:
	C$stdlib.c$198$1_0$84	= .
	.globl	C$stdlib.c$198$1_0$84
;stdlib.c:198: return result;
	ld	l, -4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -3 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	e, -2 (ix)
	ld	d, -1 (ix)
	C$stdlib.c$199$1_0$84	= .
	.globl	C$stdlib.c$199$1_0$84
;stdlib.c:199: }
	ld	sp, ix
	pop	ix
	C$stdlib.c$199$1_0$84	= .
	.globl	C$stdlib.c$199$1_0$84
	XG$strtol$0$0	= .
	.globl	XG$strtol$0$0
	ret
	G$malloc$0$0	= .
	.globl	G$malloc$0$0
	C$stdlib.c$201$1_0$90	= .
	.globl	C$stdlib.c$201$1_0$90
;stdlib.c:201: void *malloc(size_t size)
;	---------------------------------
; Function malloc
; ---------------------------------
_malloc::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$stdlib.c$208$1_0$90	= .
	.globl	C$stdlib.c$208$1_0$90
;stdlib.c:208: (list_header_t **)&prev,
	ld	hl, #0
	add	hl, sp
	ex	de, hl
	C$stdlib.c$207$1_0$90	= .
	.globl	C$stdlib.c$207$1_0$90
;stdlib.c:207: (list_header_t *)&_heap,
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	hl, #__match_free_block
	push	hl
	push	de
	ld	hl, #__heap
	push	hl
	call	__list_find
	pop	af
	pop	af
	pop	af
	pop	af
	ld	c, l
	ld	b, h
	C$stdlib.c$211$1_0$90	= .
	.globl	C$stdlib.c$211$1_0$90
;stdlib.c:211: if (b)
	ld	a, b
	or	a, c
	jr	Z, 00104$
	C$stdlib.c$213$2_0$91	= .
	.globl	C$stdlib.c$213$2_0$91
;stdlib.c:213: if (b->size - size > BLK_SIZE + MIN_CHUNK_SIZE)
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	inc	hl
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, e
	sub	a, 4 (ix)
	ld	e, a
	ld	a, d
	sbc	a, 5 (ix)
	ld	d, a
	ld	a, #0x09
	cp	a, e
	ld	a, #0x00
	sbc	a, d
	jr	NC, 00102$
	C$stdlib.c$214$2_0$91	= .
	.globl	C$stdlib.c$214$2_0$91
;stdlib.c:214: _split(b, size);
	push	bc
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	push	bc
	call	__split
	pop	af
	pop	af
	pop	bc
00102$:
	C$stdlib.c$215$2_0$91	= .
	.globl	C$stdlib.c$215$2_0$91
;stdlib.c:215: b->stat = ALLOCATED;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	ld	(hl), #0x01
	C$stdlib.c$216$2_0$91	= .
	.globl	C$stdlib.c$216$2_0$91
;stdlib.c:216: return b->data;
	ld	hl, #0x0005
	add	hl, bc
	jr	00106$
00104$:
	C$stdlib.c$219$1_0$90	= .
	.globl	C$stdlib.c$219$1_0$90
;stdlib.c:219: return NULL;
	ld	hl, #0x0000
00106$:
	C$stdlib.c$220$1_0$90	= .
	.globl	C$stdlib.c$220$1_0$90
;stdlib.c:220: }
	ld	sp, ix
	pop	ix
	C$stdlib.c$220$1_0$90	= .
	.globl	C$stdlib.c$220$1_0$90
	XG$malloc$0$0	= .
	.globl	XG$malloc$0$0
	ret
	G$free$0$0	= .
	.globl	G$free$0$0
	C$stdlib.c$222$1_0$93	= .
	.globl	C$stdlib.c$222$1_0$93
;stdlib.c:222: void free(void *p)
;	---------------------------------
; Function free
; ---------------------------------
_free::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	C$stdlib.c$228$1_0$93	= .
	.globl	C$stdlib.c$228$1_0$93
;stdlib.c:228: b = (block_t *)((uint16_t)p - BLK_SIZE);
	ld	a, 4 (ix)
	ld	b, 5 (ix)
	add	a, #0xfb
	ld	c, a
	ld	a, b
	adc	a, #0xff
	ld	b, a
	C$stdlib.c$231$1_0$93	= .
	.globl	C$stdlib.c$231$1_0$93
;stdlib.c:231: if (_list_find((list_header_t *)&_heap, (list_header_t **)&prev, _list_match_eq, (uint16_t)b))
	ld	-2 (ix), c
	ld	-1 (ix), b
	ld	hl, #0
	add	hl, sp
	push	bc
	ex	de, hl
	ld	l, -2 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, -1 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	ld	hl, #__list_match_eq
	push	hl
	push	de
	ld	hl, #__heap
	push	hl
	call	__list_find
	pop	af
	pop	af
	pop	af
	pop	af
	ex	de, hl
	pop	bc
	ld	a, d
	or	a, e
	jr	Z, 00109$
	C$stdlib.c$233$2_0$94	= .
	.globl	C$stdlib.c$233$2_0$94
;stdlib.c:233: b->stat = NEW;
	ld	e, c
	ld	d, b
	inc	de
	inc	de
	xor	a, a
	ld	(de), a
	C$stdlib.c$235$2_0$94	= .
	.globl	C$stdlib.c$235$2_0$94
;stdlib.c:235: if (prev && !(prev->stat & ALLOCATED))
	ld	a, -3 (ix)
	or	a, -4 (ix)
	jr	Z, 00102$
	pop	de
	push	de
	ld	l, e
;	spillPairReg hl
;	spillPairReg hl
	ld	h, d
;	spillPairReg hl
;	spillPairReg hl
	inc	hl
	inc	hl
	ld	a, (hl)
	rrca
	jr	C, 00102$
	C$stdlib.c$237$3_0$95	= .
	.globl	C$stdlib.c$237$3_0$95
;stdlib.c:237: _merge_with_next(prev);
	push	de
	call	__merge_with_next
	pop	af
	C$stdlib.c$238$3_0$95	= .
	.globl	C$stdlib.c$238$3_0$95
;stdlib.c:238: b = prev;
	pop	bc
	push	bc
00102$:
	C$stdlib.c$241$2_0$94	= .
	.globl	C$stdlib.c$241$2_0$94
;stdlib.c:241: if (b->hdr.next && !(((block_t *)(b->hdr.next))->stat & ALLOCATED))
	ld	l, c
	ld	h, b
	ld	e, (hl)
	inc	hl
	ld	d, (hl)
	ld	a, d
	or	a, e
	jr	Z, 00109$
	inc	de
	inc	de
	ld	a, (de)
	rrca
	jr	C, 00109$
	C$stdlib.c$242$2_0$94	= .
	.globl	C$stdlib.c$242$2_0$94
;stdlib.c:242: _merge_with_next(b);
	push	bc
	call	__merge_with_next
	pop	af
00109$:
	C$stdlib.c$244$1_0$93	= .
	.globl	C$stdlib.c$244$1_0$93
;stdlib.c:244: }
	ld	sp, ix
	pop	ix
	C$stdlib.c$244$1_0$93	= .
	.globl	C$stdlib.c$244$1_0$93
	XG$free$0$0	= .
	.globl	XG$free$0$0
	ret
	G$calloc$0$0	= .
	.globl	G$calloc$0$0
	C$stdlib.c$246$1_0$97	= .
	.globl	C$stdlib.c$246$1_0$97
;stdlib.c:246: void *calloc(size_t num, size_t size)
;	---------------------------------
; Function calloc
; ---------------------------------
_calloc::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$stdlib.c$248$1_0$97	= .
	.globl	C$stdlib.c$248$1_0$97
;stdlib.c:248: size_t bytes = num * size;
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
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
	call	__mulint
	pop	af
	pop	af
	ex	de, hl
	C$stdlib.c$249$1_0$97	= .
	.globl	C$stdlib.c$249$1_0$97
;stdlib.c:249: void *result = malloc(bytes);
	push	de
	push	de
	call	_malloc
	pop	af
	pop	de
	C$stdlib.c$250$1_0$97	= .
	.globl	C$stdlib.c$250$1_0$97
;stdlib.c:250: memset(result, 0, bytes);
	push	hl
	push	de
	ld	de, #0x0000
	push	de
	push	hl
	call	_memset
	pop	af
	pop	af
	pop	af
	pop	hl
	C$stdlib.c$251$1_0$97	= .
	.globl	C$stdlib.c$251$1_0$97
;stdlib.c:251: return result;
	C$stdlib.c$252$1_0$97	= .
	.globl	C$stdlib.c$252$1_0$97
;stdlib.c:252: }
	pop	ix
	C$stdlib.c$252$1_0$97	= .
	.globl	C$stdlib.c$252$1_0$97
	XG$calloc$0$0	= .
	.globl	XG$calloc$0$0
	ret
	.area _CODE
	.area _INITIALIZER
Fstdlib$__xinit__next$0_0$0 == .
__xinit___next:
	.byte #0x01, #0x00, #0x00, #0x00	; 1
	.area _CABS (ABS)
