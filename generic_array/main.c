#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"
#include "utils.h"


/// main.c
/// Brendan Dileo - November 3 2025

// Prototypes
void test_insertion();
void test_deletion();


int main() {

    test_insertion();
    return 0;
}


void test_insertion() {

    struct GenericArray *ga_int = create_int_array();
    struct GenericArray *ga_dbl = create_dbl_array();
    print_arr_int(ga);
    print_arr_dbl(ga);

    _discard(ga_int);
    _discard(ga_dbl);
    ga_int = NULL;
    ga_dbl = NULL;
}

void test_deletion() {

    struct GenericArray *ga = create_int_array();
    _print(ga);

    _discard(ga);
    ga = NULL;
}

















void test_add() {

    int value = 999;
    void *val_ptr = &value;
    if (_add(ga, 0, val_ptr)) {
        printf("Item added successfully\n");
    } else {
        printf("Failed to add item\n");
    }

    print_arr_int(ga);
    _print(ga);

    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_get() {
    printf("=========================================\n");
    printf("GET TEST (_get): \n");
    struct GenericArray *ga = create_int_array();

    void *value_ptr;
    if (_get(ga, 1, &value_ptr)) {
        printf("GET VALUE: %d\n", *(int *)value_ptr);
    } else {
        printf("GET operation failed.\n");
    }

    void *value_ptr2;
    if (_get(ga, 0, &value_ptr2)) {
        printf("GET VALUE: %d\n", *(int *)value_ptr2);
    } else {
        printf("GET operation failed.\n");
    }

    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_set() {
    printf("=========================================\n");
    printf("SET TEST (_set): \n");
    struct GenericArray *ga = create_int_array();

    int val = 1;
    void *ptr_val = &val;
    if (_set(ga, 0, ptr_val)) {
        printf("SET operation successful\n");
    }

    print_arr_int(ga);
    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_remove_last() {
    printf("=========================================\n");
    printf("REMOVE LAST (_remove_last) TEST: \n");
    struct GenericArray *ga = create_int_array();
    print_arr_int(ga);

    for (int i = 0; i < 95; i++) {
        _remove_last(ga);
        _print(ga);
    }

    printf("AFTER REMOVE LAST: \n");
    print_arr_int(ga);
    
    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}

void test_remove_at() {
    printf("=========================================\n");
    printf("REMOVE AT (_remove_at) TEST: \n");
    struct GenericArray *ga = create_int_array();
    printf("BEFORE REMOVAL: \n");
    print_arr_int(ga);

    _remove_at(ga, 0);
    printf("AFTER REMOVAL: \n");
    print_arr_int(ga);

    _remove_at(ga, 1);
    printf("AFTER REMOVAL INDEX 1: \n");
    print_arr_int(ga);

    _discard(ga);
    ga = NULL;
    printf("=========================================\n");
}