/**
 * hash_table.c
 * A generic implementation of a hash table
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"

// Grow the bucket array once the load factor climbs past this.
#define LOAD_THRESHOLD 0.75

// One entry in a bucket's chain. The node owns heap copies of both the key
// (key_size bytes) and the value (value_size bytes).
typedef struct Node {
    void *key;
    size_t key_size;
    void *value;
    size_t value_size;
    struct Node *next;
} Node;

// Prototypes
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize);
static int ht_hash(void *key, size_t key_size, int capacity);
static void ht_resize(struct HashTable *hashtable);
static void ht_discard_node(struct Node *node);
static void ht_discard_all_nodes(struct HashTable *hashtable);

struct HashTable* ht_create() {
    struct HashTable *hashtable = malloc(sizeof(struct HashTable));
    if (hashtable == NULL) return NULL;

    hashtable->capacity = 8;
    hashtable->length = 0;

    // calloc so every empty bucket reads back as a NULL chain head.
    hashtable->buckets = calloc(hashtable->capacity, sizeof(struct Node*));
    if (hashtable->buckets == NULL) {
        free(hashtable);
        return NULL;
    }

    return hashtable;
}

bool ht_insert(struct HashTable *hashtable, void *key, size_t ksize, void *value, size_t vsize) {
    if (ht_load_factor(hashtable) > LOAD_THRESHOLD) {
        printf("Resizing internal array...\n");
        ht_resize(hashtable);
    }

    int hash = ht_hash(key, ksize, hashtable->capacity);

    // Chain head for this bucket; NULL when the bucket is empty.
    struct Node *head = hashtable->buckets[hash];

    if (head == NULL) {
        struct Node *newnode = ht_create_node(key, ksize, value, vsize);
        hashtable->buckets[hash] = newnode;
        hashtable->length++;
        return true;

    } else {
        // Walk the chain: overwrite in place if the key is already here,
        // otherwise fall through and append a new node.
        struct Node *previous = NULL;

        while (head != NULL) {
            if (memcmp(head->key, key, head->key_size) == 0) {
                memcpy(head->value, value, vsize);
                return true;
            }

            previous = head;
            head = head->next;
        }

        struct Node *newnode = ht_create_node(key, ksize, value ,vsize);
        previous->next = newnode;
        hashtable->length++;
        return true;
    }
    return false;
}

bool ht_remove(struct HashTable *hashtable, void *key, size_t ksize) {
    if (ht_is_empty(hashtable)) return false;

    int hash = ht_hash(key, ksize, hashtable->capacity);

    // Track previous so a non-head node can be unlinked.
    struct Node *current = hashtable->buckets[hash];
    struct Node *previous = NULL;

    while (current != NULL) {
        if (memcmp(current->key, key, ksize) == 0) {

            if (current == hashtable->buckets[hash]) {
                // Removing the chain head: repoint the bucket at node 2.
                struct Node *next = current->next;
                ht_discard_node(current);
                hashtable->buckets[hash] = next;

            } else {
                // Removing a middle/tail node: bridge previous over it.
                struct Node *next = current->next;
                ht_discard_node(current);
                previous->next = next;
            }

            hashtable->length--;
            return true;
        }

        previous = current;
        current = current->next;
    }
    return false;
}

bool ht_get(struct HashTable *hashtable, void *key, size_t ksize, void *out) {
    if (ht_is_empty(hashtable)) return false;

    int hash = ht_hash(key, ksize, hashtable->capacity);

    struct Node *current = hashtable->buckets[hash];
    while (current != NULL) {
        if (memcmp(current->key, key, ksize) == 0) {
            memcpy(out, current->value, current->value_size);
            return true;
        }
        current = current->next;
    }
    return false;
}

bool ht_contains(struct HashTable *hashtable, void *key, size_t ksize) {
    if (ht_is_empty(hashtable)) return false;

    int hash = ht_hash(key, ksize, hashtable->capacity);
    struct Node *current = hashtable->buckets[hash];
    while (current != NULL) {
        if (memcmp(current->key, key, current->key_size) == 0) return true;
        current = current->next;
    }
    return false;
}

void ht_clear(struct HashTable *hashtable) {
    if (ht_is_empty(hashtable)) return;

    ht_discard_all_nodes(hashtable);
    free(hashtable->buckets);

    // Back to the initial state.
    hashtable->length = 0;
    hashtable->capacity = 8;

    hashtable->buckets = calloc(hashtable->capacity, sizeof(struct Node*));
    if (hashtable->buckets == NULL) return;
}

void ht_print(struct HashTable *hashtable, void (* print_fn)(void*, void*)) {
    for (int i = 0; i < hashtable->capacity; i++) {
        printf("Bucket %d -> ", i);

        struct Node *current = hashtable->buckets[i];

        if (current == NULL) {
            printf("NULL\n");
        } else {
            while (current != NULL) {
                print_fn(current->key, current->value);
                if (current->next != NULL) {
                    printf(" -> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
}

void ht_discard(struct HashTable *hashtable) {
    if (hashtable != NULL) {
        ht_discard_all_nodes(hashtable);
        free(hashtable->buckets);
        free(hashtable);
    }
}

bool ht_is_empty(struct HashTable *hashtable) {
    return hashtable->length == 0;
}

int ht_size(struct HashTable *hashtable) {
    return hashtable->length;
}

int ht_capacity(struct HashTable *hashtable) {
    return hashtable->capacity;
}

float ht_load_factor(struct HashTable *hashtable) {
    return (float) hashtable->length / hashtable->capacity;
}


// Private helper functions - linkage limited to this file


// Deep-copies key (ksize bytes) and value (vsize bytes); the node owns both.
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }

    node->key_size = ksize;
    node->value_size = vsize;
    node->next = NULL;

    node->key = malloc(node->key_size);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }

    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node->key);
        free(node);
        return NULL;
    }

    memcpy(node->key, key, node->key_size);
    memcpy(node->value, value, node->value_size);
    return node;
}

// Sum of the key's bytes modulo capacity: cheap, but order-insensitive and
// clusters badly for similar keys.
static int ht_hash(void *key, size_t key_size, int capacity) {
    unsigned char *bytes = (unsigned char *) key;
    int hash_value = 0;

    for (int i = 0; i < key_size; i++) {
        hash_value += *(bytes + i);
    }

    return hash_value % capacity;
}

// Doubles the bucket count and rehashes every node into the new array.
static void ht_resize(struct HashTable *hashtable) {
    // Hold onto the old array/capacity while we rehash out of it.
    struct Node **bucketscopy = hashtable->buckets;
    int old_capacity = hashtable->capacity;

    hashtable->capacity = hashtable->capacity * 2;

    hashtable->buckets = calloc(hashtable->capacity, sizeof(struct Node*));

    for (int i = 0; i < old_capacity; i++) {
        struct Node *current = bucketscopy[i];
        while (current != NULL) {
            int hash = ht_hash(current->key, current->key_size, hashtable->capacity);

            // Save next before we overwrite current->next while relinking.
            struct Node *next = current->next;
            struct Node *currhead = hashtable->buckets[hash];

            // Prepend the node to its new bucket's chain.
            current->next = currhead;
            hashtable->buckets[hash] = current;

            current = next;
        }
    }

    // The old array holds no nodes now, only stale head pointers.
    free(bucketscopy);
    bucketscopy = NULL;
}

static void ht_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

static void ht_discard_all_nodes(struct HashTable *hashtable) {
    for (int i = 0; i < hashtable->capacity; i++) {
        struct Node *current = hashtable->buckets[i];
        while (current != NULL) {
            // Grab next before freeing current.
            struct Node *next = current->next;
            ht_discard_node(current);
            current = next;
        }
    }
}
