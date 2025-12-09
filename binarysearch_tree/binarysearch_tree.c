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
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*));
static void bst_print_rec(struct Node *root, void (* print_fn)(void*));    
static struct Node* bst_create_node(void *value, size_t value_size);
static void bst_discard_node(struct Node *node);
static void bst_discard_all_nodes(struct BinarySearchTree *tree);


// Creates a new binary search tree
struct BinarySearchTree* bst_create() {

    // Allocate memory for the tree itself and handle allocation failure
    struct BinarySearchTree *tree = malloc(sizeof(struct BinarySearchTree));
    if (tree == NULL) return NULL;

    // Set the initial root pointer and length of the tree
    tree->root = NULL;
    tree->length = 0;
    
    return tree;
}

// Public interface for inserting a new value into the binary search tree
void bst_insert(struct BinarySearchTree *tree, void *value, size_t value_size, int (*compare)(void*, void*)) {
    tree->root = bst_insert_rec(tree->root, value, value_size, compare);
    tree->length++;
}

// Recursive helper function for inserting a value into the binary search tree
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*)) {
    
    // Base case - if the root node is empty, return it to insert
    if (root == NULL) {
        printf("Inserting ROOT\n");
        return bst_create_node(value, value_size);

    // Compare memory blocks pointed to by the value being inserted and the current node value
    // to see if we need to recurse left in the tree
    } else if (compare(value, root->value) < 0) {
        printf("Inserting %d, current root: %d, going LEFT\n", *(int*)value, *(int*)root->value);

        // Recurse to the left of the tree to insert the value, then assign the returned
        // subtree back to the root nodes left child to maintain the connection, and return
        // root so the caller can update their pointer to this subtree
        root->left = bst_insert_rec(root->left, value, value_size, compare);
        return root;
    // Otherwise recurse right in the tree
    } else {
        printf("Inserting %d, current root: %d, going RIGHT\n", *(int*)value, *(int*)root->value);
        root->right = bst_insert_rec(root->right, value, value_size, compare);
        return root;
    }
}

// Public interface for printing the contents of the binary search tree
void bst_print(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    bst_print_rec(tree->root, print_fn);
}

// Recursive helper function for printing the contents of the binary search tree in order traversal
static void bst_print_rec(struct Node *root, void (* print_fn)(void*)) {

    // Base case - if we hit a empty node, weve hit the end of the branch
    if (root == NULL) return;

    // Recurse down the left side first, once base case is hit, print current value,
    // go to root, go to right child, print if no children, go back to root, print
    bst_print_rec(root->left, print_fn);
    print_fn(root->value);  // wrong?
    bst_print_rec(root->right, print_fn);
}



// Returns the number of nodes in the binary search tree
int bst_size(struct BinarySearchTree *tree) {
    return tree->length;
}

// Checks whether the binary search tree is empty
bool bst_isempty(struct BinarySearchTree *tree) {
    return tree->length == 0;
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

// Frees the memory previously allocated by a node
static void bst_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

