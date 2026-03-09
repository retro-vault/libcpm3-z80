/*
 * _list_match_eq.c
 *
 * Match a list node against a key by pointer equality.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <_impl/list/_list.h>

uint8_t _list_match_eq(_list_header_t *p, uint16_t arg) {
        return ( ((uint16_t)p) == arg );
}
