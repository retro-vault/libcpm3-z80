/*
 * _list_remove.c
 *
 * Remove a specific node from an internal singly-linked list.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include "_list.h"

_list_header_t *_list_remove(_list_header_t **first, _list_header_t *el) {
	_list_header_t *prev;
	if (el==*first) {
		*first=el->next;
	} else {
		if (!_list_find(*first, &prev, _list_match_eq, (uint16_t) el))
			return NULL;
		else  /* rewire */
			prev->next=el->next;
	}
	return el;
}
