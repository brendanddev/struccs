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

} Node;


// Prototypes
// ...


// Creates a new binary search tree
struct BinarySearchTree* bst_create() {
    struct BinarySearchTree *tree = malloc(sizeof(struct BinarySearchTree));
    return tree;

}




// Private helper functions, linkage limited to this file