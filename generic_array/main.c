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



int main() {
    // test_insertion();
    // test_deletion();
    // test_access();
    // test_contains();
    test_shrinking();
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
        _print(ga);
    }

    // Remove items from index 1
    for (int i = 0; i < 45; i++) {
        _remove_at(ga, 1);
        _print(ga);
    }

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

    for (int i = 0; i < 95; i++) {
        _remove_last(ga);
        _print(ga);
    }

    _print(ga);

    int val = 5;
    void *ptr = &val;
    if (_append(ga, ptr)) printf("Item appended\n");

    _print(ga);
    
    // Segmentation fault occurs here
    // Array shrinks from capacity 128 --> 6
    // Item gets appended, increments length from 5 --> 6
    // At this point capacity is also 6
    // Another append attempt, should immediately trigger a resize (i want to avoid this but first deal with this bug)
    // Instead program crashes
    int val2 = 100;
    void *ptr2 = &val2;
    if (_append(ga, ptr2)) printf("Item appended\n");

    _print(ga);


}