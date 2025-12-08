
/// binary_tree.h
/// Header for the generic binary tree implementation 
/// Brendan Dileo - December 8 2025


#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the buckets of the binary tree
struct Node;


// Defines the BinaryTree struct type
typedef struct BinaryTree {
    struct Node *root;          // Pointer to the root node of the tree
    int length;                 // Number of nodes in the tree
} BinaryTree;


struct BinaryTree* bt_create();
void bt_insert(struct BinaryTree *binarytree, void* value, size_t vsize);
bool bt_is_empty(struct BinaryTree *binarytree);
int bt_size(struct BinaryTree *binarytree);

void bt_remove();
bool bt_search();
bool bt_contains();
void bt_clear();
bool bt_is_empty();
int bt_size();
void bt_print();
void bt_discard();


#endif