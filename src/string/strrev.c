/*
 * strrev.c
 *
 * strrev function (see: string.h).
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 08.07.2023   tstih
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