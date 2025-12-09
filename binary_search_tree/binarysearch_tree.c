#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binarysearch_tree.h"


/// binarysearch_tree.c
/// A generic implementation of a binary search tree
/// Brendan Dileo - December 8 2025


// Defines the Node struct type
typedef struct Node {
    void *value;                // Pointer to the memory where the value is stored
    size_t value_size;          // Number of bytes the value will occupy in memory pointed to for the value
    struct Node *left;          // Pointer to the current nodes left child in the tree
    struct Node *right;         // Pointer to the current nodes right child in the tree
} Node;


// Prototypes
static struct Node* bst_create_node(void *value, size_t value_size);
static void bst_discard_node(struct Node *node);
static void bst_discard_all_nodes(struct BinarySearchTree *tree);


// Creates a new binary search tree
struct BinarySearchTree* bst_create() {
    struct BinarySearchTree *tree = malloc(sizeof(struct BinarySearchTree));
    return tree;

}




// Private helper functions, linkage limited to this file


// Creates a new node to be stored in the tree
static struct Node* bst_create_node(void *value, size_t value_size) {
    
    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Set size of value to be stored in the node and
    // initial left/right child pointers
    node->value_size = value_size;
    node->left = NULL;
    node->right = NULL;

    // Allocate memory for the value itself stored in the node, store pointer to the address, and
    // handle allocation failure
    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy the raw memory pointed to by the parameter into the memory pointed to by the nodes member
    memcpy(node->value, value, node->value_size);
    
    return node;
}