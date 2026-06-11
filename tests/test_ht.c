/**
 * test_ht.c
 * The test suite for the HashTable implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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
    test_hashtable_create();
    test_hashtable_clear();
    test_hashtable_is_empty();
    test_hashtable_remove();
    test_hashtable_get();
    test_hashtable_contains();
    test_hashtable_capacity();
    test_hashtable_load_factor();

    printf("All HashTable tests passed.\n");
    return 0;
}

void test_hashtable_create(void) {
    struct HashTable *hashtable = ht_create();

    assert(hashtable != NULL);
    assert (ht_size(hashtable) == 0);
    assert(ht_is_empty(hashtable) == true);

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

    assert(ht_size(hashtable) == 3);

    ht_clear(hashtable);

    assert(ht_size(hashtable) == 0);
    assert(ht_is_empty(hashtable) == true);

    // clear again should be safe
    ht_clear(hashtable);

    assert(ht_size(hashtable) == 0);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_is_empty(void) {
    struct HashTable *hashtable = ht_create();

    assert(ht_is_empty(hashtable) == true);

    int a = 10, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));
    assert(ht_is_empty(hashtable) == false);

    ht_remove(hashtable, &a, sizeof(int));

    assert(ht_is_empty(hashtable) == true);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_insert(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 250, c = 370;
    int one = 1, two = 2, three = 3;

    assert(ht_insert(hashtable, &a, sizeof(int), &one, sizeof(int)) == true);
    assert(ht_size(hashtable) == 1);

    assert(ht_insert(hashtable, &b, sizeof(int), &two, sizeof(int)) == true);
    assert(ht_size(hashtable) == 2);

    assert(ht_insert(hashtable, &c, sizeof(int), &three, sizeof(int)) == true);
    assert(ht_size(hashtable) == 3);

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

    assert(ht_size(hashtable) == 3);

    assert(ht_remove(hashtable, &a, sizeof(int)) == true);
    assert(ht_size(hashtable) == 2);

    assert(ht_remove(hashtable, &b, sizeof(int)) == true);
    assert(ht_size(hashtable) == 1);

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

    assert(ht_get(hashtable, &a, sizeof(int), &out));
    assert(out == 1);

    assert(ht_get(hashtable, &b, sizeof(int), &out));
    assert(out == 2);

    assert(ht_get(hashtable, &c, sizeof(int), &out));
    assert(out == 3);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_contains(void) {
    struct HashTable *hashtable = ht_create();

    int a = 100, b = 1;

    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));

    assert(ht_contains(hashtable, &a, sizeof(int)) == true);
    assert(ht_contains(hashtable, &b, sizeof(int)) == false);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_size(void) {
    struct HashTable *hashtable = ht_create();
    assert(ht_size(hashtable) == 0);

    int a = 100, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));
    
    assert(ht_size(hashtable) == 1);

    int foo = 250, bar = 50;
    ht_insert(hashtable, &foo, sizeof(int), &bar, sizeof(int));

    assert(ht_size(hashtable) == 2);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_capacity(void) {
    struct HashTable *hashtable = ht_create();
    assert(ht_capacity(hashtable) == 8);

    for (int i = 0; i < 8; i++) {
        int k = i, v = i * 2;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    assert(ht_capacity(hashtable) == 16);

    for (int i = 0; i < 12; i++) {
        int k = i * 3, v = i * 4;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    assert(ht_capacity(hashtable) == 32);

    ht_discard(hashtable);
    hashtable = NULL;
}

void test_hashtable_load_factor(void) {
    struct HashTable *hashtable = ht_create();
    assert(ht_load_factor(hashtable) == 0);

    for (int i = 0; i < 7; i++) {
        int k = i, v = i * 2;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    // Resize happens after the threshold is exceeded by an insertion, not before
    assert(ht_load_factor(hashtable) > 0.75);

    int a = 100, b = 1;
    ht_insert(hashtable, &a, sizeof(int), &b, sizeof(int));

    assert(ht_load_factor(hashtable) == 0.5);

    ht_discard(hashtable);
    hashtable = NULL;
}
