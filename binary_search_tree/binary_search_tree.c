#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_search_tree.h"

/// binary_search_tree.c
/// A generic implementation of a binary search tree
/// Brendan Dileo - December 8 2025


// Defines the node struct type
typedef struct Node {
    void *value;            // Pointer to the memory where the value is stored
    size_t value_size;      // The numver of bytes the value will occupy in the memory pointed to
    struct Node *left;      // Pointer to the left child
    struct Node *right;     // Pointer to the right child
} Node;


// Prototypes
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t vsize);
static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int level);
static struct Node* bst_create_node(void *value, size_t vsize);
static void bst_discard_node(struct Node *node);
static void bst_discard_all_nodes(struct BinarySearchTree binarytree);
static void bst_discard_all_nodes_rec(struct Node *root);


// Creates a new BinaryTree
struct BinarySearchTree* bst_create() {

    // Allocate memory for the binary tree itself and handle allocation failure
    struct BinarySearchTree *binarytree = malloc(sizeof(struct BinarySearchTree));
    if (binarytree == NULL) return NULL;

    // Set the initial pointer to the root node and length of the tree
    binarytree->root = NULL;
    binarytree->length = 0;

    return binarytree;
}

// Public interface for inserting a new node into the binary tree
void bst_insert(struct BinarySearchTree *binarytree, void* value, size_t vsize) { 
    // Call recursive helper to insert the node
    binarytree->root = bst_insert_rec(binarytree->root, value, vsize);
    binarytree->length++;
}

// Recursive helper function that performs the insertion
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t vsize) {

    // Base case
    // The root node is empty, so we can return the created node to insert here
    if (root == NULL) {
        return bst_create_node(value, vsize);

    // Compare raw memory of the two values, if the value being inserted is less than the root, traverse to the left
    } else if (memcmp(value, root->value, vsize) < 0) {
        // Recurse to the left of the tree to find insertion point
        root->left = bst_insert_rec(root->left, value, vsize);

    // Otherwise value being inserted is equal to or larger to the root, traverse to the right
    } else {
        // Recurse to the right of the tree to find the insertion point
        root->right = bst_insert_rec(root->right, value, vsize);
    }

    // Return original root to ensure tree remains linked
    return root;
}

// Public interface for printing the contents of the binary search tree
void bst_print(struct BinarySearchTree *binarytree, void (* print_fn)(void*)) {
    // Start recursion from root of the binary tree until the base case is hit
    bst_print_rec(binarytree->root, print_fn, 0);
}

// Recursive helper function that prints each node in the tree
static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int level) {

    // Base case
    // Root node is empty so we stop recursing here
    if (root == NULL) return;

    // Recurse all the way down to the right, print, then do the same for the left
    bst_print_rec(root->right, print_fn, level + 1);

    for (int i = 0; i < level; i++) printf("    ");
    print_fn(root->value);
    printf("\n");
    bst_print_rec(root->left, print_fn, level + 1);
}


// Checks if the binary tree is empty or not
bool bst_is_empty(struct BinarySearchTree *binarytree) {
    return binarytree->length == 0;
}

// Returns the number of nodes stored in the binary tree
int bst_size(struct BinarySearchTree *binarytree) {
    return binarytree->length;
}





// Private helper functions, linkage limited to this file


// Creates a new node to be stored in the binary tree
static struct Node* bst_create_node(void *value, size_t vsize) {

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
static void bst_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Frees the memory previously allocated by all nodes in the binary search tree
// by calling the recursive helper function
static void bst_discard_all_nodes(struct BinarySearchTree *binarytree) {
    bst_discard_all_nodes(binarytree->root);
}

// Recursive helper function that frees all nodes in the binary search tree
static void bst_discard_all_nodes_rec(struct Node *root) {

    // Base case
    // Root node is empty, stop recursing
    if (root == NULL) return;
    
    // Recurse down to the left to free all nodes on the left side of the tree first,
    // free the current node, then do the same for the right side of the tree
    bst_discard_all_nodes_rec(root->left);
    bst_discard_node(root);
    bst_discard_all_nodes_rec(root->right);
}
