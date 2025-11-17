#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_helpers.h"


/// test_helpers.c
/// Brendan Dileo, November 10 2025


// Creates a new GenericArray and populates it with integers
struct GenericArray * create_int_array() {
    struct GenericArray *ga = _init(sizeof(int));
    for (int i = 0; i < 10; i++) {
        int rd_num = rand() % 1000;
        void *ptr = &rd_num;
        _append(ga, ptr);
    }
    return ga;
}

// Creates a new GenericArray with a specified size and populates it with integers 
struct GenericArray * create_int_array_from_size(int size) {
    struct GenericArray *ga = _init(sizeof(int));
    for (int i = 0; i < size; i++) {
        int rd_num = rand() % 100;
        void *ptr = &rd_num;
        _append(ga, ptr);
    }
    return ga;
}

// Creates a new GenericArray and populates it with doubles
struct GenericArray * create_dbl_array() {
    struct GenericArray *ga = _init(sizeof(double));
    for (int i = 0; i < 10; i++) {
        double rd_num = 0.5 + ((double)rand() / RAND_MAX) * (1000 - 0.5);
        void *ptr = &rd_num;
        _append(ga, ptr);
    }
    return ga;
}

// Creates a new GenericArray and populates it with chars
struct GenericArray * create_chr_array() {
    struct GenericArray *ga = _init(sizeof(char));
    for (int i = 0; i < 10; i++) {
        char rd_chr = 'A' + (rand() % 26);
        void *ptr = &rd_chr;
        _append(ga, ptr);
    }
    return ga;
}

// Defines how two integers will be compared
bool contains_int(void *a, void *b) {
    // Dereferences the void* by first casting to an int*
    // and then storing the int values to check for equality
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia == ib) return true;
    return false;
}

// Returns 0 if equal, 1 if a > b, other wise -1 (a < b)
int compare_int(void *a, void *b) {
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia == ib) {
        printf("Values are equal\n");
        return 0;
    } else if (ia > ib) {
        printf("%d > %d\n", ia, ib);
        return 1;
    } else {
        printf("%d < %d\n", ia, ib);
        return -1;
    }
}

bool equals_int(void *a, void *b) {
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia == ib) return true;
    return false;
}

int is_less_than(void *a, void *b) {
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia < ib) {
        return 0;
    } else if (ia > ib) {
        return 1;
    } else {
        return -1;
    }
}

// Defines how two doubles will be compared
bool contains_dbl(void *a, void *b) {
    double da = * (int *) a;
    double db = * (int *) b;
    if (da == db) return true;
    return false;
}

// Prints the contents of an integer based GenericArray
void print_arr_int(struct GenericArray *ga) { 
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] ", *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
    printf("\n");
}

// Print double based GenericArray
void print_arr_dbl(struct GenericArray *ga) {
    for (int i = 0; i < ga->length; i++) {
        printf("[%f] ", *(double *)((char *)ga->ptrData + i * ga->item_size));
    }
    printf("\n");
}

void print_arr_chr(struct GenericArray *ga) {
    for (int i = 0; i < ga->length; i++) {
        printf("[%c] ", *(char *)((char *)ga->ptrData + i * ga->item_size));
    }
    printf("\n");
}