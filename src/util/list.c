/*
 * list.h
 *
 * Linked list header file.
 * 
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 05.06.2012   tstih
 *
 */
#include <util/list.h>

uint8_t _list_match_eq(list_header_t *p, uint16_t arg) {
        return ( ((uint16_t)p) == arg );
}

list_header_t* _list_find(
        list_header_t *first,
        list_header_t **prev,
        uint8_t ((*match)(list_header_t *p, uint16_t arg)),
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

list_header_t *_list_insert(list_header_t** first, list_header_t *el) {
        el->next=*first;
        *first=el;
	return el;
}

list_header_t *_list_append(list_header_t** first, list_header_t *el) {

	list_header_t *current;

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

list_header_t *_list_remove(list_header_t **first, list_header_t *el) {
	list_header_t *prev;
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

list_header_t *_list_remove_first(list_header_t **first) {
	list_header_t *result;	
	if (*first==NULL) return NULL; /* empty list */
	result=*first;
	*first = (list_header_t*) ((*first)->next);
	return result;
}
