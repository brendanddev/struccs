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

    ht_clear(hashtable);    // clear again should be safe

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

// int main() {
//     struct HashTable *hashtable = ht_create();
//     printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", hashtable->capacity, hashtable->length, ht_load_factor(hashtable));
//     printf("HashTable is empty: %d\n", ht_is_empty(hashtable));

//     for (int i = 0; i < 8; i++) {
//         int k = i;
//         int v = i * 15;
//         ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
//         printf("Current Capacity: %d\n", ht_capacity(hashtable));
//     }
//     ht_print(hashtable, print_int_key_value);

//     // Should trigger resize
//     for (int i = 0; i < 16; i++) {
//         int rd_num = rand() % 100;
//         int k = rd_num;
//         int v = i * 3;
//         ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
//         printf("Current Capacity: %d\n", ht_capacity(hashtable));
//     }
//     ht_print(hashtable, print_int_key_value);

//     // printf("Removing key/value pairs: \n");

//     // printf("Removing key=1: \n");
//     // int rk1 = 1;
//     // ht_remove(hashtable, &rk1, sizeof(int));
//     // ht_print(hashtable, print_int_key_value);

//     // printf("Removing key=2: \n");
//     // int rk2 = 2;
//     // ht_remove(hashtable, &rk2, sizeof(int));
//     // ht_print(hashtable, print_int_key_value);

//     // printf("Removing key=3: \n");
//     // int rk3 = 3;
//     // ht_remove(hashtable, &rk3, sizeof(int));
//     // ht_print(hashtable, print_int_key_value);

//     // printf("Removing key=4: \n");
//     // int rk4 = 4;
//     // ht_remove(hashtable, &rk4, sizeof(int));
//     // ht_print(hashtable, print_int_key_value);

//     // int key = 6;
//     // int get_value;
//     // if (ht_get(hashtable, &key, sizeof(int), &get_value)) {
//     //     printf("Value associated with key=%d: %d\n", key, get_value);
//     // } else {
//     //     printf("Failed to retrieve the value!\n");
//     // }

//     // int keycontains = 10;
//     // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
//     //     printf("The hash table has key=%d\n", keycontains);
//     // } else {
//     //     printf("Could not find key=%d in the table\n", keycontains);
//     // }

//     // keycontains = 11;
//     // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
//     //     printf("The hash table has key=%d\n", keycontains);
//     // } else {
//     //     printf("Could not find key=%d in the table\n", keycontains);
//     // }

//     // keycontains = 900;
//     // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
//     //     printf("The hash table has key=%d\n", keycontains);
//     // } else {
//     //     printf("Could not find key=%d in the table\n", keycontains);
//     // }

//     // ht_clear(hashtable);
//     // printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", hashtable->capacity, hashtable->length, ht_load_factor(hashtable));
//     // printf("HashTable is empty: %d\n", ht_is_empty(hashtable));

//     ht_discard(hashtable);
//     hashtable = NULL;

//     return 0;
// }