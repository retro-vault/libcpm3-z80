#include <util/list.h>

list_header_t *_list_insert(list_header_t** first, list_header_t *el) {
        el->next=*first;
        *first=el;
	return el;
}