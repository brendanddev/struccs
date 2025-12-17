#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"


/// binary_tree.c
/// A generic implementation of a complete binary tree
/// Brendan Dileo - December 17 2025


// Prototypes
static int parent_index(int index);
static int left_child_index(int index);
static int right_child_index(int index);


// Creates a new binary tree storing elements of the provided size
struct BinaryTree* bt_create(size_t element_size) {

    // Allocate memory for the binary tree struct itself and handle allocation failure
    struct BinaryTree *tree = malloc(sizeof(struct BinaryTree));
    if (tree == NULL) return NULL;

    // Set initial capacity, length and size of elements stored in the tree
    tree->capacity = 12;
    tree->length = 0;
    tree->element_size = element_size;

    // Allocate memory for the underlying array that will hold the tree elements
    // and handle allocation failure
    tree->elements = malloc(tree->capacity * tree->element_size);
    if (tree->elements == NULL) {
        free(tree);
        return NULL;
    }

    return tree;
}

// Returns the current size (length) of the binary tree
int bt_size(struct BinaryTree *tree) {
    return tree->length;
}

// Returns the current capacity of the tree's underlying array
int bt_capacity(struct BinaryTree *tree) {
    return tree->capacity;
}

// Checks if the binary tree is empty
bool bt_isempty(struct BinaryTree *tree) {
    return tree->length == 0;
}

// Frees the memory previously allocated for the binary tree
void bt_discard(struct BinaryTree *tree) {
    if (tree != NULL) {
        free(tree->elements);
        free(tree);
    }
}


// Private helper functions, linkage limited to this file


// Returns the array index of the parent of the element at index `index` in the tree
static int parent_index(int index) {
    return (index - 1) / 2;
}

// Returns the array index of the left child of the element at the provided index in the tree
static int left_child_index(int index) {
    return 2 * index + 1;
}

// Returns the array index of the right child of the element at the provided index in the tree
static int right_child_index(int index) {
    return 2 * index + 2;
}