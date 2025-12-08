#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binary_tree/binary_tree.h"


/// test_bt.c
/// The test suite for the BinaryTree implementation
/// Brendan Dileo, December 8 2025


int main() {

    struct BinaryTree *binarytree = bt_create();
    printf("Root Node: %p, Length: %d\n", binarytree->root, binarytree->length);







    return 0;

}