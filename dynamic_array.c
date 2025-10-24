#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// dynamic_array.c

/// Initializes an instance of the DynamicArray
struct DynamicArray * _init() {

    // Allocate memory for the struct DynamicArray
    // Use sizeof to allocate just enough memory to hold the struct itself right now
    struct DynamicArray *da = malloc(sizeof(struct DynamicArray));

    // Initialize the structs fields (members)
    da->length = 0;
    da->capacity = 4;
    da->ptrData = NULL;

    // Allocate memory for the data the struct DyanmicArray will hold
    // Each int typically takes sizeof(int) bytes
    // Total allocated = sizeof(int) * capacity bytes (4 ints × 4 bytes each on most systems)
    da->ptrData = malloc(sizeof(int) * da->capacity);

    // Return the created struct DynamicArray
    return da;
}

/// Adds an integer to the back of the DynamicArray
int _add(struct DynamicArray *da, int element) { 

    // Ensure capacity
    if (da->length < da->capacity) {
        da->ptrData[da->length++] = element;
    
    // Reached capacity, needs resize
    } else {

        // Set new capacity to old size * 2
        da->capacity = da->capacity * 2;

        // Consider: If 'realloc' fails assisinging directly to 'da->ptrData' would lose the pointer
        // to the old array and cause a memory leak

        // Consider: 'malloc' and make copy of array

        // Allocate more memory for the new size of the array
        // Will allocate: ((old size * 2) * sizeof(int))
        da->ptrData = realloc(da->ptrData, da->capacity * sizeof(int));
        da->ptrData[da->length++] = element;
    }
}

/// Get an element from the array at the specified index
int _get(struct DynamicArray *da, int index) {
    if (index < 0 || index > da->length) return -1;
    return da->ptrData[index];
}


void _remove_back(struct DynamicArray *da) { 
    da->ptrData[da->length--];
}

/// Frees the memory in use by the DynamicArray
void _discard(struct DynamicArray *da) {
    free(da->ptrData);
    da->ptrData = NULL;
}

/// Prints the elements of the DynamicArray
void _print(struct DynamicArray *da) {
    for (int i = 0; i < da->length; i++) {
        printf("[%d] %d\n", i, da->ptrData[i]);
    }
}
