#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// dynamic_array.c

// Prototypes
static void resize(struct DynamicArray *da);
static void shift_right(struct DynamicArray *da, int index);
static void shift_left(struct DynamicArray *da, int index);


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


// Adds an item at the specified index
void _add(struct DynamicArray *da, int item, int index) {
    if (da->length == da->capacity) {
        resize(da);
    }

    shift_right(da, index);
    printf("Inserting %d at index %d\n", item, index);
    da->ptrData[index] = item;
    da->length++;
}

// Adds an item to the back of the array
void _append(struct DynamicArray *da, int item) {

    // Capacity reached, resize needed
    if (da->length == da->capacity) {
        // resize
        resize(da);
    }

    da->ptrData[da->length++] = item;
}


int _get(struct DynamicArray *da, int index) {
    return da->ptrData[index];
}

// Removes the last item in the array
void _remove_last(struct DynamicArray *da) {
    da->length--;
}

// Removes an item at a specifed index
void _remove_at(struct DynamicArray *da, int index) {
    shift_left(da, index);
    da->length--;
}

// Remove the first occurence of a specified item
void _remove(struct DynamicArray *da, int item) {
    for (int i = 0; i < da->length; i++) {
        if (da->ptrData[i] == item) {
            shift_left(da, i);
            da->length--;
        }
    }
}

// Prints the contents of the DynamicArray
void _print(struct DynamicArray *da) {
    for (int i = 0; i < da->length; i++) {
        printf("[%d] - %d\n", i, da->ptrData[i]);
    }
}

void _status(struct DynamicArray *da) {
    printf("Capacity: %d\nLength: %d\n", da->capacity, da->length);
}


// Resizes the array by doubling its capacity and reallocating more memory
static void resize(struct DynamicArray *da) {

    // Set new capacity, double the initial
    da->capacity = da->capacity * 2;

    // Initialize a temporary pointer to NULL
    int *ptrTemp = NULL;

    // Reallocate more memory for the new capacity of the array
    // and point the pointer at the 
    ptrTemp = realloc(da->ptrData, sizeof(int) * da->capacity);
    da->ptrData = ptrTemp;
}


static void shift_right(struct DynamicArray *da, int index) {

    for (int i = da->length - 1; i > index + 1; i--) {
        printf("Before move: [%d] -> %d\n", i, da->ptrData[i]);
        da->ptrData[i + 1] = da->ptrData[i];
        printf("After move: [%d] = %d\n", i + 1, da->ptrData[i + 1]);
    }




    // for (int i = index; i < da->length - 1; i++) {
    //     printf("Before move: [%d] -> %d\n", i, da->ptrData[i]);
    //     da->ptrData[i + 1] = da->ptrData[i];
    //     printf("After move: [%d] = %d\n", i + 1, da->ptrData[i + 1]);
    //     // printf("Moving element %d from %d to %d\n", da->ptrData[i], i, i + 1);
    // }
}

// Shifts items in the array to the left to fill the gap from the item being removed
static void shift_left(struct DynamicArray *da, int index) {
    for (int i = index + 1; i < da->length - 1; i++) {
        da->ptrData[i] = da->ptrData[i + 1];
    }
}