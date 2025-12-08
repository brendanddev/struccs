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

// Inserts a new node into the binary tree
void bt_insert(struct BinaryTree *binarytree, void* value, size_t vsize) { 


    
}



// Checks if the binary tree is empty or not
bool bt_is_empty(struct BinaryTree *binarytree) {
    return binarytree->length == 0;
}

// Returns the number of nodes stored in the binary tree
int bt_size(struct BinaryTree *binarytree) {
    return binarytree->length;
}





// Private helper functions, linkage limited to this file


// Creates a new node to be stored in the binary tree
static struct Node* bt_create_node(void *value, size_t vsize) {

    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Set initial left and right child pointers for the node
    // and the size of the value to be stored in the node
    node->left = NULL;
    node->right = NULL;
    node->value_size = vsize;

    // Allocate memory for the value to be stored in the nodes and
    // handle allocation failure
    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy the raw memory pointed to by the pointer parameter into the memory pointed to by 
    // the nodes value
    memcpy(node->value, value, node->value_size);

    return node;
}

// Frees the memory previously allocated by a node
static void bt_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Frees the memory previously allocated by all nodes in the binary tree
static void bt_discard_all_nodes(struct BinaryTree binarytree) {
    return;
}