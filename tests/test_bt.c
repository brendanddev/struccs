/**
 * test_bt.c
 * The test suite for the BinaryTree implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_utils.h"
#include "binary_tree.h"


// Prototypes
void test_bt_init(void);
void test_bt_insert(void);
void test_bt_insert_many(void);
void test_bt_remove(void);
void test_bt_get(void);
void test_bt_set(void);
void test_bt_contains(void);
void test_bt_find(void);
void test_bt_is_empty(void);
void test_bt_size(void);
void test_bt_capacity(void);
void test_bt_clear(void);
void test_bt_height(void);
void test_bt_leaves(void);

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

    TEST(test_bt_init);
    TEST(test_bt_insert);
    TEST(test_bt_insert_many);
    TEST(test_bt_remove);
    TEST(test_bt_get);
    TEST(test_bt_set);
    TEST(test_bt_contains);
    TEST(test_bt_find);
    TEST(test_bt_is_empty);
    TEST(test_bt_size);
    TEST(test_bt_capacity);
    TEST(test_bt_clear);
    TEST(test_bt_height);
    TEST(test_bt_leaves);

    return 0;
}

void test_bt_init(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    ASSERT_NOT_NULL(bt);
    ASSERT_EQ(bt_size(bt), 0);
    ASSERT_TRUE(bt_isempty(bt));

    bt_discard(bt);
    bt = NULL;
}

void test_bt_insert(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    int num = 100;
    bt_insert(bt, &num);

    ASSERT_EQ(bt_size(bt), 1);
    ASSERT_FALSE(bt_isempty(bt));

    bt_discard(bt);
    bt = NULL;
}

void test_bt_insert_many(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 10000; i++) {
        int num = 13 * i;
        bt_insert(bt, &num);
    }

    ASSERT_EQ(bt_size(bt), 10000);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_remove(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        int num = 2 * i;
        bt_insert(bt, &num);
    }
    ASSERT_EQ(bt_size(bt), 10);

    for (int i = 0; i < 4; i++) {
        bt_remove(bt, 0);
    }
    ASSERT_EQ(bt_size(bt), 6);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_get(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int val;
    ASSERT_TRUE(bt_get(bt, 0, &val));
    ASSERT_EQ(val, 0);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_set(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int set = 10;
    ASSERT_TRUE(bt_set(bt, 0, &set));

    int val;
    ASSERT_TRUE(bt_get(bt, 0, &val));
    ASSERT_EQ(val, 10);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_contains(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int contains = 1;
    ASSERT_TRUE(bt_contains(bt, &contains, compare_int));

    bt_discard(bt);
    bt = NULL;
}

void test_bt_find(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int val = 2;
    ASSERT_TRUE(bt_find(bt, &val, compare_int) != -1);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_is_empty(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    ASSERT_TRUE(bt_isempty(bt));

    int num = 100;
    bt_insert(bt, &num);

    ASSERT_FALSE(bt_isempty(bt));

    bt_discard(bt);
    bt = NULL;
}

void test_bt_size(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    ASSERT_EQ(bt_size(bt), 0);

    int num = 100;
    bt_insert(bt, &num);

    ASSERT_EQ(bt_size(bt), 1);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_capacity(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    ASSERT_EQ(bt_capacity(bt), 12);

    for (int i = 0; i < 12; i++) {
        bt_insert(bt, &i);
    }

    ASSERT_EQ(bt_capacity(bt), 24);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_clear(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    int num = 100;
    bt_insert(bt, &num);

    ASSERT_EQ(bt_size(bt), 1);

    bt_clear(bt);

    ASSERT_EQ(bt_size(bt), 0);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_height(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    ASSERT_EQ(bt_height(bt), -1);

    int a = 10;
    bt_insert(bt, &a);
    ASSERT_EQ(bt_height(bt), 0);

    int b = 20, c = 30;
    bt_insert(bt, &b);
    bt_insert(bt, &c);

    ASSERT_EQ(bt_height(bt), 1);

    bt_discard(bt);
    bt = NULL;
}


void test_bt_leaves(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    ASSERT_EQ(bt_leaves(bt), 0);

    int a = 10;
    bt_insert(bt, &a);
    ASSERT_EQ(bt_leaves(bt), 1);

    int b = 20, c = 30;
    bt_insert(bt, &b);
    bt_insert(bt, &c);

    ASSERT_EQ(bt_leaves(bt), 2);

    bt_discard(bt);
    bt = NULL;
}
