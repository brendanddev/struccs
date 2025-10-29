#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// dynamic_array.c

// Prototypes
static void _resize(struct DynamicArray *da);


// Initializes a DynamicArray
struct DynamicArray * _init() {

    // Declare the pointer to the DynamicArray struct and 
    // Allocate enough memory for the struct
    struct DynamicArray *da = NULL;
    da = malloc(sizeof(struct DynamicArray));

    // Set initial capacity and length
    da->capacity = 4;
    da->length = 0;
    da->item_size = sizeof(int);

    // Allocate memory for the items the array will store
    da->ptrData = malloc(sizeof(int) * da->capacity);

    // Return the pointer to the struct
    return da;
}


void _add(struct DynamicArray *da, int item) {

    // Capacity reached, resize needed
    if (da->length == da->capacity) {
        // resize
        _resize(da);
        da->length++;
    } else {
        da->ptrData[da->length++] = item;
    }
}

int _get(struct DynamicArray *da, int index) {
    return da->ptrData[index];
}

void _remove(struct DynamicArray *da, int index);

void _print(struct DynamicArray *da) {
    for (int i = 0; i < da->length; i++) {
        printf("[%d] - %d\n", i, da->ptrData[i]);
    }
}

void _status(struct DynamicArray *da) {
    printf("Capacity: %d\nLength: %d\n", da->capacity, da->length);
}


static void _resize(struct DynamicArray *da) {

    // Set new capacity, double the initial
    da->capacity = da->capacity * 2;

    // Initialize a temporary pointer to NULL
    int *ptrTemp = NULL;

    // Reallocate more memory for the new capacity of the array
    // and point the pointer at the 
    ptrTemp = realloc(da->ptrData, sizeof(int) * da->capacity);
    da->ptrData = ptrTemp;
}