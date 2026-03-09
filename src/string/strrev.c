/*
 * strrev.c
 *
 * Reverse the contents of a string buffer in place.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2026 tomaz stih
 *
 * 09.03.2026   tstih
 *
 */
#include <string.h>

void strrev(char *s, register size_t n)
{
	int start = 0;
	int end = n -1;
    char tmp;
	while (start < end)
	{
        /* swap. */
        tmp=*(s+start);
        *(s+start)=*(s+end);
        *(s+end)=tmp;
		start++;
		end--;
	}
}
