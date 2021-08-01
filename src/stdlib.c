/*
 * stdlib.c
 *
 * Standard C library stdlib implementation.
 *
 * NOTES:
 *  rand() function uses long, can we do it with int? 
 *  Is there a way to preserve exit code? CPM 3 System control block 
 *  might have this?
 *  qsort is missing.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 28.04.2021   tstih
 *
 */
#include <util/bdos.h>
#include <util/mem.h>
#include <ctype.h>

void exit(int status)
{
    status; 
    /* Unfortunately, the status is lost in CP/M. */
    bdos_call_t bdc = { P_TERMCPM, { (uint16_t)0 } };
    _bdos(&bdc);
}

int abs(int i)
{
    return i < 0 ? -i : i;
}

int atoi(const char *str)
{
    int res = 0;
    for (int i = 0; str[i] != '\0'; ++i)
        res = res * 10 + str[i] - '0';
    return res;
}

static unsigned long _next = 1;

int rand(void) /* RAND_MAX assumed to be 32767 */
{
    _next = _next * 1103515245 + 12345;
    return (unsigned int)(_next / 65536) % 32768;
}

void srand(unsigned int seed)
{
    _next = seed;
}

const static char _cvt_in[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,           /* '0' - '9' */
    100, 100, 100, 100, 100, 100, 100,      /* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, /* 'A' - 'Z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35,
    100, 100, 100, 100, 100, 100,           /* punctuation */
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, /* 'a' - 'z' */
    20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35};

unsigned long strtoul(char *string, char **end_ptr, int base)
{
    register char *p;
    register unsigned long int result = 0;
    register unsigned digit;
    int any_digits = 0;

    /* Skip any leading blanks. */
    p = string;
    while (isspace(*p))
    {
        p += 1;
    }
    if (base == 0)
    {
        if (*p == '0')
        {
            p += 1;
            if (*p == 'x')
            {
                p += 1;
                base = 16;
            }
            else
            {
                any_digits = 1;
                base = 8;
            }
        }
        else
            base = 10;
    }
    else if (base == 16)
    {
        if ((p[0] == '0') && (p[1] == 'x'))
        {
            p += 2;
        }
    }

    if (base == 8)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > 7)
            {
                break;
            }
            result = (result << 3) + digit;
            any_digits = 1;
        }
    }
    else if (base == 10)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > 9)
            {
                break;
            }
            result = (10 * result) + digit;
            any_digits = 1;
        }
    }
    else if (base == 16)
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > ('z' - '0'))
            {
                break;
            }
            digit = _cvt_in[digit];
            if (digit > 15)
            {
                break;
            }
            result = (result << 4) + digit;
            any_digits = 1;
        }
    }
    else
    {
        for (;; p += 1)
        {
            digit = *p - '0';
            if (digit > ('z' - '0'))
            {
                break;
            }
            digit = _cvt_in[digit];
            if (digit >= base)
            {
                break;
            }
            result = result * base + digit;
            any_digits = 1;
        }
    }

    if (!any_digits)
        p = string;
    if (end_ptr != 0)
        *end_ptr = p;
    return result;
}

long strtol(char *nptr, char **endptr, int base)
{
    long result;
    char *p = nptr;
    while (isspace(*p))
    {
        p++;
    }
    if (*p == '-')
    {
        p++;
        result = -strtoul(p, endptr, base);
    }
    else
    {
        if (*p == '+')
            p++;
        result = strtoul(p, endptr, base);
    }
    if (endptr != 0 && *endptr == p)
    {
        *endptr = nptr;
    }
    return result;
}

void *malloc(size_t size)
{
    block_t *prev;
    block_t *b;

    b = (block_t *)_list_find(
        (list_header_t *)&_heap,
        (list_header_t **)&prev,
        _match_free_block, size);

    if (b)
    {
        if (b->size - size > BLK_SIZE + MIN_CHUNK_SIZE)
            _split(b, size);
        b->stat = ALLOCATED;
        return b->data;
    }
    else
        return NULL;
}

void free(void *p)
{
    block_t *prev;
    block_t *b;

    /* calculate block address from pointer */
    b = (block_t *)((uint16_t)p - BLK_SIZE);

    /* make sure it is a valid memory block by finding it */
    if (_list_find((list_header_t *)&_heap, (list_header_t **)&prev, _list_match_eq, (uint16_t)b))
    {
        b->stat = NEW;
        /* merge 3 blocks if possible */
        if (prev && !(prev->stat & ALLOCATED))
        { /* try previous */
            _merge_with_next(prev);
            b = prev;
        }
        /* try next */
        if (b->hdr.next && !(((block_t *)(b->hdr.next))->stat & ALLOCATED))
            _merge_with_next(b);
    }
}

void *calloc(size_t num, size_t size)
{
    size_t bytes = num * size;
    void *result = malloc(bytes);
    memset(result, 0, bytes);
    return result;
}