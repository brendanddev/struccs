#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"

/// hash_table.c
/// A generic implementation of a hash table
/// Brendan Dileo - November 24 2025


// Defines the Node struct type
typedef struct Node {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
    struct Node *next;
} Node;


// Prototypes
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize);
static void ht_discard_node(struct Node *node);
static void ht_discard_all_nodes(struct HashTable *hashtable);
