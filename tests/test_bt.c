/**
 * test_bt.c
 * The test suite for the BinaryTree implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
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

    test_bt_init();


    return 0;
}

void test_bt_init(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    assert(bt != NULL);
    assert(bt_size(bt) == 0);
    assert(bt_isempty(bt) == true);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_insert(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    int num = 100;
    bt_insert(bt, &num);

    assert(bt_size(bt) == 1);
    assert(bt_isempty(bt) == false);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_insert_many(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 10000; i++) {
        int num = 13 * i;
        bt_insert(bt, &num);
    }

    assert(bt_size(bt) == 10000);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_remove(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 10; i++) {
        int num = 2 * i;
        bt_insert(bt, &num);
    }
    assert(bt_size(bt) == 10);

    for (int i = 0; i < 4; i++) {
        bt_remove(bt, 0);
    }
    assert(bt_size(bt) == 6);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_get(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int val;
    assert(bt_get(bt, 0, val));
    assert(val == 0);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_set(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int set = 10;
    assert(bt_set(bt, 0, &set));
    
    int val;
    assert(bt_get(bt, 0, val));
    assert(val == 10);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_contains(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int contains = 1;
    assert(bt_contains(bt, &contains, compare_int) == true);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_find(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    for (int i = 0; i < 3; i++) {
        bt_insert(bt, &i);
    }

    int val = 2;
    assert(bt_find(bt, &val, compare_int) != -1);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_is_empty(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    assert(bt_isempty(bt) == true);

    int num = 100;
    bt_insert(bt, &num);

    assert(bt_isempty(bt) == false);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_size(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    assert(bt_size(bt) == 0);

    int num = 100;
    bt_insert(bt, &num);

    assert(bt_size(bt) == 1);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_capacity(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));
    assert(bt_capacity(bt) == 12);

    for (int i = 0; i < 12; i++) {
        bt_insert(bt, &i);
    }

    assert(bt_capacity(bt) == 24);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_clear(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    int num = 100;
    bt_insert(bt, &num);

    assert(bt_size(bt) == 1);

    bt_clear(bt);

    assert(bt_size(bt) == 0);

    bt_discard(bt);
    bt = NULL;
}

void test_bt_height(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    assert(bt_height(bt) == -1);

    int a = 10;
    bt_insert(bt, &a);
    assert(bt_height(bt) == 0);

    int b = 20, c = 30;
    bt_insert(bt, &b);
    bt_insert(bt, &c);

    assert(bt_height(bt) == 1);

    bt_discard(bt);
    bt = NULL;
}


void test_bt_leaves(void) {
    struct BinaryTree *bt = bt_create(sizeof(int));

    assert(bt_leaves(bt) == 0);

    int a = 10;
    bt_insert(bt, &a);
    assert(bt_leaves(bt) == 1);

    int b = 20, c = 30;
    bt_insert(bt, &b);
    bt_insert(bt, &c);

    assert(bt_leaves(bt) == 2);

    bt_discard(bt);
    bt = NULL;
}