/**
 * test_heap.c
 * The test suite for the Heap implementation
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
#include "heap.h"

// Prototypes
void test_heap_create(void);
void test_heap_insert(void);
void test_heap_peek(void);
void test_heap_remove(void);
void test_heap_max_heap_property(void);
void test_heap_empty_behavior(void);
void test_heap_reuse_after_remove(void);
void test_heap_large_insert(void);
void test_heap_remove_until_empty(void);
void test_heap_single_element(void);
void test_heap_mixed_operations(void);
void test_heap_resize(void);
void test_heap_extract_sorted(void);
void test_heap_duplicates(void);
void test_heap_stress_mix(void);

int compare_int(void *a, void *b) {
    int num1 = * (int *)a;
    int num2 = * (int *)b;

    if (num1 == num2) {
        return 0;
    } else if (num1 > num2) {
        return 1;
    } else {
        return -1;
    }
}

int main(void) {
    TEST(test_heap_create);
    TEST(test_heap_insert);
    TEST(test_heap_peek);
    TEST(test_heap_remove);
    TEST(test_heap_max_heap_property);
    TEST(test_heap_empty_behavior);
    TEST(test_heap_reuse_after_remove);
    TEST(test_heap_large_insert);
    TEST(test_heap_remove_until_empty);
    TEST(test_heap_single_element);
    TEST(test_heap_mixed_operations);
    TEST(test_heap_resize);
    TEST(test_heap_extract_sorted);
    TEST(test_heap_duplicates);
    TEST(test_heap_stress_mix);

    return 0;
}

void test_heap_create(void) {
    struct Heap *heap = heap_create(sizeof(int));

    ASSERT_NOT_NULL(heap);
    ASSERT_EQ(heap_size(heap), 0);
    ASSERT_TRUE(heap_capacity(heap) > 0);
    ASSERT_TRUE(heap_isempty(heap));

    heap_discard(heap);
}

void test_heap_insert(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 10, b = 20;

    ASSERT_TRUE(heap_insert(heap, &a, sizeof(int), compare_int));
    ASSERT_EQ(heap_size(heap), 1);

    ASSERT_TRUE(heap_insert(heap, &b, sizeof(int), compare_int));
    ASSERT_EQ(heap_size(heap), 2);

    heap_discard(heap);
}

void test_heap_peek(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 42;
    heap_insert(heap, &a, sizeof(int), compare_int);

    int *root = (int *)heap_peek(heap);

    ASSERT_EQ(*root, 42);

    heap_discard(heap);
}

void test_heap_remove(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 100;
    heap_insert(heap, &a, sizeof(int), compare_int);

    int out;
    ASSERT_TRUE(heap_remove(heap, &out, compare_int));
    ASSERT_EQ(out, 100);
    ASSERT_EQ(heap_size(heap), 0);

    heap_discard(heap);
}

void test_heap_max_heap_property(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int values[] = {5, 20, 3, 50, 10};

    for (int i = 0; i < 5; i++) {
        heap_insert(heap, &values[i], sizeof(int), compare_int);
    }

    int root = *(int *)heap_peek(heap);

    // max element must be at root
    ASSERT_EQ(root, 50);

    heap_discard(heap);
}

void test_heap_empty_behavior(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int out;

    ASSERT_FALSE(heap_remove(heap, &out, compare_int));
    ASSERT_TRUE(heap_isempty(heap));

    heap_discard(heap);
}

void test_heap_reuse_after_remove(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 10, b = 20;

    heap_insert(heap, &a, sizeof(int), compare_int);
    heap_remove(heap, &a, compare_int);

    ASSERT_TRUE(heap_isempty(heap));

    heap_insert(heap, &b, sizeof(int), compare_int);

    ASSERT_EQ(*(int *)heap_peek(heap), 20);

    heap_discard(heap);
}

void test_heap_large_insert(void) {
    struct Heap *heap = heap_create(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        heap_insert(heap, &i, sizeof(int), compare_int);
    }

    ASSERT_EQ(heap_size(heap), 1000);

    int root = *(int *)heap_peek(heap);
    ASSERT_EQ(root, 999);

    heap_discard(heap);
}

void test_heap_remove_until_empty(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 10, b = 20, c = 30;

    heap_insert(heap, &a, sizeof(int), compare_int);
    heap_insert(heap, &b, sizeof(int), compare_int);
    heap_insert(heap, &c, sizeof(int), compare_int);

    int out;

    ASSERT_TRUE(heap_remove(heap, &out, compare_int));
    ASSERT_TRUE(heap_remove(heap, &out, compare_int));
    ASSERT_TRUE(heap_remove(heap, &out, compare_int));

    ASSERT_TRUE(heap_isempty(heap));

    heap_discard(heap);
}

void test_heap_single_element(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 42;

    heap_insert(heap, &a, sizeof(int), compare_int);

    ASSERT_EQ(heap_size(heap), 1);
    ASSERT_EQ(*(int *)heap_peek(heap), 42);

    int out;
    ASSERT_TRUE(heap_remove(heap, &out, compare_int));
    ASSERT_EQ(out, 42);

    ASSERT_TRUE(heap_isempty(heap));

    heap_discard(heap);
}

void test_heap_mixed_operations(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 10, b = 50, c = 30, d = 40;

    heap_insert(heap, &a, sizeof(int), compare_int);
    heap_insert(heap, &b, sizeof(int), compare_int);

    int out;
    heap_remove(heap, &out, compare_int); // removes 50

    heap_insert(heap, &c, sizeof(int), compare_int);
    heap_insert(heap, &d, sizeof(int), compare_int);

    ASSERT_EQ(heap_size(heap), 3);

    // Root must be >= children (max heap property)
    int root = *(int *)heap_peek(heap);
    ASSERT_TRUE(root >= 30);
    ASSERT_TRUE(root >= 10);

    heap_discard(heap);
}

void test_heap_resize(void) {
    struct Heap *heap = heap_create(sizeof(int));

    for (int i = 0; i < 100; i++) {
        heap_insert(heap, &i, sizeof(int), compare_int);
    }

    ASSERT_EQ(heap_size(heap), 100);
    ASSERT_TRUE(heap_capacity(heap) >= 100);

    heap_discard(heap);
}

void test_heap_extract_sorted(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int values[] = {5, 1, 9, 3, 7, 2, 8};

    for (int i = 0; i < 7; i++) {
        heap_insert(heap, &values[i], sizeof(int), compare_int);
    }

    int prev = 10000;
    int out;

    while (!heap_isempty(heap)) {
        heap_remove(heap, &out, compare_int);
        ASSERT_TRUE(out <= prev);
        prev = out;
    }

    heap_discard(heap);
}

void test_heap_duplicates(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int a = 10, b = 10, c = 10;

    heap_insert(heap, &a, sizeof(int), compare_int);
    heap_insert(heap, &b, sizeof(int), compare_int);
    heap_insert(heap, &c, sizeof(int), compare_int);

    ASSERT_EQ(heap_size(heap), 3);

    int out;
    heap_remove(heap, &out, compare_int);
    ASSERT_EQ(out, 10);

    heap_remove(heap, &out, compare_int);
    ASSERT_EQ(out, 10);

    heap_remove(heap, &out, compare_int);
    ASSERT_EQ(out, 10);

    heap_discard(heap);
}

void test_heap_stress_mix(void) {
    struct Heap *heap = heap_create(sizeof(int));

    int out;

    for (int i = 0; i < 200; i++) {
        heap_insert(heap, &i, sizeof(int), compare_int);

        if (i % 3 == 0 && !heap_isempty(heap)) {
            heap_remove(heap, &out, compare_int);
        }
    }

    ASSERT_TRUE(heap_size(heap) >= 0);

    heap_discard(heap);
}
