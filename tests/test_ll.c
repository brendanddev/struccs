/**
 * test_ll.c
 * The test suite for the LinkedList implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
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
    test_linkedlist_create();
    test_linkedlist_clear();
    test_linkedlist_is_empty();
    test_linkedlist_insert();
    test_linkedlist_insert_tail();
    test_linkedlist_insert_at();
    test_linkedlist_remove();
    test_linkedlist_remove_tail();
    test_linkedlist_remove_at();
    test_linkedlist_remove_single_element();
    test_linkedlist_get();
    test_linkedlist_get_invalid_index();
    test_linkedlist_set();
    test_linkedlist_set_invalid_index();
    test_linkedlist_find();
    test_linkedlist_contains();
    test_linkedlist_reverse();
    test_linkedlist_size_consistency();
    test_linkedlist_reuse_after_empty();
    test_linkedlist_copy();
    test_linkedlist_struct_type();
    test_linkedlist_string_pointer();
    test_linkedlist_large_operations();

    printf("All LinkedList tests passed.\n");
    return 0;
}

void test_linkedlist_create(void) {
    struct LinkedList *list = ll_create();

    assert(list != NULL);
    assert(ll_size(list) == 0);
    assert(ll_is_empty(list) == true);

    ll_discard(list);
}

void test_linkedlist_clear(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    assert(ll_size(list) == 3);

    ll_clear(list);

    assert(ll_size(list) == 0);
    assert(ll_is_empty(list) == true);

    // clearing again should be safe
    ll_clear(list);

    assert(ll_size(list) == 0);

    ll_discard(list);
}

void test_linkedlist_is_empty(void) {
    struct LinkedList *list = ll_create();

    assert(ll_is_empty(list) == true);

    int a = 10;
    ll_insert(list, &a, sizeof(int));

    assert(ll_is_empty(list) == false);

    ll_remove(list);

    assert(ll_is_empty(list) == true);

    ll_discard(list);
}

void test_linkedlist_insert(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert(list, &a, sizeof(int));
    assert(ll_size(list) == 1);

    ll_insert(list, &b, sizeof(int));
    assert(ll_size(list) == 2);

    int out;

    // insert adds to head
    ll_get(list, 0, &out);
    assert(out == 2);

    ll_get(list, 1, &out);
    assert(out == 1);

    ll_discard(list);
}

void test_linkedlist_insert_tail(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));

    assert(ll_size(list) == 2);

    int out;

    ll_get(list, 0, &out);
    assert(out == 1);

    ll_get(list, 1, &out);
    assert(out == 2);

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

    assert(ll_size(list) == 3);

    int out;

    ll_get(list, 0, &out);
    assert(out == 1);

    ll_get(list, 1, &out);
    assert(out == 2);

    ll_get(list, 2, &out);
    assert(out == 3);

    ll_discard(list);
}

void test_linkedlist_remove(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert(list, &a, sizeof(int));
    ll_insert(list, &b, sizeof(int));

    assert(ll_size(list) == 2);

    ll_remove(list);

    assert(ll_size(list) == 1);

    int out;
    ll_get(list, 0, &out);

    // b was removed from head
    assert(out == 1);

    ll_discard(list);
}

void test_linkedlist_remove_tail(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    int b = 2;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));

    ll_remove_tail(list);

    assert(ll_size(list) == 1);

    int out;
    ll_get(list, 0, &out);

    assert(out == 1);

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

    assert(ll_size(list) == 2);

    int out;

    ll_get(list, 0, &out);
    assert(out == 1);

    ll_get(list, 1, &out);
    assert(out == 3);

    ll_discard(list);
}

void test_linkedlist_remove_single_element(void) {
    struct LinkedList *list = ll_create();

    int a = 99;

    ll_insert(list, &a, sizeof(int));

    assert(ll_size(list) == 1);

    ll_remove(list);

    assert(ll_size(list) == 0);
    assert(ll_is_empty(list) == true);

    ll_discard(list);
}

void test_linkedlist_get(void) {
    struct LinkedList *list = ll_create();

    int a = 10, b = 20, c = 30;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    int out;

    assert(ll_get(list, 0, &out) == true);
    assert(out == 10);

    assert(ll_get(list, 1, &out) == true);
    assert(out == 20);

    assert(ll_get(list, 2, &out) == true);
    assert(out == 30);

    ll_discard(list);
}

void test_linkedlist_get_invalid_index(void) {
    struct LinkedList *list = ll_create();

    int a = 1;
    ll_insert(list, &a, sizeof(int));

    int out;

    assert(ll_get(list, -1, &out) == false);
    assert(ll_get(list, 99, &out) == false);

    ll_discard(list);
}

void test_linkedlist_set(void) {
    struct LinkedList *list = ll_create();

    int a = 10;
    int replacement = 50;

    ll_insert(list, &a, sizeof(int));

    assert(ll_set(list, 0, &replacement) == true);

    int out;
    ll_get(list, 0, &out);

    assert(out == 50);

    ll_discard(list);
}

void test_linkedlist_set_invalid_index(void) {
    struct LinkedList *list = ll_create();

    int value = 100;

    assert(ll_set(list, 0, &value) == false);
    assert(ll_set(list, -1, &value) == false);

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

    assert(ll_find(list, &a, int_equals) == 0);
    assert(ll_find(list, &b, int_equals) == 1);
    assert(ll_find(list, &c, int_equals) == 2);

    int missing = 99;
    assert(ll_find(list, &missing, int_equals) == -1);

    ll_discard(list);
}

void test_linkedlist_contains(void) {
    struct LinkedList *list = ll_create();

    int a = 5;
    int b = 10;

    ll_insert(list, &a, sizeof(int));

    assert(ll_contains(list, &a, int_equals) == true);
    assert(ll_contains(list, &b, int_equals) == false);

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
    assert(out == 3);

    ll_get(list, 1, &out);
    assert(out == 2);

    ll_get(list, 2, &out);
    assert(out == 1);

    ll_discard(list);
}

void test_linkedlist_size_consistency(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;
    int out;

    ll_insert(list, &a, sizeof(int));
    assert(ll_size(list) == 1);

    ll_insert_tail(list, &b, sizeof(int));
    assert(ll_size(list) == 2);

    ll_insert_tail(list, &c, sizeof(int));
    assert(ll_size(list) == 3);

    ll_remove_at(list, 1);
    assert(ll_size(list) == 2);

    ll_remove(list);
    assert(ll_size(list) == 1);

    ll_remove_tail(list);
    assert(ll_size(list) == 0);

    assert(ll_is_empty(list));

    ll_discard(list);
}

void test_linkedlist_reuse_after_empty(void) {
    struct LinkedList *list = ll_create();

    int a = 10, b = 20;
    int out;

    ll_insert(list, &a, sizeof(int));
    ll_clear(list);

    assert(ll_is_empty(list));
    assert(ll_size(list) == 0);

    ll_insert_tail(list, &b, sizeof(int));

    assert(ll_get(list, 0, &out) == true);
    assert(out == 20);

    ll_discard(list);
}

void test_linkedlist_copy(void) {
    struct LinkedList *list = ll_create();

    int a = 1, b = 2, c = 3;

    ll_insert_tail(list, &a, sizeof(int));
    ll_insert_tail(list, &b, sizeof(int));
    ll_insert_tail(list, &c, sizeof(int));

    struct LinkedList *copy = ll_copy(list);

    assert(ll_size(copy) == ll_size(list));

    int out1, out2;

    ll_get(list, 0, &out1);
    ll_get(copy, 0, &out2);
    assert(out1 == out2);

    ll_get(list, 2, &out1);
    ll_get(copy, 2, &out2);
    assert(out1 == out2);

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
    assert(out.x == 1 && out.y == 2);

    ll_get(list, 1, &out);
    assert(out.x == 3 && out.y == 4);

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
    assert(strcmp(out, "hello") == 0);

    ll_get(list, 1, &out);
    assert(strcmp(out, "world") == 0);

    ll_discard(list);
}

void test_linkedlist_large_operations(void) {
    struct LinkedList *list = ll_create();

    for (int i = 0; i < 1000; i++) {
        ll_insert_tail(list, &i, sizeof(int));
    }

    assert(ll_size(list) == 1000);

    int out;

    for (int i = 0; i < 1000; i++) {
        ll_get(list, i, &out);
        assert(out == i);
    }

    ll_reverse(list);

    for (int i = 0; i < 1000; i++) {
        ll_get(list, i, &out);
        assert(out == 999 - i);
    }

    ll_discard(list);
}
