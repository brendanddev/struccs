#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../hash_table/hash_table.h"


/// test_ht.c
/// The test suite for the hash table implementation
/// Brendan Dileo, November 25 2025


int main() {

    struct HashTable *hashtable = ht_create();
    printf("Capacity: %d, Length: %d\n", hashtable->capacity, hashtable->length);



    return 0;
}