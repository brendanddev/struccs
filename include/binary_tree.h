/**
 * binary_tree.h
 * Header for the generic complete binary tree implementation, backed by an array.
 * Brendan Dileo - 2025
 */

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Defines the BinaryTree struct type.
 * Elements are stored in a flat array using index-based parent/child relationships.
 */
typedef struct BinaryTree {
    int length;             // Number of elements in the tree
    int capacity;           // Capacity of the trees underlying array
    void *elements;         // Pointer to the memory where the elements are stored
    size_t element_size;    // Size of the elements stored in the tree
} BinaryTree;


struct BinaryTree* bt_create(size_t element_size);
void bt_insert(struct BinaryTree *tree, void *value);
void bt_remove(struct BinaryTree *tree, int index);
bool bt_get(struct BinaryTree *tree, int index, void *out);
bool bt_set(struct BinaryTree *tree, int index, void *value);
bool bt_contains(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
int bt_find(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
int bt_height(struct BinaryTree *tree);
int bt_leaves(struct BinaryTree *tree);
bool bt_isempty(struct BinaryTree *tree);
int bt_size(struct BinaryTree *tree);
int bt_capacity(struct BinaryTree *tree);
void bt_clear(struct BinaryTree *tree);
void bt_print(struct BinaryTree *tree, void (*print_fn)(void*));
void bt_discard(struct BinaryTree *tree);

#endif