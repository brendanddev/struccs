// hash_table.h
// Header for the generic hash table implementation using seperate chaining to handle collisions.
// Brendan Dileo - 2025

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node is opaque to callers, its layout lives in hash_table.c.
struct Node;

typedef struct HashTable {
    struct Node **buckets;         // array of `capacity` chain heads
    int capacity;                  // number of buckets
    int length;                    // number of key/value pairs stored
} HashTable;


// Allocates an empty table. Caller frees with ht_discard. NULL on failure.
struct HashTable* ht_create();
// Inserts a copy of the key (ksize bytes) and value (vsize bytes), or overwrites
// the value in place if the key is already present. Returns true.
bool ht_insert(struct HashTable *hashtable, void *key, size_t ksize, const void *value, size_t vsize);
// Removes the entry for key. Returns false if the key is absent.
bool ht_remove(struct HashTable *hashtable, void *key, size_t ksize);
// Copies the value for key into out. Returns false if the key is absent.
bool ht_get(struct HashTable *hashtable, void *key, size_t ksize, void *out);
// Returns true if key is present.
bool ht_contains(struct HashTable *hashtable, void *key, size_t ksize);
// Frees every entry and resets the table to its initial capacity.
void ht_clear(struct HashTable *hashtable);
// Returns true if no entries are stored.
bool ht_is_empty(struct HashTable *hashtable);
// Returns the number of key/value pairs stored.
int ht_size(struct HashTable *hashtable);
// Returns the number of buckets.
int ht_capacity(struct HashTable *hashtable);
// Returns length / capacity.
float ht_load_factor(struct HashTable *hashtable);
// Applies print_fn(key, value) to every entry, bucket by bucket.
void ht_print(struct HashTable *hashtable, void (* print_fn)(void*, void*));
// Frees every entry, the bucket array, and the table struct.
void ht_discard(struct HashTable *hashtable);

#endif
