/**
 * test_ht.c
 * The test suite for the HashTable implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_table.h"

void print_int_key_value(void *key, void *value) {
    int *k = (int*)key;
    int *v = (int*)value;
    printf("[Key: %d: Value: %d]", *k, *v);
}

int main() {
    struct HashTable *hashtable = ht_create();
    printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", hashtable->capacity, hashtable->length, ht_load_factor(hashtable));
    printf("HashTable is empty: %d\n", ht_is_empty(hashtable));

    for (int i = 0; i < 8; i++) {
        int k = i;
        int v = i * 15;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
        printf("Current Capacity: %d\n", ht_capacity(hashtable));
    }
    ht_print(hashtable, print_int_key_value);

    // Should trigger resize
    for (int i = 0; i < 16; i++) {
        int rd_num = rand() % 100;
        int k = rd_num;
        int v = i * 3;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
        printf("Current Capacity: %d\n", ht_capacity(hashtable));
    }
    ht_print(hashtable, print_int_key_value);

    // printf("Removing key/value pairs: \n");

    // printf("Removing key=1: \n");
    // int rk1 = 1;
    // ht_remove(hashtable, &rk1, sizeof(int));
    // ht_print(hashtable, print_int_key_value);

    // printf("Removing key=2: \n");
    // int rk2 = 2;
    // ht_remove(hashtable, &rk2, sizeof(int));
    // ht_print(hashtable, print_int_key_value);

    // printf("Removing key=3: \n");
    // int rk3 = 3;
    // ht_remove(hashtable, &rk3, sizeof(int));
    // ht_print(hashtable, print_int_key_value);

    // printf("Removing key=4: \n");
    // int rk4 = 4;
    // ht_remove(hashtable, &rk4, sizeof(int));
    // ht_print(hashtable, print_int_key_value);

    // int key = 6;
    // int get_value;
    // if (ht_get(hashtable, &key, sizeof(int), &get_value)) {
    //     printf("Value associated with key=%d: %d\n", key, get_value);
    // } else {
    //     printf("Failed to retrieve the value!\n");
    // }

    // int keycontains = 10;
    // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
    //     printf("The hash table has key=%d\n", keycontains);
    // } else {
    //     printf("Could not find key=%d in the table\n", keycontains);
    // }

    // keycontains = 11;
    // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
    //     printf("The hash table has key=%d\n", keycontains);
    // } else {
    //     printf("Could not find key=%d in the table\n", keycontains);
    // }

    // keycontains = 900;
    // if (ht_contains(hashtable, &keycontains, sizeof(int))) {
    //     printf("The hash table has key=%d\n", keycontains);
    // } else {
    //     printf("Could not find key=%d in the table\n", keycontains);
    // }

    // ht_clear(hashtable);
    // printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", hashtable->capacity, hashtable->length, ht_load_factor(hashtable));
    // printf("HashTable is empty: %d\n", ht_is_empty(hashtable));

    ht_discard(hashtable);
    hashtable = NULL;

    return 0;
}