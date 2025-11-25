
/// hash_table.h
/// Header for the generic hash table implementation using seperate chaining to handle collisions
/// Brendan Dileo - November 24 2025


#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines the Node struct type representing a key-value pair stored in the table
typedef struct Node {
    void *key;                          // Pointer to memory where the key is stored
    size_t key_size;                    // The size of the key stored
    void *value;                        // Pointer to the memory where the value is stored
    size_t value_size;                  // The size of the value stored
    struct Node *next;                  // Pointer to the next node in the buckets chain
} Node;


// Defines the HashTable struct type
typedef struct HashTable {
    struct Node **buckets;              // Pointer to the array of buckets where each element is a pointer to a node
    int capacity;                       // The capacity of the table
    int length;                         // The current length of the table
    float load_factor;
} HashTable;



#endif
