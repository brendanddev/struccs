

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
int bst_size(struct BinarySearchTree *tree);
bool bst_isempty(struct BinarySearchTree *tree);

void bst_print(struct BinarySearchTree *tree);
void bst_discard(struct BinarySearchTree *tree);


#endif