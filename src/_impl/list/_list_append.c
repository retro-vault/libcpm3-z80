/*
 * _list_append.c
 *
 * Append a node to the tail of an internal singly-linked list.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <_impl/list/_list.h>

_list_header_t *_list_append(_list_header_t** first, _list_header_t *el) {

	_list_header_t *current;

	el->next=NULL;		/* it's always the last element */

	if (*first==NULL)	/* empty list? */
        	*first=el;
	else {
		current=*first;
		while (current->next) current=current->next;
		current->next=el;
	}
	return el;
}
