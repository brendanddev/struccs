#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"

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
static int ht_hash(void *key, size_t ksize, int capacity);
static struct Node* ht_create_node(void *key, size_t ksize, void *value, size_t vsize);
static void ht_discard_node(struct Node *node);
static void ht_discard_all_nodes(struct HashTable *hashtable);


// Creates a new hash table
struct HashTable* ht_create() {

    // Allocate memory for the hash table itself and handle allocation failure
    struct HashTable *hashtable = malloc(sizeof(struct HashTable));
    if (hashtable == NULL) return NULL;

    // Initialize capacity, length, and load factore of the table
    hashtable->capacity = 8;
    hashtable->length = 0;
    hashtable->load_factor = 0;

    // Allocate memory for the buckets, which is an array of pointers to the nodes 
    // No memory is allocated yet for the nodes themselves, just the slots to hold pointers to them
    // where each slot corresponds to a bucket
    // Use calloc() instead of malloc() to initialize all allocated memory to 0
    hashtable->buckets = calloc(hashtable->capacity, sizeof(struct Node *));

    // Handle allocation failure
    if (hashtable->buckets == NULL) {
        free(hashtable);
        return NULL;
    }

    return hashtable;
}

// Inserts a new or updates an existing key/value pair in the hash table
bool ht_insert(struct HashTable *hashtable, void *key, size_t ksize, void *value, size_t vsize) {

    // Compute hash code to determine which bucket the key/value pair belongs to
    int hash = ht_hash(key, ksize, hashtable->capacity);

    // Check if specific bucket being inserted into is empty
    if (hashtable->buckets[hash] == NULL) {
        // Create the node to insert into this bucket as the head
        // and handle allocation failure
        struct Node *newnode = ht_create_node(key, ksize, value, vsize);
        if (newnode == NULL) return false;

        // Set the new node as the head of this bucket
        hashtable->buckets[hash] = newnode;
        hashtable->length++;
        return true;
    }

    // If bucket being inserted to is not empty, need to traverse the linked nodes starting from the 
    // head node of the bucket to try and find the key and update if found
    for (struct Node *current = hashtable->buckets[hash]; current != NULL; current = current->next) {
        
        // Check if we found key to update using `memcmp` to compare the raw bytes in memory at two pointers
        // to determine if they hold identical content
        if (memcmp(current->key, key, current->key_size) == 0) {
            // Update the stored value by copying the new value bytes into the memory pointed to by node->value
            memcpy(current->value, value, vsize);
            return true;
        }
    }

    // If we reach here, key was not found inside of the bucket and we need to append
    // a new node to this bucket
    struct Node *newnode = ht_create_node(key, ksize, value, vsize);

    // Traverse the nodes inside of the bucket starting from the head node
    struct Node *current = hashtable->buckets[hash];
    while (current->next != NULL) {
        current = current->next;
    }

    // At this point `current->next == NULL` so we can append the bucket
    current->next = newnode;
    hashtable->length++;
    return true;
}

// Removes a key/value pair from the table if the key is found
bool ht_remove(struct HashTable *hashtable, void *key, size_t ksize) {
    if (ht_is_empty(hashtable)) return false;

    // Hash the key to find the bucket index
    int hash = ht_hash(key, ksize, hashtable->capacity);

    // Track both previous and current nodes while traversing
    struct Node *previous = NULL;
    struct Node *current = hashtable->buckets[hash];

    while (current != NULL) {

        // Check if we found the key by comparing raw bytes in memory
        if (memcmp(current->key, key, ksize) == 0) {

            // Check if the current node is the head based on the previous node
            if (previous == NULL) {
                hashtable->buckets[hash] = current->next;

            // Not head of the list
            } else {
                previous->next = current->next;
            }

            // Discard the memory allocated by the key/value pair and node itself
            ht_discard_node(current);
            hashtable->length--;
            return true;
        }

        // Advance the pointers if key not found
        previous = current;
        current = current->next;
    }
    return false;
}

// Retrieves the value for a given key in the hash table
bool ht_get(struct HashTable *hashtable, void *key, size_t ksize, void *out) {
    if (ht_is_empty(hashtable)) return false;

    // Hash the key to find the bucket
    int hash = ht_hash(key, ksize, hashtable->capacity);

    // Start from the head of the linked nodes inside the bucket
    // and traverse to search for key
    struct Node *current = hashtable->buckets[hash];
    while (current != NULL) {

        // Check if we found the key by comparing the raw bytes stored in memory
        if (memcmp(current->key, key, ksize) == 0) {
            // If the key is found, copy raw bytes stored in memory into the 
            // memory pointed to by the out pointer
            memcpy(out, current->value, current->value_size);
            return true;
        }
        current = current->next;
    }
    return false;
}

// Checks if the hash table is empty, meaning it contains no key/value pairs
bool ht_is_empty(struct HashTable *hashtable) {
    return hashtable->length == 0;
}

// Prints the contents of each bucket in the hash table, printing the key/value pair for each node in a bucket
void ht_print(struct HashTable *hashtable, void (*print_fn)(void*, void*)) {
    printf("HashTable - Capacity: %d, Length: %d\n", hashtable->capacity, hashtable->length);

    // Traverse each possible bucket in the table
    for (int i = 0; i < hashtable->capacity; i++) {
        
        // The head of the current bucket
        struct Node *current = hashtable->buckets[i];
        printf("Bucket [%d]:", i);

        // Check if bucket is empty for debugging
        if (!current) {
            printf(" -> NULL (empty)\n");
            continue;
        }

        // Traverse the linked nodes inside the bucket starting from the head node
        while (current != NULL) {
            printf(" -> ");
            print_fn(current->key, current->value);
            current = current->next;
        }
        printf("\n");
    }
}


// Private helper functions, linkage limited to this file


// Turns a keys raw bytes into a hash value that corresponds to a bucket in the hash table following the djb2-style hash
static int ht_hash(void *key, size_t ksize, int capacity) {
    // Initialize the hash with a seed value
    unsigned long raw_hash = 5381;

    // Loop over each byte of the key
    for (int i = 0; i < ksize; i++) {
        // For each byte, access the value of the i-th byte of the key
        // and mix the byte into the running hash to get a better distribution
        unsigned char byte = ((unsigned char *) key)[i];
        raw_hash = raw_hash * 33 + byte;
    }

    // Map the hash to a bucket in the table based on the raw hash and capacity of the table
    int bucket_index = raw_hash % capacity;
    return bucket_index;
}

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
