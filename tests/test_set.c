/**
 * test_set.c
 * The test suite for the Set implementation backed by a hash table.
 * Brendan Dileo - 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
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
    TEST(test_set_create);
    TEST(test_set_add);
    TEST(test_set_contains);
    TEST(test_set_remove);
    TEST(test_set_empty);
    TEST(test_set_size_consistency);
    TEST(test_set_bulk_behavior);

    return 0;
}


void test_set_create(void) {
    Set *set = set_create(sizeof(int));

    ASSERT_NOT_NULL(set);
    ASSERT_EQ(set_size(set), 0);

    set_discard(set);
}

void test_set_add(void) {
    Set *set = set_create(sizeof(int));

    int a = 10;
    int b = 20;

    ASSERT_TRUE(set_add(set, &a));
    ASSERT_FALSE(set_add(set, &a));       // dupe should fail
    ASSERT_TRUE(set_add(set, &b));

    ASSERT_EQ(set_size(set), 2);
    set_discard(set);
}

void test_set_contains(void) {
    Set *set = set_create(sizeof(int));
    int a = 42;
    set_add(set, &a);

    ASSERT_TRUE(set_contains(set, &a));

    int b = 99;
    ASSERT_FALSE(set_contains(set, &b));

    set_discard(set);
}

void test_set_remove(void) {

    Set *set = set_create(sizeof(int));
    int a = 5;

    ASSERT_FALSE(set_remove(set, &a));   // remove from empty set

    set_add(set, &a);

    ASSERT_TRUE(set_remove(set, &a));
    ASSERT_FALSE(set_contains(set, &a));

    // removing again should fail
    ASSERT_FALSE(set_remove(set, &a));

    set_discard(set);
}

void test_set_empty(void) {
    Set *set = set_create(sizeof(int));

    ASSERT_EQ(set_size(set), 0);
    ASSERT_FALSE(set_contains(set, &(int){123}));
    ASSERT_FALSE(set_remove(set, &(int){123}));

    set_discard(set);
}

void test_set_size_consistency(void) {
    Set *set = set_create(sizeof(int));

    int a = 1, b = 2, c = 3;

    set_add(set, &a);
    set_add(set, &b);
    set_add(set, &c);

    ASSERT_EQ(set_size(set), 3);

    set_remove(set, &b);

    ASSERT_EQ(set_size(set), 2);

    set_add(set, &b);

    ASSERT_EQ(set_size(set), 3);

    set_discard(set);
}

void test_set_bulk_behavior(void) {
    Set *set = set_create(sizeof(int));

    for (int i = 0; i < 1000; i++) {
        set_add(set, &i);
    }

    ASSERT_EQ(set_size(set), 1000);

    for (int i = 0; i < 1000; i++) {
        ASSERT_TRUE(set_contains(set, &i));
    }

    for (int i = 0; i < 500; i++) {
        set_remove(set, &i);
    }

    ASSERT_EQ(set_size(set), 500);

    for (int i = 0; i < 500; i++) {
        ASSERT_FALSE(set_contains(set, &i));
    }

    set_discard(set);
}
