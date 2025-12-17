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
    int value = 100;
    for (int i = 0; i < 3; i++) bt_insert(tree, &value);
    printf(">>> Current BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));

    bt_print(tree, print_int);

    // Free the binary tree
    printf(">>> Discarding the BinaryTree...\n");
    bt_discard(tree);
    tree = NULL;

    return 0;
}