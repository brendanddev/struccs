/**
 * test_bt.c
 * The test suite for the BinaryTree implementation.
 * Brendan Dileo - 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binary_tree.h"

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

    // Get the height of the tree - should be -1 right now since its empty
    printf(">>> Height of tree: %d (-1 if empty)\n", bt_height(tree));

    // Get number of leaves in the tree - should be 0 right now
    printf(">>> Number of leaves in the tree: %d\n", bt_leaves(tree));

    // Insert values into the tree
    printf(">>> Inserting 100 into the tree...\n");
    for (int i = 0; i < 15; i++) {
        int value = 100 + i;
        bt_insert(tree, &value);
    }
    printf(">>> Current BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));
    printf(">>> Height of tree: %d (-1 if empty)\n", bt_height(tree));
    printf(">>> Number of leaves in the tree: %d\n", bt_leaves(tree));


    // Print the contents of the tree
    printf(">>> Printing the BinaryTree: \n");
    bt_print(tree, print_int);

    // Remove an element
    for (int i = 0; i < 3; i++) {
        printf(">>> Removing element at index=%d \n", i);
        bt_remove(tree, 0);
        bt_print(tree, print_int);
    }
    
    // Get a value in the tree
    int val;
    if (bt_get(tree, 1, &val)) {
        printf(">>> [GET] Found value=%d at index=1\n", val);
    } else {
        printf(" >>> [GET] Could not access the value in the tree\n");
    }

    // Set a value in the tree
    int set = 10;
    if (bt_set(tree, 1, &set)) {
        printf(">>> Set value=%d at index=2\n", set);
    } else {
        printf(" >>> Could not set the value in the tree\n");
    }

    printf(">>> Printing the BinaryTree: \n");
    bt_print(tree, print_int);

    // Check if the tree contains a value
    int value = 102;
    if (bt_contains(tree, &value, compare_int)) {
        printf(">>> [CONTAINS] Found value=%d\n", value);
    } else {
        printf(">>> [CONTAINS] Could not access the value in the tree\n");
    }

    value = 1000;
    if (bt_contains(tree, &value, compare_int)) {
        printf(">>> [CONTAINS] Found value=%d\n", value);
    } else {
        printf(" >>> [CONTAINS] Could not access the value in the tree\n");
    }
    
    // Find the index of a value in the tree
    value = 103;
    int idx = bt_find(tree, &value, compare_int);
    if (idx != -1) {
        printf(">>> [FIND] Found value=%d at index=%d\n", value, idx);
    } else {
        printf(" >>> [FIND] Could not find the value in the tree\n");
    }

    value = 3000;
    idx = bt_find(tree, &value, compare_int);
    if (idx != -1) {
        printf(">>> [FIND] Found value=%d at index=%d\n", value, idx);
    } else {
        printf(" >>> [FIND] Could not find the value in the tree\n");
    }

    printf("Height of tree: %d (-1 if empty)\n", bt_height(tree));

    // Clear the binary tree
    bt_clear(tree);
    printf(">>> Cleared BinaryTree - Length: %d, Capacity: %d Is Empty: %d\n", bt_size(tree), bt_capacity(tree), bt_isempty(tree));

    // Free the binary tree
    printf(">>> Discarding the BinaryTree...\n");
    bt_discard(tree);
    tree = NULL;

    return 0;
}