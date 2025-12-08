#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"

/// binary_tree.c
/// A generic implementation of a binary tree
/// Brendan Dileo - December 8 2025


// Defines the node struct type
typedef struct Node {
    void *value;            // Pointer to the memory where the value is stored
    size_t value_size;      // The numver of bytes the valye will occupy in the memory pointed to
    struct Node *left;      // Pointer to the left child
    struct Node *right;     // Pointer to the right child
} Node;


// Prototypes
static struct Node* bt_create_node();