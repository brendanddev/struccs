/**
 * test_ll.c
 * The test suite for the LinkedList implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "test_utils.h"
#include "linked_list.h"

// Prototypes
void test_linkedlist_create(void);
void test_linkedlist_clear(void);
void test_linkedlist_is_empty(void);
void test_linkedlist_insert(void);
void test_linkedlist_insert_tail(void);
void test_linkedlist_insert_at(void);
void test_linkedlist_remove(void);
void test_linkedlist_remove_tail(void);
void test_linkedlist_remove_at(void);
void test_linkedlist_remove_single_element(void);
void test_linkedlist_get(void);
void test_linkedlist_get_invalid_index(void);
void test_linkedlist_set(void);
void test_linkedlist_set_invalid_index(void);
void test_linkedlist_find(void);
void test_linkedlist_contains(void);
void test_linkedlist_reverse(void);
void test_linkedlist_size_consistency(void);
void test_linkedlist_reuse_after_empty(void);
void test_linkedlist_copy(void);
void test_linkedlist_struct_type(void);
void test_linkedlist_string_pointer(void);
void test_linkedlist_large_operations(void);

int main(void) {
    TEST(test_linkedlist_create);
    TEST(test_linkedlist_clear);
    TEST(test_linkedlist_is_empty);
    TEST(test_linkedlist_insert);
    TEST(test_linkedlist_insert_tail);
    TEST(test_linkedlist_insert_at);
    TEST(test_linkedlist_remove);
    TEST(test_linkedlist_remove_tail);
    TEST(test_linkedlist_remove_at);
    TEST(test_linkedlist_remove_single_element);
    TEST(test_linkedlist_get);
    TEST(test_linkedlist_get_invalid_index);
    TEST(test_linkedlist_set);
    TEST(test_linkedlist_set_invalid_index);
    TEST(test_linkedlist_find);
    TEST(test_linkedlist_contains);
    TEST(test_linkedlist_reverse);
    TEST(test_linkedlist_size_consistency);
    TEST(test_linkedlist_reuse_after_empty);
    TEST(test_linkedlist_copy);
    TEST(test_linkedlist_struct_type);
    TEST(test_linkedlist_string_pointer);
    TEST(test_linkedlist_large_operations);

    return 0;
}

void test_linkedlist_create(void) {
    struct LinkedList *list = ll_create();

    ASSERT_NOT_NULL(list);
    ASSERT_EQ(ll_size(list), 0);
    ASSERT_TRUE(ll_is_empty(list));

    ll_discard(list);
}

void test_linkedlist_clear(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    ASSERT_EQ(ll_size(list), 3);

    ll_clear(list);

    ASSERT_EQ(ll_size(list), 0);
    ASSERT_TRUE(ll_is_empty(list));

    // clearing again should be safe
    ll_clear(list);

    ASSERT_EQ(ll_size(list), 0);

    ll_discard(list);
}

void test_linkedlist_is_empty(void) {
    struct LinkedList *list = ll_create();

    ASSERT_TRUE(ll_is_empty(list));

    int a = 10;
    ll_insert(list, &a, sizeof(int));

    ASSERT_FALSE(ll_is_empty(list));

    ll_remove(list);

    ASSERT_TRUE(ll_is_empty(list));

    ll_discard(list);
}

void test_linkedlist_insert(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert(list, &a, sizeof(int));
    ASSERT_EQ(ll_size(list), 1);

    ll_insert(list, &b, sizeof(int));
    ASSERT_EQ(ll_size(list), 2);

    int out;

    // insert adds to head
    ll_get(list, 0, &out);
    ASSERT_EQ(out, 2);

    ll_get(list, 1, &out);
    ASSERT_EQ(out, 1);

    ll_discard(list);
}

void test_linkedlist_insert_tail(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));

    ASSERT_EQ(ll_size(list), 2);

    int out;

    ll_get(list, 0, &out);
    ASSERT_EQ(out, 1);

    ll_get(list, 1, &out);
    ASSERT_EQ(out, 2);

    ll_discard(list);
}

void test_linkedlist_insert_at(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 3;
    int c = 2;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));

    // insert in middle
    ll_insert_at(list, &c, sizeof(int), 1);

    ASSERT_EQ(ll_size(list), 3);

    int out;

    ll_get(list, 0, &out);
    ASSERT_EQ(out, 1);

    ll_get(list, 1, &out);
    ASSERT_EQ(out, 2);

    ll_get(list, 2, &out);
    ASSERT_EQ(out, 3);

    ll_discard(list);
}

void test_linkedlist_remove(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert(list, &a, sizeof(int));
    ll_insert(list, &b, sizeof(int));

    ASSERT_EQ(ll_size(list), 2);

    ll_remove(list);

    ASSERT_EQ(ll_size(list), 1);

    int out;
    ll_get(list, 0, &out);

    // b was removed from head
    ASSERT_EQ(out, 1);

    ll_discard(list);
}

void test_linkedlist_remove_tail(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));

    ll_remove_tail(list);

    ASSERT_EQ(ll_size(list), 1);

    int out;
    ll_get(list, 0, &out);

    ASSERT_EQ(out, 1);

    ll_discard(list);
}

void test_linkedlist_remove_at(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    // remove middle element
    ll_remove_at(list, 1);

    ASSERT_EQ(ll_size(list), 2);

    int out;

    ll_get(list, 0, &out);
    ASSERT_EQ(out, 1);

    ll_get(list, 1, &out);
    ASSERT_EQ(out, 3);

    ll_discard(list);
}

void test_linkedlist_remove_single_element(void) {
    struct LinkedList *list = ll_create();

    int a = 99;

    ll_insert(list, &a, sizeof(int));

    ASSERT_EQ(ll_size(list), 1);

    ll_remove(list);

    ASSERT_EQ(ll_size(list), 0);
    ASSERT_TRUE(ll_is_empty(list));

    ll_discard(list);
}

void test_linkedlist_get(void) {
    struct LinkedList *list = ll_create();

    int a = 10, b = 20, c = 30;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    int out;

    ASSERT_TRUE(ll_get(list, 0, &out));
    ASSERT_EQ(out, 10);

    ASSERT_TRUE(ll_get(list, 1, &out));
    ASSERT_EQ(out, 20);

    ASSERT_TRUE(ll_get(list, 2, &out));
    ASSERT_EQ(out, 30);

    ll_discard(list);
}

void test_linkedlist_get_invalid_index(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    ll_insert(list, &a, sizeof(int));

    int out;

    ASSERT_FALSE(ll_get(list, -1, &out));
    ASSERT_FALSE(ll_get(list, 99, &out));

    ll_discard(list);
}

void test_linkedlist_set(void) {
    struct LinkedList *list = ll_create();

    int a = 10;
    int replacement = 50;

    ll_insert(list, &a, sizeof(int));

    ASSERT_TRUE(ll_set(list, 0, &replacement));

    int out;
    ll_get(list, 0, &out);

    ASSERT_EQ(out, 50);

    ll_discard(list);
}

void test_linkedlist_set_invalid_index(void) {
    struct LinkedList *list = ll_create();

    int value = 100;

    ASSERT_FALSE(ll_set(list, 0, &value));
    ASSERT_FALSE(ll_set(list, -1, &value));

    ll_discard(list);
}

bool int_equals(void *a, void *b) {
    return *(int *)a == *(int *)b;
}

void test_linkedlist_find(void) {
    struct LinkedList *list = ll_create();

    int a = 10, b = 20, c = 30;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    ASSERT_EQ(ll_find(list, &a, int_equals), 0);
    ASSERT_EQ(ll_find(list, &b, int_equals), 1);
    ASSERT_EQ(ll_find(list, &c, int_equals), 2);

    int missing = 99;
    ASSERT_EQ(ll_find(list, &missing, int_equals), -1);

    ll_discard(list);
}

void test_linkedlist_contains(void) {
    struct LinkedList *list = ll_create();

    int a = 5;
    int b = 10;

    ll_insert(list, &a, sizeof(int));

    ASSERT_TRUE(ll_contains(list, &a, int_equals));
    ASSERT_FALSE(ll_contains(list, &b, int_equals));

    ll_discard(list);
}

void test_linkedlist_reverse(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    ll_reverse(list);

    int out;

    ll_get(list, 0, &out);
    ASSERT_EQ(out, 3);

    ll_get(list, 1, &out);
    ASSERT_EQ(out, 2);

    ll_get(list, 2, &out);
    ASSERT_EQ(out, 1);

    ll_discard(list);
}

void test_linkedlist_size_consistency(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;
    int out;

    ll_insert(list, &a, sizeof(int));
    ASSERT_EQ(ll_size(list), 1);

    ll_insert_tail(list, &b, sizeof(int));
    ASSERT_EQ(ll_size(list), 2);

    ll_insert_tail(list, &c, sizeof(int));
    ASSERT_EQ(ll_size(list), 3);

    ll_remove_at(list, 1);
    ASSERT_EQ(ll_size(list), 2);

    ll_remove(list);
    ASSERT_EQ(ll_size(list), 1);

    ll_remove_tail(list);
    ASSERT_EQ(ll_size(list), 0);

    ASSERT_TRUE(ll_is_empty(list));

    ll_discard(list);
}

void test_linkedlist_reuse_after_empty(void) {
    struct LinkedList *list = ll_create();

    int a = 10, b = 20;
    int out;

    ll_insert(list, &a, sizeof(int));
    ll_clear(list);

    ASSERT_TRUE(ll_is_empty(list));
    ASSERT_EQ(ll_size(list), 0);

    ll_insert_tail(list, &b, sizeof(int));

    ASSERT_TRUE(ll_get(list, 0, &out));
    ASSERT_EQ(out, 20);

    ll_discard(list);
}

void test_linkedlist_copy(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    struct LinkedList *copy = ll_copy(list);

    ASSERT_EQ(ll_size(copy), ll_size(list));

    int out1, out2;

    ll_get(list, 0, &out1);
    ll_get(copy, 0, &out2);
    ASSERT_EQ(out1, out2);

    ll_get(list, 2, &out1);
    ll_get(copy, 2, &out2);
    ASSERT_EQ(out1, out2);

    ll_discard(list);
    ll_discard(copy);
}

typedef struct {
    int x;
    int y;
} Point;

void test_linkedlist_struct_type(void) {
    struct LinkedList *list = ll_create();

    Point a = {1, 2};
    Point b = {3, 4};

    ll_insert_tail(list, &a, sizeof(Point));
    ll_insert_tail(list, &b, sizeof(Point));

    Point out;

    ll_get(list, 0, &out);
    ASSERT_TRUE(out.x == 1 && out.y == 2);

    ll_get(list, 1, &out);
    ASSERT_TRUE(out.x == 3 && out.y == 4);

    ll_discard(list);
}

void test_linkedlist_string_pointer(void) {
    struct LinkedList *list = ll_create();

    char *a = "hello";
    char *b = "world";

    ll_insert_tail(list, &a, sizeof(char*));
    ll_insert_tail(list, &b, sizeof(char*));

    char *out;

    ll_get(list, 0, &out);
    ASSERT_EQ(strcmp(out, "hello"), 0);

    ll_get(list, 1, &out);
    ASSERT_EQ(strcmp(out, "world"), 0);

    ll_discard(list);
}

void test_linkedlist_large_operations(void) {
    struct LinkedList *list = ll_create();

    for (int i = 0; i < 1000; i++) {
        ll_insert_tail(list, &i, sizeof(int));
    }

    ASSERT_EQ(ll_size(list), 1000);

    int out;

    for (int i = 0; i < 1000; i++) {
        ll_get(list, i, &out);
        ASSERT_EQ(out, i);
    }

    ll_reverse(list);

    for (int i = 0; i < 1000; i++) {
        ll_get(list, i, &out);
        ASSERT_EQ(out, 999 - i);
    }

    ll_discard(list);
}
