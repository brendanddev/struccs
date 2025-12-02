#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../hash_table/hash_table.h"


/// test_ht.c
/// The test suite for the hash table implementation
/// Brendan Dileo, November 25 2025


void print_int_key_value(void *key, void *value) {
    int *k = (int*)key;
    int *v = (int*)value;
    printf("Key: %d, Value: %d", *k, *v);
}

int main() {

    // Create the hash table
    struct HashTable *hashtable = ht_create();
    printf("Capacity: %d, Length: %d\n", hashtable->capacity, hashtable->length);

    // Check if empty
    printf("HashTable is empty: %d\n", ht_is_empty(hashtable));

    for (int i = 0; i < 10; i++) {
        int key = i;
        int value = i * 10;
        ht_insert(hashtable, &key, sizeof(int), &value, sizeof(int));
    }

    ht_print(hashtable, print_int_key_value);

    




    return 0;
}