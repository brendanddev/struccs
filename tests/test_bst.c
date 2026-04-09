/**
 * test_bt.c
 * The test suite for the BinarySearchTree implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "binarysearch_tree.h"

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
    struct BinarySearchTree *binarytree = bst_create();
    printf("Root Node: %p, Length: %d\n", binarytree->root, binarytree->length);
    printf("Length: %d\n", bst_size(binarytree));
    printf("Is empty? %d\n", bst_isempty(binarytree));

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(binarytree, &nums[i], sizeof(int), compare_int);
    }
    printf("Length: %d, Is empty? %d\n", bst_size(binarytree), bst_isempty(binarytree));

    bst_print(binarytree, print_int);
    bst_inorder(binarytree, print_int);
    printf("\n");
    bst_postorder(binarytree, print_int);
    printf("\n");
    bst_preorder(binarytree, print_int);

    int val = 100;
    if (bst_contains(binarytree, &val, compare_int)) {
        printf("[CONTAINS] Found the value %d in the tree\n", val);
    } else {
        printf("[CONTAINS] Did not find the value %d in the tree\n", val);
    }

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

    // Should not find this value
    val = 1000;
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
    
    printf("The minumum value in the tree: %d\n", * (int *) bst_min(binarytree));
    printf("The maximum value in the tree: %d\n", * (int *) bst_max(binarytree));
    printf("The height of the tree: %d\n", bst_height(binarytree));

    int num = 100;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    num = 20;
    bst_remove(binarytree, &num, compare_int);
    bst_print(binarytree, print_int);
    printf("\n");

    // Not in the tree
    num = 1220;
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

    bst_clear(binarytree);
    printf("Length: %d, Is empty? %d\n", bst_size(binarytree), bst_isempty(binarytree));

    bst_discard(binarytree);
    binarytree = NULL;
    return 0;
}