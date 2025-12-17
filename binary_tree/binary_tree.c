#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"


/// binary_tree.c
/// A generic implementation of a complete binary tree
/// Brendan Dileo - December 17 2025


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