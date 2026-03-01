        ;; split.s
        ;;
        ;; Split memory block to two blocks.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 18.02.2026   tstih
        .module split

        .globl  _split

        .equ    BLK_SIZE, 5

        .area   _CODE

        ;; --------------------------------------------------------
        ;; void _split(block_t *b, uint16_t size)
        ;; --------------------------------------------------------
        ;; input:
        ;;   4(ix): b low
        ;;   5(ix): b high
        ;;   6(ix): size low
        ;;   7(ix): size high
_split::
        push    ix
        ld      ix,#0
        add     ix,sp

        ;; hl = b
        ld      l,4(ix)
        ld      h,5(ix)

        ;; de = size
        ld      e,6(ix)
        ld      d,7(ix)

        ;; bc = nw = b + BLK_SIZE + size
        ld      bc,#BLK_SIZE
        add     hl,bc
        add     hl,de
        ld      c,l
        ld      b,h

        ;; nw->hdr.next = b->hdr.next
        ld      l,4(ix)
        ld      h,5(ix)
        ld      e,(hl)
        inc     hl
        ld      d,(hl)
        ld      l,c
        ld      h,b
        ld      (hl),e
        inc     hl
        ld      (hl),d

        ;; nw->size = b->size - (size + BLK_SIZE)
        ld      l,4(ix)
        ld      h,5(ix)
        inc     hl
        inc     hl
        inc     hl
        ld      e,(hl)                        ; b->size low
        inc     hl
        ld      d,(hl)                        ; b->size high

        ld      l,6(ix)
        ld      h,7(ix)
        ld      a,l
        add     a,#BLK_SIZE
        ld      l,a
        jr      nc,split_sub
        inc     h

split_sub:
        ld      a,e
        sub     l
        ld      e,a
        ld      a,d
        sbc     a,h
        ld      d,a

        ld      l,c
        ld      h,b
        inc     hl
        inc     hl
        inc     hl
        ld      (hl),e
        inc     hl
        ld      (hl),d

        ;; nw->stat = b->stat
        ld      l,4(ix)
        ld      h,5(ix)
        inc     hl
        inc     hl
        ld      a,(hl)
        ld      l,c
        ld      h,b
        inc     hl
        inc     hl
        ld      (hl),a

        ;; b->size = size
        ld      l,4(ix)
        ld      h,5(ix)
        inc     hl
        inc     hl
        inc     hl
        ld      a,6(ix)
        ld      (hl),a
        inc     hl
        ld      a,7(ix)
        ld      (hl),a

        ;; b->hdr.next = nw
        ld      l,4(ix)
        ld      h,5(ix)
        ld      (hl),c
        inc     hl
        ld      (hl),b

        pop     ix
        ret
