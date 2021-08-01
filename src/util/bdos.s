        ;; bdos.s
        ;; 
        ;; cp/m bdos and extended bdos calls
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
		;; 26.04.2021   tstih
        .module bdos

        .globl __bdos
        .globl __bdosex

        .equ    BDOS, 5

        .area _CODE


        ;; ------------------------------
        ;; uint8_t _bdos(bdos_call_t *p);
        ;; ------------------------------
        ;; calls cp/m bdos
        ;; input:	bdos_call_t struct on stack
        ;; affect:  af, bc, de, hl
__bdos::
        push    ix                      ; store ix
		call    rawbdos                 ; raw bdos fn call
		pop     ix                      ; restore ix
		ret


        ;; ----------------------
        ;; uint8_t _bdosex(
        ;;     bdos_call_t *p, 
        ;;     uint16_t* ret_ba, 
        ;;     uint16_t *ret_hl);
        ;; ----------------------
        ;; calls cp/m bdos and store result to variables
        ;; input:	bdos_call_t struct on stack, pointer to ba and hl structures
        ;; output: a, b, hl populated with ret. values
        ;; affect:  af, bc, de, hl
__bdosex::
        ;; classic bdos call!
        push    ix
        call    rawbdos

		;; store ret value.
		push    hl

        ;; get ptr to ret_ba (ix still points to stack)
        ;; and store a and b values into it
		ld      l,2(ix)
		ld      h,3(ix) 
		ld      (hl),a
		inc     hl
		ld      (hl),b

        ;; get ptr to ret_hl and store hl into it
		ld      l,4(ix)
		ld      h,5(ix)
		pop     bc		                ; recover the HL we have pushed
		ld      (hl),c
		inc     hl
		ld      (hl),b

        ;; finally, return byte in c    
        ld      l,c

		pop     ix                      ; restore ix
		ret


        ;; raw bdos call
        ;; input:	bdos_call_t struct pointer on stack
        ;; output:  ix=stack, (a,b,de)=potential result
        ;; affect:  af, bc, de, hl, ix
rawbdos:
        ld      ix,#6
		add     ix,sp                   ; ix=sp
		ld      l,(ix)                  ; load bdos struct into hl
		ld      h,1(ix)
		ld      c,(hl)                  ; and bdos function into c.
		inc     hl
		ld      e,(hl)                  ; load bdos parameter into de
		inc     hl
		ld      d,(hl)
		call    BDOS                    ; make BDOS call!
        ret