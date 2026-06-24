/**
 * test_ht.c
 * The test suite for the HashTable implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
#include "hash_table.h"

// Prototypes
void test_hashtable_create(void);
void test_hashtable_clear(void);
void test_hashtable_is_empty(void);
void test_hashtable_insert(void);
void test_hashtable_remove(void);
void test_hashtable_get(void);
void test_hashtable_contains(void);
void test_hashtable_size(void);
void test_hashtable_capacity(void);
void test_hashtable_load_factor(void);


int main() {
    TEST(test_hashtable_create);
    TEST(test_hashtable_clear);
    TEST(test_hashtable_is_empty);
    TEST(test_hashtable_remove);
    TEST(test_hashtable_get);
    TEST(test_hashtable_contains);
    TEST(test_hashtable_capacity);
    TEST(test_hashtable_load_factor);

    return 0;
}

void test_hashtable_create(void) {
    struct HashTable *hashtable = ht_create();

    ASSERT_NOT_NULL(hashtable);
    ASSERT_EQ(ht_size(hashtable), 0);
    ASSERT_TRUE(ht_is_empty(hashtable));

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_clear(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 250, c = 370;
    int one = 1, two = 2, three = 3;

    ht_insert(hashtable, &a, sizeof(int), &one, sizeof(int));
    ht_insert(hashtable, &b, sizeof(int), &two, sizeof(int));
    ht_insert(hashtable, &c, sizeof(int), &three, sizeof(int));

    ASSERT_EQ(ht_size(hashtable), 3);

    ht_clear(hashtable);

    ASSERT_EQ(ht_size(hashtable), 0);
    ASSERT_TRUE(ht_is_empty(hashtable));

    // clear again should be safe
    ht_clear(hashtable);

    ASSERT_EQ(ht_size(hashtable), 0);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_is_empty(void) {
    struct HashTable *hashtable = ht_create();

    ASSERT_TRUE(ht_is_empty(hashtable));

    int a = 10, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));
    ASSERT_FALSE(ht_is_empty(hashtable));

    ht_remove(hashtable, &a, sizeof(int));

    ASSERT_TRUE(ht_is_empty(hashtable));

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_insert(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 250, c = 370;
    int one = 1, two = 2, three = 3;

    ASSERT_TRUE(ht_insert(hashtable, &a, sizeof(int), &one, sizeof(int)));
    ASSERT_EQ(ht_size(hashtable), 1);

    ASSERT_TRUE(ht_insert(hashtable, &b, sizeof(int), &two, sizeof(int)));
    ASSERT_EQ(ht_size(hashtable), 2);

    ASSERT_TRUE(ht_insert(hashtable, &c, sizeof(int), &three, sizeof(int)));
    ASSERT_EQ(ht_size(hashtable), 3);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_remove(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 250, c = 370;
    int one = 1, two = 2, three = 3;

    ht_insert(hashtable, &a, sizeof(int), &one, sizeof(int));
    ht_insert(hashtable, &b, sizeof(int), &two, sizeof(int));
    ht_insert(hashtable, &c, sizeof(int), &three, sizeof(int));

    ASSERT_EQ(ht_size(hashtable), 3);

    ASSERT_TRUE(ht_remove(hashtable, &a, sizeof(int)));
    ASSERT_EQ(ht_size(hashtable), 2);

    ASSERT_TRUE(ht_remove(hashtable, &b, sizeof(int)));
    ASSERT_EQ(ht_size(hashtable), 1);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_get(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 250, c = 370;
    int one = 1, two = 2, three = 3;

    ht_insert(hashtable, &a, sizeof(int), &one, sizeof(int));
    ht_insert(hashtable, &b, sizeof(int), &two, sizeof(int));
    ht_insert(hashtable, &c, sizeof(int), &three, sizeof(int));

    int out;

    ASSERT_TRUE(ht_get(hashtable, &a, sizeof(int), &out));
    ASSERT_EQ(out, 1);

    ASSERT_TRUE(ht_get(hashtable, &b, sizeof(int), &out));
    ASSERT_EQ(out, 2);

    ASSERT_TRUE(ht_get(hashtable, &c, sizeof(int), &out));
    ASSERT_EQ(out, 3);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_contains(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 1;

    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));

    ASSERT_TRUE(ht_contains(hashtable, &a, sizeof(int)));
    ASSERT_FALSE(ht_contains(hashtable, &b, sizeof(int)));

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_size(void) {
    struct HashTable *hashtable = ht_create();
    ASSERT_EQ(ht_size(hashtable), 0);

    int a = 100, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));

    ASSERT_EQ(ht_size(hashtable), 1);

    int foo = 250, bar = 50;
    ht_insert(hashtable, &foo, sizeof(int), &bar, sizeof(int));

    ASSERT_EQ(ht_size(hashtable), 2);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_capacity(void) {
    struct HashTable *hashtable = ht_create();
    ASSERT_EQ(ht_capacity(hashtable), 8);

    for (int i = 0; i < 8; i++) {
        int k = i, v = i * 2;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    ASSERT_EQ(ht_capacity(hashtable), 16);

    for (int i = 0; i < 12; i++) {
        int k = i * 3, v = i * 4;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    ASSERT_EQ(ht_capacity(hashtable), 32);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_load_factor(void) {
    struct HashTable *hashtable = ht_create();
    ASSERT_TRUE(ht_load_factor(hashtable) == 0);

    for (int i = 0; i < 7; i++) {
        int k = i, v = i * 2;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    // Resize happens after the threshold is exceeded by an insertion, not before
    ASSERT_TRUE(ht_load_factor(hashtable) > 0.75);

    int a = 100, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));

    ASSERT_TRUE(ht_load_factor(hashtable) == 0.5);

    ht_discard(hashtable);
    hashtable = NULL;
}
