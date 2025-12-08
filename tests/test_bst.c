#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binary_search_tree/binary_search_tree.h"


/// test_bt.c
/// The test suite for the BinaryTree implementation
/// Brendan Dileo, December 8 2025


int main() {

    struct BinarySearchTree *binarytree = bst_create();
    printf("Root Node: %p, Length: %d\n", binarytree->root, binarytree->length);

    // Print length of bst and whether its empty
    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_is_empty(binarytree));

    // Insert node into the tree
    int val = 100;
    bst_insert(binarytree, &val, sizeof(int));

    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_is_empty(binarytree));








    return 0;

}