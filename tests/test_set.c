/**
 * test_set.c
 * The test suite for the Set implementation backed by a hash table.
 * Brendan Dileo - 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "set.h"

// Prototypes
void test_set_create(void);
void test_set_add(void);
void test_set_contains(void);
void test_set_remove(void);
void test_set_empty(void);
void test_set_size_consistency(void);
void test_set_bulk_behavior(void);

int main(void) {
    test_set_create();
    test_set_add();
    test_set_contains();
    test_set_remove();
    test_set_empty();
    test_set_size_consistency();
    test_set_bulk_behavior();

    printf("All Set tests passed.\n");
    return 0;
}


void test_set_create(void) {
    Set *set = set_create(sizeof(int));

    assert(set != NULL);
    assert(set_size(set) == 0);

    set_discard(set);
}

void test_set_add(void) {
    Set *set = set_create(sizeof(int));

    int a = 10;
    int b = 20;

    assert(set_add(set, &a) == true);
    assert(set_add(set, &a) == false);       // dupe should fail
    assert(set_add(set, &b) == true);

    assert(set_size(set) == 2);
    set_discard(set);
}

void test_set_contains(void) {
    Set *set = set_create(sizeof(int));
    int a = 42;
    set_add(set, &a);

    assert(set_contains(set, &a) == true);

    int b = 99;
    assert(set_contains(set, &b) == false);

    set_discard(set);
}

void test_set_remove(void) {

    Set *set = set_create(sizeof(int));
    int a = 5;

    assert(set_remove(set, &a) == false);   // remove from empty set

    set_add(set, &a);

    assert(set_remove(set, &a) == true);
    assert(set_contains(set, &a) == false);

    // removing again should fail
    assert(set_remove(set, &a) == false);

    set_discard(set);
}

void test_set_empty(void) {
    Set *set = set_create(sizeof(int));

    assert(set_size(set) == 0);
    assert(set_contains(set, &(int){123}) == false);
    assert(set_remove(set, &(int){123}) == false);

    set_discard(set);
}

void test_set_size_consistency(void) {
    Set *set = set_create(sizeof(int));

    int a = 1, b = 2, c = 3;

    set_add(set, &a);
    set_add(set, &b);
    set_add(set, &c);

    assert(set_size(set) == 3);

    set_remove(set, &b);

    assert(set_size(set) == 2);

    set_add(set, &b);

    assert(set_size(set) == 3);

    set_discard(set);
}

void test_set_bulk_behavior(void) {
    Set *set = set_create(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        set_add(set, &i);
    }

    assert(set_size(set) == 1000);

    for (int i = 0; i < 1000; i++) {
        assert(set_contains(set, &i) == true);
    }

    for (int i = 0; i < 500; i++) {
        set_remove(set, &i);
    }

    assert(set_size(set) == 500);

    for (int i = 0; i < 500; i++) {
        assert(set_contains(set, &i) == false);
    }

    set_discard(set);
}
