#include <util/list.h>

uint8_t _list_match_eq(list_header_t *p, uint16_t arg) {
        return ( ((uint16_t)p) == arg );
}