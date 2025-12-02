
/// hash_table.h
/// Header for the generic hash table implementation using seperate chaining to handle collisions
/// Brendan Dileo - November 24 2025


#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the buckets of the hash table
struct Node;


// Defines the HashTable struct type
typedef struct HashTable {
    struct Node **buckets;              // Pointer to the array of buckets where each element is a pointer to a node
    int capacity;                       // The number of buckets in the hash table
    int length;                         // The number of key/value pairs stored in the hash table
} HashTable;


struct HashTable* ht_create();
bool ht_insert(struct HashTable *hashtable, void *key, size_t ksize, void *value, size_t vsize);
bool ht_remove(struct HashTable *hashtable, void *key, size_t ksize);
bool ht_get(struct HashTable *hashtable, void *key, size_t ksize, void *out);
bool ht_is_empty(struct HashTable *hashtable);
int ht_size(struct HashTable *hashtable);
int ht_capacity(struct HashTable *hashtable);
float ht_load_factor(struct HashTable *hashtable);
void ht_print(struct HashTable *hashtable, void (* print_fn)(void*, void*));
void ht_discard(struct HashTable *hashtable);


#endif