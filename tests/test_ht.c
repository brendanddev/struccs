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

    // Create a new hash table and print initial capacity, length and load factor
    struct HashTable *hashtable = ht_create();
    printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", hashtable->capacity, hashtable->length, ht_load_factor(hashtable));

    // Check if empty
    printf("HashTable is empty: %d\n", ht_is_empty(hashtable));
    

    // Free memory allocated by the hash table
    ht_discard(hashtable);
    hashtable = NULL;
    
    return 0;
}