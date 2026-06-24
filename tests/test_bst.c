/**
 * test_bt.c
 * The test suite for the BinarySearchTree implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
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
    TEST(test_bst_init);
    TEST(test_bst_insert);
    TEST(test_bst_remove);
    TEST(test_bst_contains);
    TEST(test_bst_search);
    TEST(test_bst_clear);
    TEST(test_bst_size);
    TEST(test_bst_is_empty);
    TEST(test_bst_min);
    TEST(test_bst_max);
    TEST(test_bst_height);

    return 0;
}

void test_bst_init(void) {
    struct BinarySearchTree *bst = bst_create();

    ASSERT_NOT_NULL(bst);
    ASSERT_EQ(bst_size(bst), 0);
    ASSERT_EQ(bst_height(bst), 0);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_insert(void) {
    struct BinarySearchTree *bst = bst_create();

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    ASSERT_EQ(bst_size(bst), 4);
    ASSERT_FALSE(bst_isempty(bst));
    ASSERT_EQ(*(int *) bst_min(bst), 20);
    ASSERT_EQ(*(int *) bst_max(bst), 300);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_remove(void) {
    struct BinarySearchTree *bst = bst_create();

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    ASSERT_EQ(*(int *) bst_min(bst), 20);
    ASSERT_EQ(*(int *) bst_max(bst), 300);

    int num = 300;
    bst_remove(bst, &num, compare_int);

    ASSERT_EQ(bst_size(bst), 3);
    ASSERT_EQ(*(int *) bst_min(bst), 20);
    ASSERT_EQ(*(int *) bst_max(bst), 100);

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
    ASSERT_TRUE(bst_contains(bst, &num, compare_int));

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
    ASSERT_NOT_NULL(bst_search(bst, &num, compare_int));

    bst_discard(bst);
    bst = NULL;
}

void test_bst_clear(void) {
    struct BinarySearchTree *bst = bst_create();

    int a = 1, b = 2;
    bst_insert(bst, &a, sizeof(int), compare_int);
    bst_insert(bst, &b, sizeof(int), compare_int);

    bst_clear(bst);
    ASSERT_EQ(bst_size(bst), 0);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_size(void) {
    struct BinarySearchTree *bst = bst_create();

    int a = 1;
    bst_insert(bst, &a, sizeof(int), compare_int);
    ASSERT_EQ(bst_size(bst), 1);

    int b = 1000;
    bst_insert(bst, &b, sizeof(int), compare_int);
    ASSERT_EQ(bst_size(bst), 2);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_is_empty(void) {
    struct BinarySearchTree *bst = bst_create();
    ASSERT_TRUE(bst_isempty(bst));

    int a = 1;
    bst_insert(bst, &a, sizeof(int), compare_int);
    ASSERT_FALSE(bst_isempty(bst));

    bst_discard(bst);
    bst = NULL;
}

void test_bst_min(void) {
    struct BinarySearchTree *bst = bst_create();

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    ASSERT_EQ(*(int *) bst_min(bst), 20);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_max(void) {
    struct BinarySearchTree *bst = bst_create();

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    ASSERT_EQ(*(int *) bst_max(bst), 300);

    bst_discard(bst);
    bst = NULL;
}

void test_bst_height(void) {
    struct BinarySearchTree *bst = bst_create();

    ASSERT_EQ(bst_height(bst), 0);

    int nums[4] = { 100, 20, 300, 40 };
    for (int i = 0; i < 4; i++) {
        bst_insert(bst, &nums[i], sizeof(int), compare_int);
    }

    ASSERT_EQ(bst_height(bst), 3);

    bst_discard(bst);
    bst = NULL;
}
