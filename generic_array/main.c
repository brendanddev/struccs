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
void test_access();
void test_contains();
void test_shrinking();
void test_sorting();





int main() {
    // test_insertion();
    // test_deletion();
    // test_access();
    // test_contains();
    // test_shrinking();
    test_sorting();
    return 0;
}


void test_insertion() {
    struct GenericArray *ga_int = create_int_array();
    struct GenericArray *ga_dbl = create_dbl_array();
    struct GenericArray *ga_chr = create_chr_array();
    print_arr_int(ga_int);
    print_arr_dbl(ga_dbl);
    print_arr_chr(ga_chr);

    _discard(ga_int);
    ga_int = NULL;

    _discard(ga_dbl);
    ga_dbl = NULL;

    _discard(ga_chr);
    ga_chr = NULL;
}

void test_deletion() {
    struct GenericArray *ga = create_int_array();
    _print(ga);

    // Remove last elements
    for (int i = 0; i < 50; i++) {
        _remove_last(ga);
    }
    _print(ga);

    // Remove items from index 1
    for (int i = 0; i < 45; i++) {
        _remove_at(ga, 1);
    }
    _print(ga);

    _discard(ga);
    ga = NULL;
}


void test_access() {
    struct GenericArray *ga = create_int_array();
    _print(ga);

    // Get the value at index 1
    int value;
    if (_get(ga, 1, &value)) {
        printf("Get Value: %d\n", value);
    } else {
        printf("Failed to retrieve the value!\n");
    }

    // // Set the value at index 0
    int val = 999;
    void *ptr_val = &val;
    if (_set(ga, 0, ptr_val)) {
        printf("Set index 0 = %d\n", val);
    } else {
        printf("Failed to set!\n");
    }

    print_arr_int(ga);
    _discard(ga);
    ga = NULL;
}

void test_contains() {
    struct GenericArray *ga_int = create_int_array();
    print_arr_int(ga_int);

    // Declare a func *ptr and point it to the address of the type specific comparison func
    bool (*fptr)(void *, void *);
    fptr = &contains_int;

    // Initialize the value being searched for,
    // and point the void *ptr to point to that address
    int value = 64;
    void *ptr = NULL;
    ptr = &value;


    // For each element, calls the function pointed to by the fptr (which is contains_int),
    // to search for the value pointed to in the ptr
    if (_contains(ga_int, fptr, ptr)) {
        printf("Located value!\n");
    } else {
        printf("Value is not here.\n");
    }
}


void test_shrinking() {
    struct GenericArray *ga = create_int_array();
    _print(ga);

    for (int i = 0; i < 94; i++) {
        _remove_last(ga);
    }
    _print(ga);

    // Adding an item immediately after a shrink can trigger a resize
    // The shrink operation reduces capacity to either the current length of the array or the initial capacity
    // If the array is already nearly full, the next append exceeds the new capacity causing an imemdiate resize
    // Doing this frequently can be costly and inefficient

    int val = 5;
    void *ptr = &val;
    if (_append(ga, ptr)) printf("Item appended\n");

    _print(ga);
}


bool greatest_first(void *a, void *b) {
    int ia = * (int *)a;
    int ib = * (int *)b;
    if (a > b) return true;
    return false;
}

bool smallest_first(void *a, void *b) {
    int ia = * (int *)a;
    int ib = * (int *)b;
    if (a < b) return true;
    return false;
}

void test_sorting() {
    struct GenericArray *ga = create_int_array();
    _print(ga);
    print_arr_int(ga);
    printf("\n");

    printf("SWAP OPERATION: \n");
    void *idxone = (char *) ga->ptrData + 1 * ga->item_size;
    void *idxtwo = (char *) ga->ptrData + 2 * ga->item_size;
    _swap(ga, idxone, idxtwo);
    print_arr_int(ga);
    printf("\n");

    printf("SORT OPERATION: \n");
    bool (*fptr)(void*, void*);
    fptr = &smallest_first;
    _sort(ga, fptr);
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] ", *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
}