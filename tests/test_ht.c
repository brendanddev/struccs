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
    printf("[Key: %d: Value: %d]", *k, *v);
}

int main() {

    // Create a new hash table and print initial capacity and length
    struct HashTable *hashtable = ht_create();
    printf("Capacity: %d, Length: %d\n", hashtable->capacity, hashtable->length);

    // Check if empty
    printf("HashTable is empty: %d\n", ht_is_empty(hashtable));
    
    return 0;
}