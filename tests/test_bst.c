/**
 * test_bt.c
 * The test suite for the BinarySearchTree implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "binarysearch_tree.h"

// Prototypes
void test_bst_init(void);
void test_bst_insert(void);
void test_bst_remove(void);
void test_bst_contains(void);
void test_bst_search(void);
void test_bst_clear(void);
void test_bst_size(void);
void test_bst_is_empty(void);
void test_bst_min(void);
void test_bst_max(void);
void test_bst_height(void);

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
    test_bst_init();
    test_bst_insert();
    test_bst_remove();
    test_bst_contains();
    test_bst_search();
    test_bst_clear();
    test_bst_size();
    test_bst_is_empty();
    test_bst_min();
    test_bst_max();
    test_bst_height();

    return 0;
}

void test_bst_init(void) {
    struct BinarySearchTree *bst = bst_create();

    assert(bst != NULL);
    assert(bst_size(bst) == 0);
    assert(bst_height(bst) == 0);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_insert(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    assert(bst_size(bst) == 4);
    assert(!bst_isempty(bst));
    assert(*(int *) bst_min(bst) == 20);
    assert(*(int *) bst_max(bst) == 300);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_remove(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    assert(*(int *) bst_min(bst) == 20);
    assert(*(int *) bst_max(bst) == 300);

    int num = 300;
    bst_remove(bst, &num, compare_int);

    assert(bst_size(bst) == 3);
    assert(*(int *) bst_min(bst) == 20);
    assert(*(int *) bst_max(bst) == 100);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_contains(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 50, 520, 30, 602 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    int num = 602;
    assert(bst_contains(bst, &num, compare_int) == true);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_search(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 50, 520, 30, 602 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    int num = 520;
    assert(bst_search(bst, &num, compare_int) != NULL);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_clear(void) {
    struct BinarySearchTree *bst = bst_create();

    int a = 1, b = 2;
    bst_insert(bst, &a, sizeof(int), compare_int);
    bst_insert(bst, &b, sizeof(int), compare_int);

    bst_clear(bst);
    assert(bst_size(bst) == 0);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_size(void) {
    struct BinarySearchTree *bst = bst_create();

    int a = 1;
    bst_insert(bst, &a, sizeof(int), compare_int);
    assert(bst_size(bst) == 1);

    int b = 1000;
    bst_insert(bst, &b, sizeof(int), compare_int);
    assert(bst_size(bst) == 2);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_is_empty(void) {
    struct BinarySearchTree *bst = bst_create();
    assert(bst_isempty(bst) == true);

    int a = 1;
    bst_insert(bst, &a, sizeof(int), compare_int);
    assert(bst_isempty(bst) == false);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_min(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    assert(*(int *) bst_min(bst) == 20);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_max(void) {
    struct BinarySearchTree *bst = bst_create();
    
    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    assert(*(int *) bst_max(bst) == 300);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_height(void) {
    struct BinarySearchTree *bst = bst_create();

    assert(bst_height(bst) == 0);
    
    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    assert(bst_height(bst) == 3);

    bst_discard(bst);
    bst = NULL;
}
