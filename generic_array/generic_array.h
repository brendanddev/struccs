#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// generic_array.h
/// Brendan Dileo - November 3 2025


// Defines the GenericArray struct type
typedef struct GenericArray {
    void *ptrData;                  // Pointer to the memory where the array elements will be stored
    size_t item_size;               // The size of items stored in the array
    int capacity;
    int length;
} GenericArray;


struct GenericArray * _init(size_t item_size);
bool _append(struct GenericArray *ga, void *itemPtr);