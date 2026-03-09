/*
 * tmem.c
 *
 * Tests for internal memory and list helpers used by stdlib allocation.
 *
 * MIT License (see: LICENSE)
 * copyright (c) 2021 tomaz stih
 *
 * 01.03.2026   tstih
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "../src/util/_list.h"
#include "test_macros.h"

int g_failures = 0;
int g_tests_run = 0;
int g_tests_failed = 0;
const char *g_current_test = "";

#define BLK_SIZE      5
#define NEW           0x00
#define ALLOCATED     0x01

typedef struct _block_s {
    _list_header_t hdr;
    uint8_t       stat;
    uint16_t      size;
    uint8_t       data[1];
} _block_t;

extern void _heap_init(uint16_t start, uint16_t size);
extern void *_alloc(uint16_t heap, size_t size);
extern void _dealloc(uint16_t heap, void *p);
extern void _memory_init(void);
extern size_t _memtop(void);
extern void _libinit(void);

static uint8_t heapbuf[96];

static uint16_t heap_start(void) {
    return (uint16_t)(size_t)heapbuf;
}

static uint16_t initial_free_size(void) {
    return (uint16_t)(sizeof(heapbuf) - BLK_SIZE);
}

typedef struct _node_s {
    _list_header_t hdr;
    int id;
} node_t;

TEST(heap_init_single_block) {
    _block_t *b0 = (_block_t *)heapbuf;
    _heap_init(heap_start(), (uint16_t)sizeof(heapbuf));
    EXPECT_TRUE(b0->hdr.next == NULL);
    EXPECT_EQ_INT(NEW, b0->stat);
    EXPECT_EQ_INT((int)initial_free_size(), (int)b0->size);
}

TEST(alloc_splits_large_remainder) {
    _block_t *b0 = (_block_t *)heapbuf;
    _block_t *b1;
    uint16_t expected_tail;
    void *p;

    _heap_init(heap_start(), (uint16_t)sizeof(heapbuf));
    p = _alloc(heap_start(), 10);
    ASSERT_TRUE(p != NULL);
    EXPECT_TRUE(p == (void *)(heapbuf + BLK_SIZE));

    EXPECT_EQ_INT(ALLOCATED, b0->stat);
    EXPECT_EQ_INT(10, (int)b0->size);

    b1 = (_block_t *)b0->hdr.next;
    ASSERT_TRUE(b1 != NULL);
    expected_tail = (uint16_t)(initial_free_size() - 10 - BLK_SIZE);
    EXPECT_EQ_INT(NEW, b1->stat);
    EXPECT_EQ_INT((int)expected_tail, (int)b1->size);
}

TEST(alloc_no_split_small_remainder) {
    _block_t *b0 = (_block_t *)heapbuf;
    void *p;

    _heap_init(heap_start(), (uint16_t)sizeof(heapbuf));
    p = _alloc(heap_start(), (size_t)(initial_free_size() - 7));
    ASSERT_TRUE(p != NULL);
    EXPECT_EQ_INT(ALLOCATED, b0->stat);
    EXPECT_TRUE(b0->hdr.next == NULL);
    EXPECT_EQ_INT((int)initial_free_size(), (int)b0->size);
}

TEST(dealloc_merges_prev_and_next) {
    _block_t *b0 = (_block_t *)heapbuf;
    void *a, *b, *c;

    _heap_init(heap_start(), (uint16_t)sizeof(heapbuf));
    a = _alloc(heap_start(), 8);
    b = _alloc(heap_start(), 8);
    c = _alloc(heap_start(), 8);
    ASSERT_TRUE(a != NULL);
    ASSERT_TRUE(b != NULL);
    ASSERT_TRUE(c != NULL);

    _dealloc(heap_start(), a);
    _dealloc(heap_start(), c);
    _dealloc(heap_start(), b);

    EXPECT_TRUE(b0->hdr.next == NULL);
    EXPECT_EQ_INT(NEW, b0->stat);
    EXPECT_EQ_INT((int)initial_free_size(), (int)b0->size);
}

TEST(dealloc_unknown_pointer_noop) {
    _block_t *b0 = (_block_t *)heapbuf;
    void *a;
    void *old_next;
    uint16_t old_size;
    uint8_t old_stat;

    _heap_init(heap_start(), (uint16_t)sizeof(heapbuf));
    a = _alloc(heap_start(), 8);
    ASSERT_TRUE(a != NULL);

    old_next = b0->hdr.next;
    old_size = b0->size;
    old_stat = b0->stat;

    _dealloc(heap_start(), (void *)((uint8_t *)a + 1));

    EXPECT_EQ_INT((int)old_stat, (int)b0->stat);
    EXPECT_EQ_INT((int)old_size, (int)b0->size);
    EXPECT_EQ_LONG((long)(size_t)old_next, (long)(size_t)b0->hdr.next);

    _dealloc(heap_start(), a);
}

TEST(list_insert_find_remove) {
    node_t n1, n2, n3;
    _list_header_t *first = NULL;
    _list_header_t *prev = NULL;
    _list_header_t *found;

    _list_insert(&first, &n1.hdr);
    _list_insert(&first, &n2.hdr);
    _list_insert(&first, &n3.hdr);
    EXPECT_TRUE(first == &n3.hdr);

    found = _list_find(first, &prev, _list_match_eq, (uint16_t)(size_t)&n2.hdr);
    ASSERT_TRUE(found == &n2.hdr);
    EXPECT_TRUE(prev == &n3.hdr);

    EXPECT_TRUE(_list_remove(&first, &n2.hdr) == &n2.hdr);
    EXPECT_TRUE(first == &n3.hdr);
    EXPECT_TRUE(n3.hdr.next == &n1.hdr);
}

TEST(list_append_remove_first_and_missing) {
    node_t n1, n2;
    node_t nx;
    _list_header_t *first = NULL;

    _list_append(&first, &n1.hdr);
    _list_append(&first, &n2.hdr);
    EXPECT_TRUE(first == &n1.hdr);
    EXPECT_TRUE(n1.hdr.next == &n2.hdr);
    EXPECT_TRUE(n2.hdr.next == NULL);

    EXPECT_TRUE(_list_remove_first(&first) == &n1.hdr);
    EXPECT_TRUE(first == &n2.hdr);
    EXPECT_TRUE(_list_remove_first(&first) == &n2.hdr);
    EXPECT_TRUE(_list_remove_first(&first) == NULL);

    _list_append(&first, &n1.hdr);
    EXPECT_TRUE(_list_remove(&first, &nx.hdr) == NULL);
}

TEST(list_match_eq_works) {
    node_t n1;
    EXPECT_TRUE(_list_match_eq(&n1.hdr, (uint16_t)(size_t)&n1.hdr));
    EXPECT_TRUE(!_list_match_eq(&n1.hdr, (uint16_t)(size_t)0x1234));
}

TEST(memory_init_and_memtop_smoke) {
    size_t top = _memtop();
    EXPECT_TRUE(top != 0);
    _memory_init();
    {
        void *p = malloc(8);
        ASSERT_TRUE(p != NULL);
        free(p);
    }
}

TEST(msleep_and_libinit_smoke) {
    int before = g_failures;
    _msleep(1);
    _libinit();
    EXPECT_EQ_INT(before, g_failures);
}

int main(void) {
    puts("TMEM: memory/internal tests");
    RUN_TEST(heap_init_single_block);
    RUN_TEST(alloc_splits_large_remainder);
    RUN_TEST(alloc_no_split_small_remainder);
    RUN_TEST(dealloc_merges_prev_and_next);
    RUN_TEST(dealloc_unknown_pointer_noop);
    RUN_TEST(list_insert_find_remove);
    RUN_TEST(list_append_remove_first_and_missing);
    RUN_TEST(list_match_eq_works);
    RUN_TEST(memory_init_and_memtop_smoke);
    RUN_TEST(msleep_and_libinit_smoke);
    if (g_failures == 0) {
        printf("PASS all %d tests\n", g_tests_run);
        return 0;
    }
    printf("FAIL %d failures in %d/%d tests\n",
        g_failures, g_tests_failed, g_tests_run);
    return 1;
}
