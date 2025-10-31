#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// dynamic_array.c

// Prototypes
static void resize(struct DynamicArray *da);
static void shrink(struct DynamicArray *da);
static void shift_right(struct DynamicArray *da, int index);
static void shift_left(struct DynamicArray *da, int index);


// Initializes a DynamicArray
struct DynamicArray * _init() {

    // Declare the pointer to the DynamicArray struct and 
    // Allocate enough memory for the struct
    struct DynamicArray *da = NULL;
    da = malloc(sizeof(struct DynamicArray));

    // Set initial capacity, current capacity, and length
    da->initial_capacity = 4;
    da->capacity = da->initial_capacity;
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

// Retrieves an element at a specified index
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

// Returns the length/size of the array
int _size(struct DynamicArray *da) {
    return da->length;
}

// Returns the current capacity of the array
int _capacity(struct DynamicArray *da) {
    return da->capacity;
}

// Checks if the array contains a specified item
bool _contains(struct DynamicArray *da, int item) {
    for (int i = 0; i < da->length; i++) {
        if (da->ptrData[i] == item) {
            return true;
        }
    }
    return false;
}

// Clears the contents of the array by setting the length to 0
void _clear(struct DynamicArray *da) {
    da->length = 0;
}


// Frees the memory used by the DynamicArray, including its internal array 
void _discard(struct DynamicArray *da) {
    if (da != NULL) {
        free(da->ptrData);
        free(da);
    }
}

// Prints the contents of the DynamicArray
void _print(struct DynamicArray *da) {
    printf("Capacity: %d\nLength: %d\n", da->capacity, da->length);
    for (int i = 0; i < da->length; i++) {
        printf("[%d] - %d\n", i, da->ptrData[i]);
    }

    shrink(da);
}


/// Static methods that belong to the current file


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

// Shrinks the internal array if the length of the array is alot less than the capacity
static void shrink(struct DynamicArray *da) {
    // Check length compared to capacity to determine usage
    // Ensure we dont reallocate too little, will need to ensure we dont go past a default capacity
    // If usage falls below a certain amount, reallocate less memory for the array
    
    double usage = (double) da->length / da->capacity * 100;
    double threshold = 25.0;

    // Check if the arr usage has fallen below the threshold
    if (usage < threshold) {
        // Reallocate less memory, but enough for the current size and default capacity
        printf("The current Array Usage: %f has fallen below the threshold: %f\n", usage, threshold);
    }

    printf("Current Array Usage: %f\n", usage);
}

// Shifts elements starting at the last index, to the insertion index to make room for the item being added
static void shift_right(struct DynamicArray *da, int index) {
    // Start at last index, loop until we reach the insertion index
    for (int i = da->length - 1; i >= index; i--) {
        da->ptrData[i + 1] = da->ptrData[i];
    }
}

// Shifts items in the array to the left to fill the gap from the item being removed
static void shift_left(struct DynamicArray *da, int index) {
    for (int i = index + 1; i < da->length - 1; i++) {
        da->ptrData[i] = da->ptrData[i + 1];
    }
}