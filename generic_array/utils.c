#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"
#include "utils.h"


/// utils.c
/// Brendan Dileo - November 4 2025


// Creates a new GenericArray and populates it with integers
struct GenericArray * create_array() {
    struct GenericArray *ga = _init(sizeof(int));
    for (int i = 0; i < 100; i++) {
        int rd_num = rand() % 1000;
        void *ptr = &rd_num;
        _append(ga, ptr);
    }
    return ga;
}


// Prints the contents of an integer based GenericArray
void print_arr_int(struct GenericArray *ga) { 
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] - %d\n", i, *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
}