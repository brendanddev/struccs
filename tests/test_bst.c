#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binarysearch_tree/binarysearch_tree.h"


/// test_bt.c
/// The test suite for the BinaryTree implementation
/// Brendan Dileo, December 8 2025


void print_int(void *value) {
    printf("%d\n", * (int *) value);
}

int compare_int(void *a, void *b) {
    int num1 = * (int *)a;
    int num2 = * (int *)b;

    if (num1 == num2) {
        return 0;
    } else if (num1 > num2) {
        return 1;
    } else {
        return -1;
    }
}


int main() {

    // Create new binary search tree
    struct BinarySearchTree *binarytree = bst_create();
    printf("Root Node: %p, Length: %d\n", binarytree->root, binarytree->length);

    // Print length of bst and whether its empty
    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_isempty(binarytree));

    int nums[4] = { 100, 20, 300, 40 };

    // Insert integers into the tree
    for (int i = 0; i < 4; i++) {
        bst_insert(binarytree, &nums[i], sizeof(int), compare_int);
    }
    printf("Length: %d, Is empty? %d\n", bst_size(binarytree), bst_isempty(binarytree));

    // Print the contents of the tree
    bst_print(binarytree, print_int);


    return 0;
}