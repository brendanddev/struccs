#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table/hash_table.h"

/// hash_table.c
/// A generic implementation of a hash table
/// Brendan Dileo - November 24 2025


// Defines the Node struct type representing a key-value pair stored in the table
typedef struct Node {
    void *key;                          // Pointer to memory where the key is stored
    size_t key_size;                    // The size of the key stored
    void *value;                        // Pointer to the memory where the value is stored
    size_t value_size;                  // The size of the value stored
    struct Node *next;                  // Pointer to the next node in the buckets chain
} Node;


// Prototypes
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize);
static void ht_discard_node(struct Node *node);
static void ht_discard_all_nodes(struct HashTable *hashtable);





// Private helper functions, linkage limited to this file


// Creates a new node to store a key/value pair in a hash table bucket
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize) {

    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Initialize sizes of the values stored in the node and the nodes next pointer
    node->key_size = ksize;
    node->value_size = vsize;
    node->next = NULL;

    // Allocate memory for the key storage and handle allocation failure
    node->key = malloc(ksize);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    // Allocate memory for the value storage and handle allocation failure
    node->value = malloc(vsize);
    if (node->value == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }

    // Copy the raw bytes from the memory pointed to by the input pointers
    // into the memory allocated for the key and value stored in this node
    memcpy(node->key, key, node->key_size);
    memcpy(node->value, value, node->value_size);
    return node;
}

// Frees the memory occupied by a single node
static void ht_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

// Frees the memory occupied by each node in the hash table
static void ht_discard_all_nodes(struct HashTable *hashtable) {
    
    // Loop through each bucket in the table
    for (int i = 0; i < hashtable->capacity; i++) {

        // For each bucket, traverse the nodes inside the bucket
        // to free each one
        struct Node *current = hashtable->buckets[i];
        while (current != NULL) {
            // Store pointer to next node in the bucket to prevent losing
            // link to the rest of the nodes
            struct Node *next = current->next;
            ht_discard_node(current);
            current = next;
        }
    }
}
