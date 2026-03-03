        ;; merge_next.s
        ;;
        ;; Merge block with next block.
        ;;
        ;; MIT License (see: LICENSE)
        ;; copyright (c) 2021 tomaz stih
        ;;
        ;; 18.02.2026   tstih
        .module merge_next

        .globl  _merge_with_next

        .equ    BLK_SIZE, 5

        .area   _CODE

        ;; --------------------------------------------------------
        ;; void _merge_with_next(block_t *b)
        ;; --------------------------------------------------------
        ;; input:
        ;;   4(ix): b low
        ;;   5(ix): b high
_merge_with_next::
        push    ix
        ld      ix,#0
        add     ix,sp

        ;; hl = b
        ld      l,4(ix)
        ld      h,5(ix)

        ;; de = bnext = b->hdr.next
        ld      e,(hl)
        inc     hl
        ld      d,(hl)

        ;; bc = b->size
        inc     hl
        inc     hl
        ld      c,(hl)
        inc     hl
        ld      b,(hl)

        ;; bc += BLK_SIZE + bnext->size
        ex      de,hl
        inc     hl
        inc     hl
        inc     hl
        ld      a,c
        add     a,(hl)
        ld      c,a
        inc     hl
        ld      a,b
        adc     a,(hl)
        ld      b,a
        ld      a,c
        add     a,#BLK_SIZE
        ld      c,a
        jr      nc,merge_store_size
        inc     b

merge_store_size:
        ;; b->size = bc
        ld      l,4(ix)
        ld      h,5(ix)
        inc     hl
        inc     hl
        inc     hl
        ld      (hl),c
        inc     hl
        ld      (hl),b

        ;; b->hdr.next = bnext->hdr.next
        ld      l,4(ix)
        ld      h,5(ix)
        ld      e,(hl)
        inc     hl
        ld      d,(hl)                        ; de = bnext
        ex      de,hl
        ld      c,(hl)
        inc     hl
        ld      b,(hl)                        ; bc = bnext->next
        ld      l,4(ix)
        ld      h,5(ix)
        ld      (hl),c
        inc     hl
        ld      (hl),b

        pop     ix
        ret
