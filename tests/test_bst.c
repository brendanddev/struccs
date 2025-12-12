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

    // Print the contents of the tree with visual depth
    bst_print(binarytree, print_int);

    // Print the contents of the tree in order
    bst_inorder(binarytree, print_int);

    // Print contents of the tree post order
    bst_postorder(binarytree, print_int);

    // Check if the tree contains a value
    int val = 100;
    if (bst_contains(binarytree, &val, compare_int)) {
        printf("[CONTAINS] Found the value %d in the tree\n", val);
    } else {
        printf("[CONTAINS] Did not find the value %d in the tree\n", val);
    }

    // Test searching for a value in the tree
    if (bst_search(binarytree, &val, compare_int) != NULL) {
        printf("[SEARCH] Found the value %d in the tree\n", val);
    } else {
        printf("[SEARCH] Did not find the value %d in the tree\n", val);
    }

    val = 20;
    if (bst_contains(binarytree, &val, compare_int)) {
        printf("Found the value %d in the tree\n", val);
    } else {
        printf("Did not find the value %d in the tree\n", val);
    }

    if (bst_search(binarytree, &val, compare_int) != NULL) {
        printf("[SEARCH] Found the value %d in the tree\n", val);
    } else {
        printf("[SEARCH] Did not find the value %d in the tree\n", val);
    }

    val = 1000;     // Should not find this value
    if (bst_contains(binarytree, &val, compare_int)) {
        printf("Found the value %d in the tree\n", val);
    } else {
        printf("Did not find the value %d in the tree\n", val);
    }

    if (bst_search(binarytree, &val, compare_int) != NULL) {
        printf("[SEARCH] Found the value %d in the tree\n", val);
    } else {
        printf("[SEARCH] Did not find the value %d in the tree\n", val);
    }

    // Get height of the tree
    printf("The height of the tree: %d\n", bst_height(binarytree));

    // Remove value from the binary tree
    int num = 100;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    num = 20;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    num = 1220;     // Not in the tree
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    num = 300;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    num = 40;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    printf("The height of the tree: %d\n", bst_height(binarytree));

    // Clear contents of the binary tree
    bst_clear(binarytree);
    printf("Length: %d, Is empty? %d\n", bst_size(binarytree), bst_isempty(binarytree));

    // Free the binary search tree
    bst_discard(binarytree);
    binarytree = NULL;

    return 0;
}