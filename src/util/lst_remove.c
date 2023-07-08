#include <util/list.h>

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