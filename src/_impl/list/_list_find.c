/*
 * _list_find.c
 *
 * Search an internal linked list using a comparator callback.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <_impl/list/_list.h>

_list_header_t* _list_find(
        _list_header_t *first,
        _list_header_t **prev,
        uint8_t ((*match)(_list_header_t *p, uint16_t arg)),
        uint16_t the_arg)
        {
        /* assume no previous */
        *prev=NULL;
	while (first && !match(first,the_arg)) {
	        *prev=first;
	        first=first->next;
	}
        /* result is in first */
        return first; 
}
