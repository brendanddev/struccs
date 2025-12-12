

/// binarysearch_tree.h
/// Header for the generic binary search tree implementation with linked nodes
/// Brendan Dileo - December 8 2025


#ifndef BINARYSEARCH_TREE_H
#define BINARYSEARCH_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the binary search tree
struct Node;


// Defines the BinarySearchTree struct type
typedef struct BinarySearchTree {
    struct Node *root;              // Pointer to the root of the tree
    int length;                     // Number of nodes in the tree
} BinarySearchTree;


struct BinarySearchTree* bst_create();
void bst_insert(struct BinarySearchTree *tree, void *value, size_t value_size, int (*compare)(void*, void*));
void bst_remove(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
bool bst_contains(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
struct Node* bst_search(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*));
int bst_height(struct BinarySearchTree *tree);
void bst_print(struct BinarySearchTree *tree, void (* print_fn)(void*));
void bst_inorder(struct BinarySearchTree *tree, void (* print_fn)(void*));
void bst_postorder(struct BinarySearchTree *tree, void (* print_fn)(void*));

int bst_size(struct BinarySearchTree *tree);
bool bst_isempty(struct BinarySearchTree *tree);
void bst_clear(struct BinarySearchTree *tree);
void bst_discard(struct BinarySearchTree *tree);

void bst_preorder(struct BinarySearchTree *tree);


#endif