#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binarysearch_tree/binarysearch_tree.h"


/// test_bt.c
/// The test suite for the BinaryTree implementation
/// Brendan Dileo, December 8 2025


void print_int(void *value) {
    printf("%d", * (int *) value);
}


int main() {

    struct BinarySearchTree *binarytree = bst_create();
    printf("Root Node: %p, Length: %d\n", binarytree->root, binarytree->length);

    // Print length of bst and whether its empty
    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_isempty(binarytree));
    
    return 0;
}