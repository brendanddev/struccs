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


    // Insert new key/value pairs into the hash table
    for (int i = 0; i < 12; i++) {
        int k = i;
        int v = i * 15;
        ht_insert(hashtable, &k, sizeof(int), &v, sizeof(int));
    }

    // Print contents of the hash table
    ht_print(hashtable, print_int_key_value);

    // Remove key value pairs from the hash table
    printf("Removing key/value pairs: \n");

    printf("Removing key=1: \n");
    int rk1 = 1;
    ht_remove(hashtable, &rk1, sizeof(int));
    ht_print(hashtable, print_int_key_value);

    printf("Removing key=2: \n");
    int rk2 = 2;
    ht_remove(hashtable, &rk2, sizeof(int));
    ht_print(hashtable, print_int_key_value);

    printf("Removing key=3: \n");
    int rk3 = 3;
    ht_remove(hashtable, &rk3, sizeof(int));
    ht_print(hashtable, print_int_key_value);

    printf("Removing key=4: \n");
    int rk4 = 4;
    ht_remove(hashtable, &rk4, sizeof(int));
    ht_print(hashtable, print_int_key_value);

    // Free memory allocated by the hash table
    ht_discard(hashtable);
    hashtable = NULL;

    return 0;
}