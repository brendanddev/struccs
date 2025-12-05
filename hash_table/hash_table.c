#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"

/// hash_table.c
/// A generic implementation of a hash table
/// Brendan Dileo - November 24 2025


// Defines the maximum load factor allowed before the hash table should resize
#define LOAD_THRESHOLD 0.75


// Defines the Node struct type
typedef struct Node {
    void *key;              // Pointer to the memory where the key data is stored
    size_t key_size;        // The number of bytes the key will occupy in the memory pointed to for the key
    void *value;            // Pointer to the memory where the value data is stored
    size_t value_size;      // The number of bytes that the value will occupy in the memory pointed to for the value
    struct Node *next;      // Pointer to the next node in a bucket
} Node;


// Prototypes
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize);
static int ht_hash(void *key, size_t key_size, int capacity);
static void ht_resize();
static void ht_discard_node(struct Node *node);
static void ht_discard_all_nodes(struct HashTable *hashtable);


// Creates a new hash table
struct HashTable* ht_create() { 

    // Allocate memory for the hash table itself and handle allocation failure
    struct HashTable *hashtable = malloc(sizeof(struct HashTable));
    if (hashtable == NULL) return NULL;

    // Set initial capacity and length of the hash table
    hashtable->capacity = 8;
    hashtable->length = 0;

    // Allocate memory for the hash tables internal array of buckets
    // using calloc to initialize each bucket to NULL to know whether they are empty,
    // and handle allocation failure
    hashtable->buckets = calloc(hashtable->capacity, sizeof(struct Node*));
    if (hashtable->buckets == NULL) {
        free(hashtable);
        return NULL;
    }

    return hashtable;
}



// Checks whether the hash table is empty or not
bool ht_is_empty(struct HashTable *hashtable) {
    return hashtable->length == 0;
}

// Returns the number of key/value pairs (nodes) in the hash table
int ht_size(struct HashTable *hashtable) {
    return hashtable->length;
}

// Returns the number of buckets in the hash table
int ht_capacity(struct HashTable *hashtable) {
    return hashtable->capacity;
}

// Returns the load factor for the hash table, showing how full the hash table is
float ht_load_factor(struct HashTable *hashtable) {
    return hashtable->length / hashtable->capacity;
}


// Private helper functions, linkage limited to this file


// Creates a new node
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize) {

    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }

    // Set size of key and value being stored in the node 
    // and initial pointer to the next node
    node->key_size = ksize;
    node->value_size = vsize;
    node->next = NULL;

    // Allocate memory for the key and handle allocation failure
    node->key = malloc(node->key_size);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    // Allocate memory for the value and handle allocation failure,
    // freeing the memory allocated for the key and node itself
    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }

    // Copy the raw memory pointed to by the pointer arguments into the memory pointed to by
    // the nodes members
    memcpy(node->key, key, node->key_size);
    memcpy(node->value, value, node->value_size);
    return node;
}

// Hashes a given key and returns its bucket index
static int ht_hash(void *key, size_t key_size, int capacity) {

    // Cast so each induvidual byte in the keys memory can be accessed 
    unsigned char *bytes = (unsigned char *) key;
    int hash_value = 0;

    // Loop through each byte for key_size bytes to add each byte value to the rolling sum
    for (int i = 0; i < key_size; i++) {
        // Calculate memory address of the i-th byte from the start of the key in memory
        // and dereference the address to get the actual byte value at that position
        hash_value += *(bytes + i);
    }

    // Modulo to ensure hash value fits within the buckets array bounds
    return hash_value % capacity;
}

// Frees the memory previously allocated by a node
static void ht_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

// Frees the memory previously allocated by all nodes in the hash table
static void ht_discard_all_nodes(struct HashTable *hashtable) {

    // Loop through each bucket in the hash table
    for (int i = 0; i < hashtable->capacity; i++) {

        // Start from head node in each bucket and
        // loop through each node in the bucket to free each
        struct Node *current = hashtable->buckets[i];
        while (current != NULL) {

            // Store pointer to the next node in the bucket to prevent
            // losing the link to the rest of the nodes when freeing the current
            struct Node *next = current->next;
            ht_discard_node(current);
            current = next;
        }
    }
}