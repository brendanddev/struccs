
/// binary_search_tree.h
/// Header for the generic binary search tree implementation with linked nodes
/// Brendan Dileo - December 8 2025


#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the buckets of the binary search tree
struct Node;


// Defines the BinarySearchTree struct type
typedef struct BinarySearchTree {
    struct Node *root;          // Pointer to the root node of the tree
    int length;                 // Number of nodes in the tree
} BinarySearchTree;


struct BinarySearchTree* bst_create();
void bst_insert(struct BinarySearchTree *binarytree, void* value, size_t vsize);
void bst_print(struct BinarySearchTree *binarytree, void (* print_fn)(void*));
void bst_clear(struct BinarySearchTree *binarytree);
bool bst_is_empty(struct BinarySearchTree *binarytree);
int bst_size(struct BinarySearchTree *binarytree);
void bst_discard(struct BinarySearchTree *binarytree);

void bst_remove();
bool bst_search();
bool bst_contains();


#endif