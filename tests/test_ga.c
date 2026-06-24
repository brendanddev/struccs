/**
 * test_ga.c
 * The test suite for the GenericArray implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
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
    TEST(test_ga_init);
    TEST(test_ga_add);
    TEST(test_ga_get);
    TEST(test_ga_get_invalid_index);
    TEST(test_ga_set);
    TEST(test_ga_set_invalid_index);
    TEST(test_ga_find);
    TEST(test_ga_find_missing);
    TEST(test_ga_remove_last);
    TEST(test_ga_remove_at);
    TEST(test_ga_remove_at_invalid);
    TEST(test_ga_contains);
    TEST(test_ga_contains_missing);
    TEST(test_ga_clear);
    TEST(test_ga_large_operations);

    return 0;
}

void test_ga_init(void) {
    GenericArray *ga = ga_init(sizeof(int));

    ASSERT_NOT_NULL(ga);
    ASSERT_EQ(ga_size(ga), 0);
    ASSERT_TRUE(ga_capacity(ga) > 0);

    ga_discard(ga);
}

void test_ga_add(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10, b = 20;

    ga_add(ga, 0, &a);
    ASSERT_EQ(ga_size(ga), 1);

    ga_add(ga, 1, &b);
    ASSERT_EQ(ga_size(ga), 2);

    ga_discard(ga);
}

void test_ga_get(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 42;
    ga_add(ga, 0, &a);

    int *out = malloc(sizeof(int));

    ASSERT_TRUE(ga_get(ga, 0, out));
    ASSERT_EQ(*out, 42);

    free(out);
    ga_discard(ga);
}

void test_ga_get_invalid_index(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    ga_add(ga, 0, &a);

    int *out = malloc(sizeof(int));

    ASSERT_FALSE(ga_get(ga, 999, out));

    free(out);
    ga_discard(ga);
}

void test_ga_set(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    int replacement = 99;

    ga_add(ga, 0, &a);

    ASSERT_TRUE(ga_set(ga, 0, &replacement));

    int *out = malloc(sizeof(int));
    ga_get(ga, 0, out);

    ASSERT_EQ(*out, 99);

    free(out);
    ga_discard(ga);
}

void test_ga_set_invalid_index(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;

    ASSERT_FALSE(ga_set(ga, 0, &a));
    ASSERT_FALSE(ga_set(ga, 999, &a));

    ga_discard(ga);
}

void test_ga_find(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10, b = 20, c = 30;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);
    ga_add(ga, 2, &c);

    ASSERT_EQ(ga_find(ga, &a, compare_int), 0);
    ASSERT_EQ(ga_find(ga, &b, compare_int), 1);
    ASSERT_EQ(ga_find(ga, &c, compare_int), 2);

    ga_discard(ga);
}

void test_ga_find_missing(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 10;
    ga_add(ga, 0, &a);

    int missing = 999;

    ASSERT_EQ(ga_find(ga, &missing, compare_int), -1);

    ga_discard(ga);
}

void test_ga_remove_last(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);

    ASSERT_TRUE(ga_remove_last(ga));
    ASSERT_EQ(ga_size(ga), 1);

    ga_discard(ga);
}

void test_ga_remove_at(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2, c = 3;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);
    ga_add(ga, 2, &c);

    ASSERT_TRUE(ga_remove_at(ga, 1));
    ASSERT_EQ(ga_size(ga), 2);

    ga_discard(ga);
}

void test_ga_remove_at_invalid(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1;
    ga_add(ga, 0, &a);

    ASSERT_FALSE(ga_remove_at(ga, 999));

    ga_discard(ga);
}

void test_ga_contains(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;

    ga_add(ga, 0, &a);

    ASSERT_TRUE(ga_contains(ga, compare_int, &a));

    ga_discard(ga);
}

void test_ga_contains_missing(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 5;
    int missing = 999;

    ga_add(ga, 0, &a);

    ASSERT_FALSE(ga_contains(ga, compare_int, &missing));

    ga_discard(ga);
}

void test_ga_clear(void) {
    GenericArray *ga = ga_init(sizeof(int));

    int a = 1, b = 2;

    ga_add(ga, 0, &a);
    ga_add(ga, 1, &b);

    ga_clear(ga);

    ASSERT_EQ(ga_size(ga), 0);

    ga_discard(ga);
}

void test_ga_large_operations(void) {
    GenericArray *ga = ga_init(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        ga_add(ga, i, &i);
    }

    ASSERT_EQ(ga_size(ga), 1000);

    for (int i = 0; i < 1000; i++) {
        int *out = malloc(sizeof(int));
        ga_get(ga, i, out);
        ASSERT_EQ(*out, i);
        free(out);
    }

    ga_discard(ga);
}
