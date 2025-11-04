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

    int value = 999;
    void *val_ptr = &value;
    if (_add(ga, 0, val_ptr)) {
        printf("Item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }
    print_arr(ga);
    _print(ga);
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

    free(ga);
    ga = NULL;
}



void print_arr(struct GenericArray *ga) {
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] - %d\n", i, *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
}