/**
 * test_ga.c
 * The test suite for the GenericArray implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "generic_array.h"

// Prototypes
void test_ga_init(void);
void test_ga_add(void);
void test_ga_get(void);
void test_ga_get_invalid_index(void);
void test_ga_set(void);
void test_ga_set_invalid_index(void);
void test_ga_find(void);
void test_ga_find_missing(void);
void test_ga_remove_last(void);
void test_ga_remove_at(void);
void test_ga_remove_at_invalid(void);
void test_ga_contains(void);
void test_ga_contains_missing(void);
void test_ga_clear(void);
void test_ga_large_operations(void);

bool compare_int(void *a, void *b) {
    return (*(int *)a == *(int *)b);
}

int main(void) {
    test_ga_init();
    test_ga_add();
    test_ga_get();
    test_ga_get_invalid_index();
    test_ga_set();
    test_ga_set_invalid_index();
    test_ga_find();
    test_ga_find_missing();
    test_ga_remove_last();
    test_ga_remove_at();
    test_ga_remove_at_invalid();
    test_ga_contains();
    test_ga_contains_missing();
    test_ga_clear();
    test_ga_large_operations();

    printf("All GenericArray tests passed.\n");
    return 0;
}

void test_ga_init(void) {
    GenericArray *ga = ga_init(sizeof(int));

    assert(ga != NULL);
    assert(ga_size(ga) == 0);
    assert(ga_capacity(ga) > 0);

    ga_discard(ga);
}

void test_ga_add(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10, b = 20;

    ga_add(ga, 0, &a);
    assert(ga_size(ga) == 1);

    ga_add(ga, 1, &b);
    assert(ga_size(ga) == 2);

    ga_discard(ga);
}

void test_ga_get(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 42;
    ga_add(ga, 0, &a);

    int *out = malloc(sizeof(int));

    assert(ga_get(ga, 0, out) == true);
    assert(*out == 42);

    free(out);
    ga_discard(ga);
}

void test_ga_get_invalid_index(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    ga_add(ga, 0, &a);

    int *out = malloc(sizeof(int));

    assert(ga_get(ga, 999, out) == false);

    free(out);
    ga_discard(ga);
}

void test_ga_set(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    int replacement = 99;

    ga_add(ga, 0, &a);

    assert(ga_set(ga, 0, &replacement) == true);

    int *out = malloc(sizeof(int));
    ga_get(ga, 0, out);

    assert(*out == 99);

    free(out);
    ga_discard(ga);
}

void test_ga_set_invalid_index(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;

    assert(ga_set(ga, 0, &a) == false);
    assert(ga_set(ga, 999, &a) == false);

    ga_discard(ga);
}

void test_ga_find(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10, b = 20, c = 30;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);
    ga_add(ga, 2, &c);

    assert(ga_find(ga, &a, compare_int) == 0);
    assert(ga_find(ga, &b, compare_int) == 1);
    assert(ga_find(ga, &c, compare_int) == 2);

    ga_discard(ga);
}

void test_ga_find_missing(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    ga_add(ga, 0, &a);

    int missing = 999;

    assert(ga_find(ga, &missing, compare_int) == -1);

    ga_discard(ga);
}

void test_ga_remove_last(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);

    assert(ga_remove_last(ga) == true);
    assert(ga_size(ga) == 1);

    ga_discard(ga);
}

void test_ga_remove_at(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2, c = 3;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);
    ga_add(ga, 2, &c);

    assert(ga_remove_at(ga, 1) == true);
    assert(ga_size(ga) == 2);

    ga_discard(ga);
}

void test_ga_remove_at_invalid(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1;
    ga_add(ga, 0, &a);

    assert(ga_remove_at(ga, 999) == false);

    ga_discard(ga);
}

void test_ga_contains(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;

    ga_add(ga, 0, &a);

    assert(ga_contains(ga, compare_int, &a) == true);

    ga_discard(ga);
}

void test_ga_contains_missing(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;
    int missing = 999;

    ga_add(ga, 0, &a);

    assert(ga_contains(ga, compare_int, &missing) == false);

    ga_discard(ga);
}

void test_ga_clear(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);

    ga_clear(ga);

    assert(ga_size(ga) == 0);

    ga_discard(ga);
}

void test_ga_large_operations(void) {
    GenericArray *ga = ga_init(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        ga_add(ga, i, &i);
    }

    assert(ga_size(ga) == 1000);

    for (int i = 0; i < 1000; i++) {
        int *out = malloc(sizeof(int));
        ga_get(ga, i, out);
        assert(*out == i);
        free(out);
    }

    ga_discard(ga);
}