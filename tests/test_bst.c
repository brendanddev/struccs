#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binary_search_tree/binary_search_tree.h"


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
    printf("Is empty? %d\n", bst_is_empty(binarytree));

    // Insert node into the tree
    int val = 10;
    bst_insert(binarytree, &val, sizeof(int));
    
    val = 5;
    bst_insert(binarytree, &val, sizeof(int));

    val = 1;
    bst_insert(binarytree, &val, sizeof(int));

    val = 34;
    bst_insert(binarytree, &val, sizeof(int));

    val = 3;
    bst_insert(binarytree, &val, sizeof(int));

    val = 45;
    bst_insert(binarytree, &val, sizeof(int));

    val = 17;
    bst_insert(binarytree, &val, sizeof(int));



    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_is_empty(binarytree));


    // Print the contents of the bst
    printf("==========\n");
    bst_print(binarytree, print_int);







    return 0;

}