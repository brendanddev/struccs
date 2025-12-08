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







    return 0;

}