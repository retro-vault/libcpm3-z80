;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.1.6 #12391 (Linux)
;--------------------------------------------------------
	.module string
	.optsdcc -mz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _memchr
	.globl _memcmp
	.globl _memcpy
	.globl _memset
	.globl _strlen
	.globl _strcpy
	.globl _strncpy
	.globl _strcmp
	.globl _strncmp
	.globl _strchr
	.globl _strrchr
	.globl _strsep
	.globl _strcspn
	.globl _strtok
	.globl _strerror
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
Lstring.strtok$last$1_0$74==.
_strtok_last_65536_74:
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
	G$memchr$0$0	= .
	.globl	G$memchr$0$0
	C$string.c$20$0_0$21	= .
	.globl	C$string.c$20$0_0$21
;string.c:20: void *memchr(const void *s, int c, size_t n) {
;	---------------------------------
; Function memchr
; ---------------------------------
_memchr::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$string.c$21$2_0$21	= .
	.globl	C$string.c$21$2_0$21
;string.c:21: const unsigned char *s_ = s;
	ld	a, 4 (ix)
	ld	-2 (ix), a
	ld	a, 5 (ix)
	ld	-1 (ix), a
	C$string.c$22$1_0$21	= .
	.globl	C$string.c$22$1_0$21
;string.c:22: const unsigned char c_ = (unsigned char)c;
	ld	c, 6 (ix)
	C$string.c$24$1_0$21	= .
	.globl	C$string.c$24$1_0$21
;string.c:24: for (size_t i = 0; i < n; ++i) {
	ld	de, #0x0000
00105$:
	ld	a, e
	sub	a, 8 (ix)
	ld	a, d
	sbc	a, 9 (ix)
	jr	NC, 00103$
	C$string.c$25$3_0$23	= .
	.globl	C$string.c$25$3_0$23
;string.c:25: if (s_[i] == c_) {
	pop	hl
	push	hl
	add	hl, de
	ld	b, (hl)
	ld	a, c
	sub	a, b
	jr	Z, 00107$
	C$string.c$26$4_0$24	= .
	.globl	C$string.c$26$4_0$24
;string.c:26: return (void *)(s_ + i);
	jr	00106$
00106$:
	C$string.c$24$2_0$22	= .
	.globl	C$string.c$24$2_0$22
;string.c:24: for (size_t i = 0; i < n; ++i) {
	inc	de
	jr	00105$
00103$:
	C$string.c$30$1_0$21	= .
	.globl	C$string.c$30$1_0$21
;string.c:30: return NULL;
	ld	hl, #0x0000
00107$:
	C$string.c$31$1_0$21	= .
	.globl	C$string.c$31$1_0$21
;string.c:31: }
	ld	sp, ix
	pop	ix
	C$string.c$31$1_0$21	= .
	.globl	C$string.c$31$1_0$21
	XG$memchr$0$0	= .
	.globl	XG$memchr$0$0
	ret
	G$memcmp$0$0	= .
	.globl	G$memcmp$0$0
	C$string.c$33$1_0$26	= .
	.globl	C$string.c$33$1_0$26
;string.c:33: int memcmp(const void *lhs, const void *rhs, size_t count) {
;	---------------------------------
; Function memcmp
; ---------------------------------
_memcmp::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	C$string.c$34$2_0$26	= .
	.globl	C$string.c$34$2_0$26
;string.c:34: const unsigned char *lhs_ = lhs;
	ld	a, 4 (ix)
	ld	-4 (ix), a
	ld	a, 5 (ix)
	ld	-3 (ix), a
	C$string.c$35$2_0$26	= .
	.globl	C$string.c$35$2_0$26
;string.c:35: const unsigned char *rhs_ = rhs;
	ld	a, 6 (ix)
	ld	-2 (ix), a
	ld	a, 7 (ix)
	ld	-1 (ix), a
	C$string.c$37$1_0$26	= .
	.globl	C$string.c$37$1_0$26
;string.c:37: for (size_t i = 0; i < count; ++i) {
	ld	bc, #0x0000
00105$:
	ld	a, c
	sub	a, 8 (ix)
	ld	a, b
	sbc	a, 9 (ix)
	jr	NC, 00103$
	C$string.c$38$3_0$28	= .
	.globl	C$string.c$38$3_0$28
;string.c:38: const int res = lhs_[i] - rhs_[i];
	pop	hl
	push	hl
	add	hl, bc
	ld	e, (hl)
	ld	d, #0x00
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	add	hl, bc
	ld	l, (hl)
;	spillPairReg hl
	ld	h, #0x00
;	spillPairReg hl
;	spillPairReg hl
	ld	a, e
	sub	a, l
	ld	e, a
	ld	a, d
	sbc	a, h
	ld	d, a
	ld	l, e
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
	C$string.c$39$3_0$28	= .
	.globl	C$string.c$39$3_0$28
;string.c:39: if (res != 0) {
	ld	a,d
	ld	h,a
	or	a, e
	C$string.c$40$4_0$29	= .
	.globl	C$string.c$40$4_0$29
;string.c:40: return res;
	jr	NZ, 00107$
	C$string.c$37$2_0$27	= .
	.globl	C$string.c$37$2_0$27
;string.c:37: for (size_t i = 0; i < count; ++i) {
	inc	bc
	jr	00105$
00103$:
	C$string.c$44$1_0$26	= .
	.globl	C$string.c$44$1_0$26
;string.c:44: return 0;
	ld	hl, #0x0000
00107$:
	C$string.c$45$1_0$26	= .
	.globl	C$string.c$45$1_0$26
;string.c:45: }
	ld	sp, ix
	pop	ix
	C$string.c$45$1_0$26	= .
	.globl	C$string.c$45$1_0$26
	XG$memcmp$0$0	= .
	.globl	XG$memcmp$0$0
	ret
	G$memcpy$0$0	= .
	.globl	G$memcpy$0$0
	C$string.c$47$1_0$31	= .
	.globl	C$string.c$47$1_0$31
;string.c:47: void *memcpy(void *s1, const void *s2, size_t n) {
;	---------------------------------
; Function memcpy
; ---------------------------------
_memcpy::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	push	af
	C$string.c$48$2_0$31	= .
	.globl	C$string.c$48$2_0$31
;string.c:48: unsigned char *s1_ = s1;
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	C$string.c$49$2_0$31	= .
	.globl	C$string.c$49$2_0$31
;string.c:49: const unsigned char *s2_ = s2;
	ld	a, 6 (ix)
	ld	-4 (ix), a
	ld	a, 7 (ix)
	ld	-3 (ix), a
	C$string.c$50$1_0$31	= .
	.globl	C$string.c$50$1_0$31
;string.c:50: for (size_t i = 0; i < n; ++i) {
	ld	de, #0x0000
00103$:
	ld	a, e
	sub	a, 8 (ix)
	ld	a, d
	sbc	a, 9 (ix)
	jr	NC, 00101$
	C$string.c$51$3_0$33	= .
	.globl	C$string.c$51$3_0$33
;string.c:51: s1_[i] = s2_[i];
	ld	a, c
	add	a, e
	ld	-2 (ix), a
	ld	a, b
	adc	a, d
	ld	-1 (ix), a
	pop	hl
	push	hl
	add	hl, de
	ld	a, (hl)
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	(hl), a
	C$string.c$50$2_0$32	= .
	.globl	C$string.c$50$2_0$32
;string.c:50: for (size_t i = 0; i < n; ++i) {
	inc	de
	jr	00103$
00101$:
	C$string.c$54$1_0$31	= .
	.globl	C$string.c$54$1_0$31
;string.c:54: return s1;
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	C$string.c$55$1_0$31	= .
	.globl	C$string.c$55$1_0$31
;string.c:55: }
	ld	sp, ix
	pop	ix
	C$string.c$55$1_0$31	= .
	.globl	C$string.c$55$1_0$31
	XG$memcpy$0$0	= .
	.globl	XG$memcpy$0$0
	ret
	G$memset$0$0	= .
	.globl	G$memset$0$0
	C$string.c$57$1_0$35	= .
	.globl	C$string.c$57$1_0$35
;string.c:57: void *memset(void *s, int c, size_t n) {
;	---------------------------------
; Function memset
; ---------------------------------
_memset::
	push	ix
	ld	ix,#0
	add	ix,sp
	dec	sp
	C$string.c$58$2_0$35	= .
	.globl	C$string.c$58$2_0$35
;string.c:58: unsigned char *s_ = s;
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	C$string.c$59$1_0$35	= .
	.globl	C$string.c$59$1_0$35
;string.c:59: const unsigned char c_ = (unsigned char)c;
	ld	a, 6 (ix)
	ld	-1 (ix), a
	C$string.c$60$1_0$35	= .
	.globl	C$string.c$60$1_0$35
;string.c:60: for (size_t i = 0; i < n; ++i) {
	ld	de, #0x0000
00103$:
	ld	a, e
	sub	a, 8 (ix)
	ld	a, d
	sbc	a, 9 (ix)
	jr	NC, 00101$
	C$string.c$61$3_0$37	= .
	.globl	C$string.c$61$3_0$37
;string.c:61: s_[i] = c_;
	ld	l, c
	ld	h, b
	add	hl, de
	ld	a, -1 (ix)
	ld	(hl), a
	C$string.c$60$2_0$36	= .
	.globl	C$string.c$60$2_0$36
;string.c:60: for (size_t i = 0; i < n; ++i) {
	inc	de
	jr	00103$
00101$:
	C$string.c$63$1_0$35	= .
	.globl	C$string.c$63$1_0$35
;string.c:63: return s;
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	C$string.c$64$1_0$35	= .
	.globl	C$string.c$64$1_0$35
;string.c:64: }
	inc	sp
	pop	ix
	C$string.c$64$1_0$35	= .
	.globl	C$string.c$64$1_0$35
	XG$memset$0$0	= .
	.globl	XG$memset$0$0
	ret
	G$strlen$0$0	= .
	.globl	G$strlen$0$0
	C$string.c$66$1_0$39	= .
	.globl	C$string.c$66$1_0$39
;string.c:66: size_t strlen(const char *str)
;	---------------------------------
; Function strlen
; ---------------------------------
_strlen::
	C$string.c$70$1_0$39	= .
	.globl	C$string.c$70$1_0$39
;string.c:70: while (*str++)
	ld	bc, #0x0000
	pop	hl
	pop	de
	push	de
	push	hl
00101$:
	ld	a, (de)
	inc	de
	or	a, a
	jr	Z, 00103$
	C$string.c$71$1_0$39	= .
	.globl	C$string.c$71$1_0$39
;string.c:71: length++;
	inc	bc
	jr	00101$
00103$:
	C$string.c$73$1_0$39	= .
	.globl	C$string.c$73$1_0$39
;string.c:73: return (length);
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
	C$string.c$74$1_0$39	= .
	.globl	C$string.c$74$1_0$39
;string.c:74: }
	C$string.c$74$1_0$39	= .
	.globl	C$string.c$74$1_0$39
	XG$strlen$0$0	= .
	.globl	XG$strlen$0$0
	ret
	G$strcpy$0$0	= .
	.globl	G$strcpy$0$0
	C$string.c$76$1_0$41	= .
	.globl	C$string.c$76$1_0$41
;string.c:76: char *strcpy(char *dest, const char *src)
;	---------------------------------
; Function strcpy
; ---------------------------------
_strcpy::
	C$string.c$80$1_0$41	= .
	.globl	C$string.c$80$1_0$41
;string.c:80: while (src[index])
	ld	bc, #0x0000
00101$:
	ld	iy, #4
	add	iy, sp
	ld	l, 0 (iy)
	ld	h, 1 (iy)
	add	hl, bc
	ld	e, (hl)
	ld	a, e
	or	a, a
	jr	Z, 00103$
	C$string.c$82$2_0$42	= .
	.globl	C$string.c$82$2_0$42
;string.c:82: dest[index] = src[index];
	ld	a, -2 (iy)
	dec	iy
	dec	iy
	add	a, c
	ld	d, a
	ld	a, 1 (iy)
	adc	a, b
	ld	l, d
	ld	h, a
	ld	(hl), e
	C$string.c$83$2_0$42	= .
	.globl	C$string.c$83$2_0$42
;string.c:83: index++;
	inc	bc
	jr	00101$
00103$:
	C$string.c$86$1_0$41	= .
	.globl	C$string.c$86$1_0$41
;string.c:86: return (dest);
	pop	de
	pop	hl
	push	hl
	push	de
	C$string.c$87$1_0$41	= .
	.globl	C$string.c$87$1_0$41
;string.c:87: }
	C$string.c$87$1_0$41	= .
	.globl	C$string.c$87$1_0$41
	XG$strcpy$0$0	= .
	.globl	XG$strcpy$0$0
	ret
	G$strncpy$0$0	= .
	.globl	G$strncpy$0$0
	C$string.c$89$1_0$44	= .
	.globl	C$string.c$89$1_0$44
;string.c:89: char* strncpy(char* dst, const char* src, size_t num)
;	---------------------------------
; Function strncpy
; ---------------------------------
_strncpy::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	dec	sp
	C$string.c$91$1_0$44	= .
	.globl	C$string.c$91$1_0$44
;string.c:91: if (dst == NULL) {
	ld	a, 5 (ix)
	or	a, 4 (ix)
	jr	NZ, 00102$
	C$string.c$92$2_0$45	= .
	.globl	C$string.c$92$2_0$45
;string.c:92: return NULL;
	ld	hl, #0x0000
	jr	00107$
00102$:
	C$string.c$94$2_0$46	= .
	.globl	C$string.c$94$2_0$46
;string.c:94: char* ptr = dst;
	ld	e, 4 (ix)
	ld	d, 5 (ix)
	C$string.c$95$1_1$44	= .
	.globl	C$string.c$95$1_1$44
;string.c:95: while (*src && num--)
	push	iy
	ex	(sp), hl
	ld	l, 8 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ex	(sp), hl
	ex	(sp), hl
	ld	h, 9 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ex	(sp), hl
	pop	iy
	ld	c, e
	ld	b, d
	ld	a, 6 (ix)
	ld	-2 (ix), a
	ld	a, 7 (ix)
	ld	-1 (ix), a
00104$:
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	a, (hl)
	ld	-3 (ix), a
	or	a, a
	jr	Z, 00106$
	push	iy
	pop	hl
	dec	iy
	ld	a, h
	or	a, l
	jr	Z, 00106$
	C$string.c$97$2_1$47	= .
	.globl	C$string.c$97$2_1$47
;string.c:97: *dst = *src;
	ld	a, -3 (ix)
	ld	(bc), a
	C$string.c$98$2_1$47	= .
	.globl	C$string.c$98$2_1$47
;string.c:98: dst++;
	inc	bc
	C$string.c$99$2_1$47	= .
	.globl	C$string.c$99$2_1$47
;string.c:99: src++;
	inc	-2 (ix)
	jr	NZ, 00104$
	inc	-1 (ix)
	jr	00104$
00106$:
	C$string.c$101$1_1$46	= .
	.globl	C$string.c$101$1_1$46
;string.c:101: *dst = '\0';
	xor	a, a
	ld	(bc), a
	C$string.c$102$1_1$46	= .
	.globl	C$string.c$102$1_1$46
;string.c:102: return ptr;
	ex	de, hl
00107$:
	C$string.c$103$1_1$44	= .
	.globl	C$string.c$103$1_1$44
;string.c:103: }
	ld	sp, ix
	pop	ix
	C$string.c$103$1_1$44	= .
	.globl	C$string.c$103$1_1$44
	XG$strncpy$0$0	= .
	.globl	XG$strncpy$0$0
	ret
	G$strcmp$0$0	= .
	.globl	G$strcmp$0$0
	C$string.c$105$1_1$49	= .
	.globl	C$string.c$105$1_1$49
;string.c:105: int strcmp(const char *s1, const char *s2) {
;	---------------------------------
; Function strcmp
; ---------------------------------
_strcmp::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$string.c$106$1_0$49	= .
	.globl	C$string.c$106$1_0$49
;string.c:106: while (*s1 && *s2 && *s1 == *s2)
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
00103$:
	ld	a, (bc)
	ld	e, (hl)
	or	a, a
	jr	Z, 00105$
	inc	e
	dec	e
	jr	Z, 00105$
	cp	a, e
	jr	NZ, 00105$
	C$string.c$108$2_0$50	= .
	.globl	C$string.c$108$2_0$50
;string.c:108: s1++;
	C$string.c$109$2_0$50	= .
	.globl	C$string.c$109$2_0$50
;string.c:109: s2++;
	inc	hl
	inc	bc
	jr	00103$
00105$:
	C$string.c$111$1_0$49	= .
	.globl	C$string.c$111$1_0$49
;string.c:111: return (*s1 - *s2);
	ld	l, a
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
;	spillPairReg hl
	ld	h, #0x00
	ld	d, h
	cp	a, a
	sbc	hl, de
	C$string.c$112$1_0$49	= .
	.globl	C$string.c$112$1_0$49
;string.c:112: }
	pop	ix
	C$string.c$112$1_0$49	= .
	.globl	C$string.c$112$1_0$49
	XG$strcmp$0$0	= .
	.globl	XG$strcmp$0$0
	ret
	G$strncmp$0$0	= .
	.globl	G$strncmp$0$0
	C$string.c$114$1_0$52	= .
	.globl	C$string.c$114$1_0$52
;string.c:114: int strncmp(const char *s1, const char *s2, register size_t n)
;	---------------------------------
; Function strncmp
; ---------------------------------
_strncmp::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-8
	add	hl, sp
	ld	sp, hl
	C$string.c$117$1_0$52	= .
	.globl	C$string.c$117$1_0$52
;string.c:117: while (n-- > 0)
	ld	a, 4 (ix)
	ld	-6 (ix), a
	ld	a, 5 (ix)
	ld	-5 (ix), a
	ld	a, 6 (ix)
	ld	-4 (ix), a
	ld	a, 7 (ix)
	ld	-3 (ix), a
	ld	a, 8 (ix)
	ld	-2 (ix), a
	ld	a, 9 (ix)
	ld	-1 (ix), a
00105$:
	ld	a, -2 (ix)
	ld	-8 (ix), a
	ld	a, -1 (ix)
	ld	-7 (ix), a
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	dec	hl
	ld	-2 (ix), l
	ld	-1 (ix), h
	ld	a, -7 (ix)
	or	a, -8 (ix)
	jr	Z, 00107$
	C$string.c$119$2_0$53	= .
	.globl	C$string.c$119$2_0$53
;string.c:119: u1 = (unsigned char) *s1++;
	ld	l, -6 (ix)
	ld	h, -5 (ix)
	ld	a, (hl)
	ld	-8 (ix), a
	inc	-6 (ix)
	jr	NZ, 00130$
	inc	-5 (ix)
00130$:
	C$string.c$120$2_0$53	= .
	.globl	C$string.c$120$2_0$53
;string.c:120: u2 = (unsigned char) *s2++;
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	a, (hl)
	ld	-7 (ix), a
	inc	-4 (ix)
	jr	NZ, 00131$
	inc	-3 (ix)
00131$:
	C$string.c$121$2_0$53	= .
	.globl	C$string.c$121$2_0$53
;string.c:121: if (u1 != u2)
	ld	a, -8 (ix)
	sub	a, -7 (ix)
	jr	Z, 00102$
	C$string.c$122$2_0$53	= .
	.globl	C$string.c$122$2_0$53
;string.c:122: return u1 - u2;
	ld	a, -8 (ix)
	ld	-2 (ix), a
	ld	-1 (ix), #0x00
	ld	a, -7 (ix)
	ld	-4 (ix), a
	ld	-3 (ix), #0x00
	ld	a, -2 (ix)
	sub	a, -4 (ix)
	ld	-6 (ix), a
	ld	a, -1 (ix)
	sbc	a, -3 (ix)
	ld	-5 (ix), a
	pop	de
	pop	hl
	push	hl
	push	de
	jr	00108$
00102$:
	C$string.c$123$2_0$53	= .
	.globl	C$string.c$123$2_0$53
;string.c:123: if (u1 == '\0')
	ld	a, -8 (ix)
	or	a, a
	jp	NZ, 00105$
	C$string.c$124$2_0$53	= .
	.globl	C$string.c$124$2_0$53
;string.c:124: return 0;
	ld	hl, #0x0000
	jr	00108$
00107$:
	C$string.c$126$1_0$52	= .
	.globl	C$string.c$126$1_0$52
;string.c:126: return 0;
	ld	hl, #0x0000
00108$:
	C$string.c$127$1_0$52	= .
	.globl	C$string.c$127$1_0$52
;string.c:127: }
	ld	sp, ix
	pop	ix
	C$string.c$127$1_0$52	= .
	.globl	C$string.c$127$1_0$52
	XG$strncmp$0$0	= .
	.globl	XG$strncmp$0$0
	ret
	G$strchr$0$0	= .
	.globl	G$strchr$0$0
	C$string.c$129$1_0$55	= .
	.globl	C$string.c$129$1_0$55
;string.c:129: char *strchr(const char *s, int c) {
;	---------------------------------
; Function strchr
; ---------------------------------
_strchr::
	C$string.c$130$1_0$55	= .
	.globl	C$string.c$130$1_0$55
;string.c:130: const char c_ = (char)c;
	ld	hl, #4
	add	hl, sp
	ld	c, (hl)
	C$string.c$131$1_0$55	= .
	.globl	C$string.c$131$1_0$55
;string.c:131: do {
	pop	de
	pop	hl
	push	hl
	push	de
00103$:
	C$string.c$132$2_0$56	= .
	.globl	C$string.c$132$2_0$56
;string.c:132: if (*s == c_) {
	ld	b, (hl)
	ld	a, c
	sub	a, b
	ret	Z
	C$string.c$133$3_0$57	= .
	.globl	C$string.c$133$3_0$57
;string.c:133: return (char *)s;
	jr	00104$
00104$:
	C$string.c$135$1_0$55	= .
	.globl	C$string.c$135$1_0$55
;string.c:135: } while (*s++ != '\0');
	inc	hl
	ld	a, b
	or	a, a
	jr	NZ, 00103$
	C$string.c$136$1_0$55	= .
	.globl	C$string.c$136$1_0$55
;string.c:136: return NULL;
	ld	hl, #0x0000
	C$string.c$137$1_0$55	= .
	.globl	C$string.c$137$1_0$55
;string.c:137: }
	C$string.c$137$1_0$55	= .
	.globl	C$string.c$137$1_0$55
	XG$strchr$0$0	= .
	.globl	XG$strchr$0$0
	ret
	G$strrchr$0$0	= .
	.globl	G$strrchr$0$0
	C$string.c$139$1_0$59	= .
	.globl	C$string.c$139$1_0$59
;string.c:139: char *strrchr(char *s, int c)
;	---------------------------------
; Function strrchr
; ---------------------------------
_strrchr::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$string.c$141$1_0$59	= .
	.globl	C$string.c$141$1_0$59
;string.c:141: char *ptr = (const char *) s;
	ld	c, 4 (ix)
	ld	b, 5 (ix)
	C$string.c$142$1_0$59	= .
	.globl	C$string.c$142$1_0$59
;string.c:142: char *retptr = NULL;
	ld	hl, #0x0000
	C$string.c$144$1_0$59	= .
	.globl	C$string.c$144$1_0$59
;string.c:144: while (ptr[0] != '\0') {
00103$:
	ld	a, (bc)
	or	a, a
	jr	Z, 00105$
	C$string.c$145$2_0$60	= .
	.globl	C$string.c$145$2_0$60
;string.c:145: if (ptr[0] == c) {
	ld	e, a
	ld	d, #0x00
	ld	a, 6 (ix)
	sub	a, e
	jr	NZ, 00102$
	ld	a, 7 (ix)
	sub	a, d
	jr	NZ, 00102$
	C$string.c$146$3_0$61	= .
	.globl	C$string.c$146$3_0$61
;string.c:146: retptr = (char *) ptr;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
00102$:
	C$string.c$148$2_0$60	= .
	.globl	C$string.c$148$2_0$60
;string.c:148: ptr ++;
	inc	bc
	jr	00103$
00105$:
	C$string.c$150$1_0$59	= .
	.globl	C$string.c$150$1_0$59
;string.c:150: return retptr;
	C$string.c$151$1_0$59	= .
	.globl	C$string.c$151$1_0$59
;string.c:151: }
	pop	ix
	C$string.c$151$1_0$59	= .
	.globl	C$string.c$151$1_0$59
	XG$strrchr$0$0	= .
	.globl	XG$strrchr$0$0
	ret
	G$strsep$0$0	= .
	.globl	G$strsep$0$0
	C$string.c$153$1_0$63	= .
	.globl	C$string.c$153$1_0$63
;string.c:153: char * strsep(char **stringp, const char *delim)
;	---------------------------------
; Function strsep
; ---------------------------------
_strsep::
	push	ix
	ld	ix,#0
	add	ix,sp
	ld	hl, #-12
	add	hl, sp
	ld	sp, hl
	C$string.c$159$1_0$63	= .
	.globl	C$string.c$159$1_0$63
;string.c:159: if ((s = *stringp) == NULL)
	ld	a, 4 (ix)
	ld	-12 (ix), a
	ld	a, 5 (ix)
	ld	-11 (ix), a
	pop	hl
	push	hl
	ld	a, (hl)
	ld	-4 (ix), a
	inc	hl
	ld	a, (hl)
	ld	-3 (ix), a
	ld	a, -4 (ix)
	ld	-2 (ix), a
	ld	a, -3 (ix)
	ld	-1 (ix), a
	ld	a, -3 (ix)
	or	a, -4 (ix)
	jr	NZ, 00102$
	C$string.c$160$1_0$63	= .
	.globl	C$string.c$160$1_0$63
;string.c:160: return (NULL);
	ld	hl, #0x0000
	jp	00114$
00102$:
	C$string.c$161$2_0$64	= .
	.globl	C$string.c$161$2_0$64
;string.c:161: for (tok = s;;) {
	ld	a, -2 (ix)
	ld	-10 (ix), a
	ld	a, -1 (ix)
	ld	-9 (ix), a
	ld	a, -2 (ix)
	ld	-4 (ix), a
	ld	a, -1 (ix)
	ld	-3 (ix), a
00112$:
	C$string.c$162$3_0$65	= .
	.globl	C$string.c$162$3_0$65
;string.c:162: c = *s++;
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	a, (hl)
	inc	-4 (ix)
	jr	NZ, 00148$
	inc	-3 (ix)
00148$:
	ld	-8 (ix), a
	ld	-7 (ix), #0x00
	C$string.c$163$3_0$65	= .
	.globl	C$string.c$163$3_0$65
;string.c:163: spanp = delim;
	ld	a, 6 (ix)
	ld	-2 (ix), a
	ld	a, 7 (ix)
	ld	-1 (ix), a
	C$string.c$164$3_0$65	= .
	.globl	C$string.c$164$3_0$65
;string.c:164: do {
00108$:
	C$string.c$165$4_0$66	= .
	.globl	C$string.c$165$4_0$66
;string.c:165: if ((sc = *spanp++) == c) {
	ld	l, -2 (ix)
	ld	h, -1 (ix)
	ld	c, (hl)
	inc	-2 (ix)
	jr	NZ, 00149$
	inc	-1 (ix)
00149$:
	ld	b, #0x00
	ld	-6 (ix), c
	ld	-5 (ix), b
	ld	l, -8 (ix)
	ld	h, -7 (ix)
	cp	a, a
	sbc	hl, bc
	jr	NZ, 00109$
	C$string.c$166$2_0$63	= .
	.globl	C$string.c$166$2_0$63
;string.c:166: if (c == 0)
	ld	c, -4 (ix)
	ld	b, -3 (ix)
	ld	a, -7 (ix)
	or	a, -8 (ix)
	jr	NZ, 00104$
	C$string.c$167$5_0$67	= .
	.globl	C$string.c$167$5_0$67
;string.c:167: s = NULL;
	ld	bc, #0x0000
	jr	00105$
00104$:
	C$string.c$169$5_0$67	= .
	.globl	C$string.c$169$5_0$67
;string.c:169: s[-1] = 0;
	ld	l, -4 (ix)
	ld	h, -3 (ix)
	ld	de, #0xffff
	add	hl, de
	ld	(hl), #0x00
00105$:
	C$string.c$170$5_0$67	= .
	.globl	C$string.c$170$5_0$67
;string.c:170: *stringp = s;
	pop	hl
	push	hl
	ld	(hl), c
	inc	hl
	ld	(hl), b
	C$string.c$171$5_0$67	= .
	.globl	C$string.c$171$5_0$67
;string.c:171: return (tok);
	pop	de
	pop	hl
	push	hl
	push	de
	jr	00114$
00109$:
	C$string.c$173$3_0$65	= .
	.globl	C$string.c$173$3_0$65
;string.c:173: } while (sc != 0);
	ld	a, -5 (ix)
	or	a, -6 (ix)
	jr	NZ, 00108$
	jr	00112$
00114$:
	C$string.c$175$2_0$63	= .
	.globl	C$string.c$175$2_0$63
;string.c:175: }
	ld	sp, ix
	pop	ix
	C$string.c$175$2_0$63	= .
	.globl	C$string.c$175$2_0$63
	XG$strsep$0$0	= .
	.globl	XG$strsep$0$0
	ret
	G$strcspn$0$0	= .
	.globl	G$strcspn$0$0
	C$string.c$177$2_0$69	= .
	.globl	C$string.c$177$2_0$69
;string.c:177: size_t strcspn(const char *s1, const char *s2) {
;	---------------------------------
; Function strcspn
; ---------------------------------
_strcspn::
	push	ix
	ld	ix,#0
	add	ix,sp
	push	af
	C$string.c$178$2_0$69	= .
	.globl	C$string.c$178$2_0$69
;string.c:178: size_t res = 0;
	ld	de, #0x0000
	C$string.c$179$1_0$69	= .
	.globl	C$string.c$179$1_0$69
;string.c:179: while (*s1 != '\0') {
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
	xor	a, a
	ld	-2 (ix), a
	ld	-1 (ix), a
00104$:
	ld	a, (hl)
	or	a, a
	jr	Z, 00106$
	C$string.c$180$2_0$70	= .
	.globl	C$string.c$180$2_0$70
;string.c:180: if (strchr(s2, *s1) == NULL) {
	ld	b, #0x00
	push	hl
	push	de
	ld	c, a
	push	bc
	ld	c, 6 (ix)
	ld	b, 7 (ix)
	push	bc
	call	_strchr
	pop	af
	pop	af
	ld	c, l
	ld	b, h
	pop	de
	pop	hl
	ld	a, b
	or	a, c
	jr	NZ, 00102$
	C$string.c$181$3_0$71	= .
	.globl	C$string.c$181$3_0$71
;string.c:181: ++s1;
	inc	hl
	C$string.c$182$3_0$71	= .
	.globl	C$string.c$182$3_0$71
;string.c:182: ++res;
	inc	-2 (ix)
	jr	NZ, 00124$
	inc	-1 (ix)
00124$:
	pop	de
	push	de
	jr	00104$
00102$:
	C$string.c$184$3_0$72	= .
	.globl	C$string.c$184$3_0$72
;string.c:184: return res;
	ex	de, hl
	jr	00107$
00106$:
	C$string.c$187$1_0$69	= .
	.globl	C$string.c$187$1_0$69
;string.c:187: return res;
	ex	de, hl
00107$:
	C$string.c$188$1_0$69	= .
	.globl	C$string.c$188$1_0$69
;string.c:188: }
	ld	sp, ix
	pop	ix
	C$string.c$188$1_0$69	= .
	.globl	C$string.c$188$1_0$69
	XG$strcspn$0$0	= .
	.globl	XG$strcspn$0$0
	ret
	G$strtok$0$0	= .
	.globl	G$strtok$0$0
	C$string.c$190$1_0$74	= .
	.globl	C$string.c$190$1_0$74
;string.c:190: char *strtok(char *s, const char *delim) {
;	---------------------------------
; Function strtok
; ---------------------------------
_strtok::
	push	ix
	ld	ix,#0
	add	ix,sp
	dec	sp
	C$string.c$193$1_0$74	= .
	.globl	C$string.c$193$1_0$74
;string.c:193: if (s == NULL) {
	ld	a, 5 (ix)
	or	a, 4 (ix)
	jr	NZ, 00114$
	C$string.c$194$2_0$75	= .
	.globl	C$string.c$194$2_0$75
;string.c:194: s = last;
	ld	hl, (_strtok_last_65536_74)
	ld	4 (ix), l
	ld	5 (ix), h
	C$string.c$197$1_1$74	= .
	.globl	C$string.c$197$1_1$74
;string.c:197: do {
00114$:
	ld	l, 4 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 5 (ix)
;	spillPairReg hl
;	spillPairReg hl
00105$:
	C$string.c$198$2_1$77	= .
	.globl	C$string.c$198$2_1$77
;string.c:198: ch = *s++;
	ld	c, (hl)
	inc	hl
	ld	b, #0x00
	ld	e, c
	C$string.c$199$2_1$77	= .
	.globl	C$string.c$199$2_1$77
;string.c:199: if (ch == '\0') {
	ld	a,b
	ld	d,a
	or	a, c
	jr	NZ, 00106$
	C$string.c$200$3_1$78	= .
	.globl	C$string.c$200$3_1$78
;string.c:200: return NULL;
	ld	hl, #0x0000
	jr	00110$
00106$:
	C$string.c$202$1_1$76	= .
	.globl	C$string.c$202$1_1$76
;string.c:202: } while (strchr(delim, ch));
	push	hl
	push	de
	ld	e, 6 (ix)
	ld	d, 7 (ix)
	push	de
	call	_strchr
	pop	af
	pop	af
	ex	de, hl
	pop	hl
	ld	a, d
	or	a, e
	jr	NZ, 00105$
	C$string.c$203$1_1$76	= .
	.globl	C$string.c$203$1_1$76
;string.c:203: --s;
	ld	c, l
	ld	b, h
	dec	bc
	C$string.c$204$1_1$76	= .
	.globl	C$string.c$204$1_1$76
;string.c:204: last = s + strcspn(s, delim);
	push	bc
	ld	l, 6 (ix)
;	spillPairReg hl
;	spillPairReg hl
	ld	h, 7 (ix)
;	spillPairReg hl
;	spillPairReg hl
	push	hl
	push	bc
	call	_strcspn
	pop	af
	pop	af
	ex	de, hl
	pop	bc
	ld	a, e
	ld	hl, #_strtok_last_65536_74
	add	a, c
	ld	(hl), a
	inc	hl
	ld	a, d
	adc	a, b
	ld	(hl), a
	C$string.c$194$1_1$74	= .
	.globl	C$string.c$194$1_1$74
;string.c:194: s = last;
	ld	de, (_strtok_last_65536_74)
	C$string.c$205$1_1$76	= .
	.globl	C$string.c$205$1_1$76
;string.c:205: if (*last != '\0') {
	ld	a, (de)
	ld	-1 (ix), a
	or	a, a
	jr	Z, 00109$
	C$string.c$206$2_1$79	= .
	.globl	C$string.c$206$2_1$79
;string.c:206: *last++ = '\0';
	xor	a, a
	ld	(de), a
	ld	hl, (_strtok_last_65536_74)
	inc	hl
	ld	(_strtok_last_65536_74), hl
00109$:
	C$string.c$208$1_1$76	= .
	.globl	C$string.c$208$1_1$76
;string.c:208: return s;
	ld	l, c
;	spillPairReg hl
;	spillPairReg hl
	ld	h, b
;	spillPairReg hl
;	spillPairReg hl
00110$:
	C$string.c$209$1_1$74	= .
	.globl	C$string.c$209$1_1$74
;string.c:209: }
	inc	sp
	pop	ix
	C$string.c$209$1_1$74	= .
	.globl	C$string.c$209$1_1$74
	XG$strtok$0$0	= .
	.globl	XG$strtok$0$0
	ret
	G$strerror$0$0	= .
	.globl	G$strerror$0$0
	C$string.c$211$1_1$81	= .
	.globl	C$string.c$211$1_1$81
;string.c:211: char *strerror(int en)
;	---------------------------------
; Function strerror
; ---------------------------------
_strerror::
	push	ix
	ld	ix,#0
	add	ix,sp
	C$string.c$213$1_0$81	= .
	.globl	C$string.c$213$1_0$81
;string.c:213: switch(en) {
	ld	a, 4 (ix)
	or	a, a
	or	a, 5 (ix)
	jr	Z, 00101$
	ld	a, 4 (ix)
	sub	a, #0x02
	or	a, 5 (ix)
	jr	Z, 00102$
	ld	a, 4 (ix)
	sub	a, #0x05
	or	a, 5 (ix)
	jr	Z, 00103$
	ld	a, 4 (ix)
	sub	a, #0x07
	or	a, 5 (ix)
	jr	Z, 00104$
	ld	a, 4 (ix)
	sub	a, #0x09
	or	a, 5 (ix)
	jr	Z, 00105$
	ld	a, 4 (ix)
	sub	a, #0x0b
	or	a, 5 (ix)
	jr	Z, 00110$
	ld	a, 4 (ix)
	sub	a, #0x16
	or	a, 5 (ix)
	jr	Z, 00106$
	ld	a, 4 (ix)
	sub	a, #0x17
	or	a, 5 (ix)
	jr	Z, 00107$
	ld	a, 4 (ix)
	sub	a, #0x19
	or	a, 5 (ix)
	jr	Z, 00108$
	ld	a, 4 (ix)
	sub	a, #0x20
	or	a, 5 (ix)
	jr	Z, 00109$
	jr	00111$
	C$string.c$214$2_0$82	= .
	.globl	C$string.c$214$2_0$82
;string.c:214: case 0:
00101$:
	C$string.c$215$2_0$82	= .
	.globl	C$string.c$215$2_0$82
;string.c:215: return (const char *) "Success";
	ld	hl, #___str_0
	jr	00112$
	C$string.c$217$2_0$82	= .
	.globl	C$string.c$217$2_0$82
;string.c:217: case ENOENT:
00102$:
	C$string.c$218$2_0$82	= .
	.globl	C$string.c$218$2_0$82
;string.c:218: return (const char *) "No such file or directory";
	ld	hl, #___str_1
	jr	00112$
	C$string.c$220$2_0$82	= .
	.globl	C$string.c$220$2_0$82
;string.c:220: case EIO:
00103$:
	C$string.c$221$2_0$82	= .
	.globl	C$string.c$221$2_0$82
;string.c:221: return (const char *) "I/O error";
	ld	hl, #___str_2
	jr	00112$
	C$string.c$223$2_0$82	= .
	.globl	C$string.c$223$2_0$82
;string.c:223: case E2BIG:
00104$:
	C$string.c$224$2_0$82	= .
	.globl	C$string.c$224$2_0$82
;string.c:224: return (const char *) "Argument list too long";
	ld	hl, #___str_3
	jr	00112$
	C$string.c$226$2_0$82	= .
	.globl	C$string.c$226$2_0$82
;string.c:226: case EBADF:
00105$:
	C$string.c$227$2_0$82	= .
	.globl	C$string.c$227$2_0$82
;string.c:227: return (const char *) "Bad file descriptor";
	ld	hl, #___str_4
	jr	00112$
	C$string.c$229$2_0$82	= .
	.globl	C$string.c$229$2_0$82
;string.c:229: case EINVAL:
00106$:
	C$string.c$230$2_0$82	= .
	.globl	C$string.c$230$2_0$82
;string.c:230: return (const char *) "Illegal address";
	ld	hl, #___str_5
	jr	00112$
	C$string.c$232$2_0$82	= .
	.globl	C$string.c$232$2_0$82
;string.c:232: case ENFILE:
00107$:
	C$string.c$233$2_0$82	= .
	.globl	C$string.c$233$2_0$82
;string.c:233: return (const char *) "File table overflow";
	ld	hl, #___str_6
	jr	00112$
	C$string.c$235$2_0$82	= .
	.globl	C$string.c$235$2_0$82
;string.c:235: case ENOTTY:
00108$:
	C$string.c$236$2_0$82	= .
	.globl	C$string.c$236$2_0$82
;string.c:236: return (const char *) "Not a typewriter";
	ld	hl, #___str_7
	jr	00112$
	C$string.c$238$2_0$82	= .
	.globl	C$string.c$238$2_0$82
;string.c:238: case EPIPE:
00109$:
	C$string.c$239$2_0$82	= .
	.globl	C$string.c$239$2_0$82
;string.c:239: return (const char *) "Transport endpoint not connected";
	ld	hl, #___str_8
	jr	00112$
	C$string.c$241$2_0$82	= .
	.globl	C$string.c$241$2_0$82
;string.c:241: case EAGAIN:
00110$:
	C$string.c$242$2_0$82	= .
	.globl	C$string.c$242$2_0$82
;string.c:242: return (const char *) "Try again";
	ld	hl, #___str_9
	jr	00112$
	C$string.c$244$1_0$81	= .
	.globl	C$string.c$244$1_0$81
;string.c:244: }
00111$:
	C$string.c$246$1_0$81	= .
	.globl	C$string.c$246$1_0$81
;string.c:246: return "Unknown error!";
	ld	hl, #___str_10
00112$:
	C$string.c$247$1_0$81	= .
	.globl	C$string.c$247$1_0$81
;string.c:247: }
	pop	ix
	C$string.c$247$1_0$81	= .
	.globl	C$string.c$247$1_0$81
	XG$strerror$0$0	= .
	.globl	XG$strerror$0$0
	ret
Fstring$__str_0$0_0$0 == .
___str_0:
	.ascii "Success"
	.db 0x00
Fstring$__str_1$0_0$0 == .
___str_1:
	.ascii "No such file or directory"
	.db 0x00
Fstring$__str_2$0_0$0 == .
___str_2:
	.ascii "I/O error"
	.db 0x00
Fstring$__str_3$0_0$0 == .
___str_3:
	.ascii "Argument list too long"
	.db 0x00
Fstring$__str_4$0_0$0 == .
___str_4:
	.ascii "Bad file descriptor"
	.db 0x00
Fstring$__str_5$0_0$0 == .
___str_5:
	.ascii "Illegal address"
	.db 0x00
Fstring$__str_6$0_0$0 == .
___str_6:
	.ascii "File table overflow"
	.db 0x00
Fstring$__str_7$0_0$0 == .
___str_7:
	.ascii "Not a typewriter"
	.db 0x00
Fstring$__str_8$0_0$0 == .
___str_8:
	.ascii "Transport endpoint not connected"
	.db 0x00
Fstring$__str_9$0_0$0 == .
___str_9:
	.ascii "Try again"
	.db 0x00
Fstring$__str_10$0_0$0 == .
___str_10:
	.ascii "Unknown error!"
	.db 0x00
	.area _CODE
	.area _INITIALIZER
	.area _CABS (ABS)
