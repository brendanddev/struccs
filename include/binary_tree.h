// binary_tree.h
// Header for the generic complete binary tree implementation, backed by an array.
// Brendan Dileo - 2025

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Elements are stored in a flat array, parent/child links are derived from
// array indices (left = 2i+1, right = 2i+2), so the tree is always complete.
typedef struct BinaryTree {
    int length;             // number of elements in use
    int capacity;           // slots allocated in the backing array
    void *elements;
    size_t element_size;
} BinaryTree;


// Allocates an empty tree for elements of element_size bytes. Caller frees with
// bt_discard. Returns NULL on allocation failure.
struct BinaryTree* bt_create(size_t element_size);
// Appends value at the next free slot, growing the backing array if full.
// Copies element_size bytes from value.
void bt_insert(struct BinaryTree *tree, void *value);
// Removes the element at index by overwriting it with the last element, so
// neither insertion order nor tree shape below index is preserved.
void bt_remove(struct BinaryTree *tree, int index);
// Copies the element at index into out. Returns false if index is out of range.
bool bt_get(struct BinaryTree *tree, int index, void *out);
// Overwrites the element at index with value. Returns false if index is out of range.
bool bt_set(struct BinaryTree *tree, int index, void *value);
// Returns true if any element compares equal (comparator returns 0) to value. O(n).
bool bt_contains(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
// Returns the index of the first element equal to value, or -1 if absent. O(n).
int bt_find(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
// Returns height in edges: root-only tree = 0, empty tree = -1.
int bt_height(struct BinaryTree *tree);
// Returns the number of leaf nodes (nodes with no left child).
int bt_leaves(struct BinaryTree *tree);
// Returns true if the tree holds no elements.
bool bt_isempty(struct BinaryTree *tree);
// Returns the number of elements in the tree.
int bt_size(struct BinaryTree *tree);
// Returns the current capacity of the backing array.
int bt_capacity(struct BinaryTree *tree);
// Resets length to 0; the backing array is kept and reused by later inserts.
void bt_clear(struct BinaryTree *tree);
// Prints the tree rotated 90 degrees (root at the left) using print_fn per element.
void bt_print(struct BinaryTree *tree, void (*print_fn)(void*));
// Frees the backing array and the tree struct.
void bt_discard(struct BinaryTree *tree);

#endif
