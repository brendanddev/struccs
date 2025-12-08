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
static struct Node* bt_create_node(void *value, size_t vsize);
static void bt_discard_node(struct Node *node);
static void bt_discard_all_nodes(struct BinaryTree binarytree);


// Creates a new BinaryTree
struct BinaryTree* bt_create() {

    // Allocate memory for the binary tree itself and handle allocation failure
    struct BinaryTree *binarytree = malloc(sizeof(struct BinaryTree));
    if (binarytree == NULL) return NULL;

    // Set the initial pointer to the root node and length of the tree
    binarytree->root = NULL;
    binarytree->length = 0;

    return binarytree;
}
