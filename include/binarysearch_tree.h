/**
 * binarysearch_tree.h
 * Header for the generic binary search tree implementation with linked nodes.
 * Brendan Dileo - 2025
 */

#ifndef BINARYSEARCH_TREE_H
#define BINARYSEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node is opaque to callers, its layout lives in binarysearch_tree.c.
struct Node;

typedef struct BinarySearchTree {
    struct Node *root;
    int length;
} BinarySearchTree;


// Allocates an empty tree. Caller frees with bst_discard. Returns NULL on failure.
struct BinarySearchTree* bst_create();
// Inserts a copy of value_size bytes from value, ordered by compare. Duplicates
// go to the right subtree. length is incremented unconditionally.
void bst_insert(struct BinarySearchTree *tree, void *value, size_t value_size, int (*compare)(void*, void*));
// Removes the first node equal to value (compare returns 0). No-op if absent.
void bst_remove(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
// Returns true if a node equal to value exists.
bool bst_contains(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
// Returns the node equal to value, or NULL if absent. The node is owned by the
// tree - do not free it or hold it past a remove/discard.
struct Node* bst_search(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
// Returns a borrowed pointer to the smallest stored value, or NULL if empty.
void* bst_min(struct BinarySearchTree *tree);
// Returns a borrowed pointer to the largest stored value, or NULL if empty.
void* bst_max(struct BinarySearchTree *tree);
// Returns height in nodes: empty tree = 0, root-only tree = 1.
int bst_height(struct BinarySearchTree *tree);
// Prints the tree rotated onto its side (ascending top-to-bottom).
void bst_print(struct BinarySearchTree *tree, void (* print_fn)(void*));
// Applies print_fn to every value in in-order (sorted) order.
void bst_inorder(struct BinarySearchTree *tree, void (* print_fn)(void*));
// Applies print_fn to every value in post-order (children before parent).
void bst_postorder(struct BinarySearchTree *tree, void (* print_fn)(void*));
// Applies print_fn to every value in pre-order (parent before children).
void bst_preorder(struct BinarySearchTree *tree, void (* print_fn)(void*));
// Returns the number of nodes in the tree.
int bst_size(struct BinarySearchTree *tree);
// Returns true if the tree has no nodes.
bool bst_isempty(struct BinarySearchTree *tree);
// Frees every node but keeps the tree struct for reuse.
void bst_clear(struct BinarySearchTree *tree);
// Frees every node and the tree struct.
void bst_discard(struct BinarySearchTree *tree);

#endif
