#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
bool _add(struct DynamicArray *da, int item, int index) {
    if (index < 0 || index > da->length) return false;

    if (da->length == da->capacity) {
        resize(da);
    }

    shift_right(da, index);
    da->ptrData[index] = item;
    da->length++;
    return true;
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
bool _get(struct DynamicArray *da, int index, int *out_value) {
    if (index < 0 || index >= da->length) return false;

    // Store the value from the array into the variable pointed to by *out_value
    // and return true to indicate the operation succeeded
    *out_value = da->ptrData[index];
    return true;
}

// Sets an item in the array to a new specified item at the specified index
void _set(struct DynamicArray *da, int item, int index) {
    if (index < 0 || index >= da->length) {
        fprintf(stderr, "Index is out of bounds for the array\n");
        return;
    }
    da->ptrData[index] = item;
}

// Removes the last item in the array
void _remove_last(struct DynamicArray *da) {
    if (da->length == 0) {
        fprintf(stderr, "Cannot remove from an empty array\n");
        return;
    }
    
    da->length--;

    if (_usage(da) < SHRINK_THRESHOLD) {
        shrink(da);
    }
}

// Removes an item at a specifed index
void _remove_at(struct DynamicArray *da, int index) {
    if (da->length == 0) {
        fprintf(stderr, "Cannot remove from an empty array\n");
        return;
    }

    if (index < 0 || index >= da->length) {
        fprintf(stderr, "Index is out of bounds for the array\n");
        return;
    }
    shift_left(da, index);
    da->length--;
}

// Remove the first occurence of a specified item
void _remove(struct DynamicArray *da, int item) {
    if (da->length == 0) {
        fprintf(stderr, "Cannot remove from an empty array\n");
        return;
    }

    for (int i = 0; i < da->length; i++) {
        if (da->ptrData[i] == item) {
            shift_left(da, i);
            da->length--;
            break;
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

double _usage(struct DynamicArray *da) {
    return ((double) da->length / da->capacity) * 100;
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
}


/// Static methods that belong to the current file


// Resizes the array by doubling its capacity and reallocating more memory
static void resize(struct DynamicArray *da) {

    // Set new capacity, double the initial
    da->capacity = da->capacity * 2;

    // Initialize a temporary pointer to NULL
    int *ptrTemp = NULL;

    // Reallocate more memory for the new capacity of the internal array
    ptrTemp = realloc(da->ptrData, sizeof(int) * da->capacity);

    // Handle case where allocation failed
    if (ptrTemp == NULL) {
        fprintf(stderr, "Memory allocation failed during resize\n");
        exit(EXIT_FAILURE);
    }

    // Update the arrays internal pointer to point to the new memory
    da->ptrData = ptrTemp;
}

// Shrinks the internal array if the arrays usage falls below a set threshold
static void shrink(struct DynamicArray *da) {
    printf("TRIGGERING SHRINK\n");

    int new_capacity;
    // Check if current length is larger than the initial capacity
    // If it is, the length is the new capacity
    // Otherwise the new capacity is the initial capacity to avoid shrinking too low
    if (da->length > da->initial_capacity) {
        new_capacity = da->length;
    } else {
        new_capacity = da->initial_capacity;
    }

    // Create a temporary pointer to realloc the new amount of memory
    int *newPtrData = NULL;
    newPtrData = realloc(da->ptrData, sizeof(int) * new_capacity);

    // Point the struct pointer to the new resized memory
    // and set new capacity
    da->ptrData = newPtrData;
    da->capacity = new_capacity;
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
    for (int i = index; i < da->length - 1; i++) {
        da->ptrData[i] = da->ptrData[i + 1];
    }
}