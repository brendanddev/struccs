#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../binary_tree/binary_tree.h"


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

    // Create a new binary tree
    struct BinaryTree *tree = bt_create(sizeof(int));
    printf(">>> Created BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));

    // Insert values into the tree
    printf(">>> Inserting 100 into the tree...\n");
    for (int i = 0; i < 7; i++) {
        int value = 100 + i;
        bt_insert(tree, &value);
    }
    printf(">>> Current BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));

    // Print the contents of the tree
    printf(">>> Printing the BinaryTree: \n");
    bt_print(tree, print_int);

    // Remove an element
    for (int i = 0; i < 3; i++) {
        printf(">>> Removing element at index=%d \n", i);
        bt_remove(tree, 0);
        bt_print(tree, print_int);
    }
    
    // Clear the binary tree
    bt_clear(tree);
    printf(">>> Cleared BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));

    // Free the binary tree
    printf(">>> Discarding the BinaryTree...\n");
    bt_discard(tree);
    tree = NULL;

    return 0;
}