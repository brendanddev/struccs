#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"


/// main.c
/// Brendan Dileo - November 3 2025

// Prototypes
void test_append();
void test_add();
void test_get();
void print_arr(struct GenericArray *ga);


int main() {
    test_add();
    return 0;
}


void test_append() {
    printf("=========================================\n");
    struct GenericArray *ga = _init(sizeof(int));
    _print(ga);

    int num = 100;
    void *ptr = &num;
    _append(ga, ptr);
    _print(ga);

    int num2 = 200;
    void *ptr2 = &num2;
    _append(ga, ptr2);
    
    int num3 = 300;
    void *ptr3 = &num3;
    _append(ga, ptr3);
    _print(ga);

    print_arr(ga);
    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_add() {
    printf("=========================================\n");
    printf("ADD TEST (_add): \n");
    struct GenericArray *ga = _init(sizeof(int));
    _print(ga);

    int num1 = 200;
    void *ptr1 = &num1;
    _append(ga, ptr1);
    print_arr(ga);

    int num2 = 1000;
    void *ptr2 = &num2;
    _append(ga, ptr2);
    print_arr(ga);

    int num3 = 500;
    void *ptr3 = &num3;
    _append(ga, ptr3);
    print_arr(ga);

    int value = 999;
    void *val_ptr = &value;
    if (_add(ga, 0, val_ptr)) {
        printf("Item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }
    print_arr(ga);
    _print(ga);

    int value2 = 7777;
    void *val2_ptr = &value2;
    if (_add(ga, 1, val2_ptr)) {
        printf("Second item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    int value3 = 101;
    void *val3_ptr = &value3;
    if (_add(ga, 1, val3_ptr)) {
        printf("Third item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    int value4 = 555;
    void *val4_ptr = &value4;
    if (_add(ga, 1, val4_ptr)) {
        printf("Fourth item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    int value5 = 4;
    void *val5_ptr = &value5;
    if (_add(ga, 1, val5_ptr)) {
        printf("Fifth item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    int value6 = 41000;
    void *val6_ptr = &value6;
    if (_add(ga, 1, val6_ptr)) {
        printf("Sixth item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    print_arr(ga);
    _print(ga);

    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_get() {
    printf("=========================================\n");
    struct GenericArray *ga = _init(sizeof(int));
    _print(ga);

    int num = 100;
    void *ptr = &num;
    _append(ga, ptr);

    int num2 = 200;
    void *ptr2 = &num2;
    _append(ga, ptr2);
    
    int num3 = 300;
    void *ptr3 = &num3;
    _append(ga, ptr3);

    void *value_ptr;
    if (_get(ga, 1, &value_ptr)) {
        printf("GET VALUE: %d\n", (int *)value_ptr);
    } else {
        printf("GET operation failed.\n");
    }

    void *value_ptr2;
    if (_get(ga, 0, &value_ptr2)) {
        printf("GET VALUE: %d\n", (int *)value_ptr2);
    } else {
        printf("GET operation failed.\n");
    }

    _discard(ga);
    ga = NULL;
}



void print_arr(struct GenericArray *ga) {
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] - %d\n", i, *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
}