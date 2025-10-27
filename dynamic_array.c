#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// dynamic_array.c

// Prototypes
static void _resize(struct DynamicArray *da);
static void _shift_right(struct DynamicArray *da, int index);
static void _shift_left(struct DynamicArray *da, int index);



/// Initializes an instance of the DynamicArray

/// @brief Initializes a new instance of the DynamicArray structure
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
        // Array is full - reisze to make room
        _resize(da);

        // Insert the new element at the end and increment length
        da->ptrData[da->length++] = element;
    }
}

/// Adds an integer at a specified index in the array
int _add_at(struct DynamicArray *da, int index, int element) {

    // Ensure capacity
    if (da->length < da->capacity) {

    }

}


/// Get an element from the array at the specified index
int _get(struct DynamicArray *da, int index) {
    if (index < 0 || index > da->length) return -1;
    return da->ptrData[index];
}

/// Removes an element from the back of the array by decrementing length
void _remove_back(struct DynamicArray *da) { 
    da->length--;
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



/// @brief Doubles the internal arrays capacity when the current capacity is full,
///         allowing space for the additional elements.
///
/// Consider: If 'realloc()' fails assigning directly to 'da->ptrData', would lose the 
//            pointer to the old array and cause a memory leak
//            Could use 'malloc()' and copy elements one by one
/// 
/// @param da A pointer to the DynamicArray structure to be resized.
static void _resize(struct DynamicArray *da) { 

    // Set new capacity to old cap * 2
    da->capacity *= 2;

    // Allocate more memory for the new size of the array
    // In this case, we request a new larger memory block using realloc, which tries to
    // resize the existing block if possible, and store the result in a temporary pointer 
    // for safety
    int *newData = realloc(da->ptrData, da->capacity * sizeof(int));

    // If the realloc operations returns NULL, the allocation failed but old data is still
    // valid. We exit here to prevent undefined behavior and data loss.
    if (newData == NULL) {
        printf("Memory allocation failed during resize.\n");
        exit(1);
    }

    // If realloc succeeded, update the arrays pointer to reference the new memory block
    da->ptrData = newData;
}


/// @brief Shifts elements of the DynamicArray one position to the right starting from a specified index.
///        This is used to make room for a new element to be inserted at 'index'.
///
/// @param da A pointer to the DynamicArray structure whose elements are being shifted.
/// @param index The position at which the new element will be inserted. All elements from this index
//               to the last element will be moved one position to the right.
static void _shift_right(struct DynamicArray *da, int index) { 
    // Loop backwards from the last element to the specified index
    // Each element is moved one position to the right to make space at 'index'
    for (int i = da->length - 1; i >= index; i--) {
        da->ptrData[i + 1] = da->ptrData[i];
    }
}


/// @brief Shifts elements of the DynamicArray one position to the left starting from a specified index.
///        This is used to fill the gap left by a removed element at 'index'.
///
/// @param da A pointer to the DynamicArray whose elements are being shifted.
/// @param index The index of the element being removed. All elements after this index will be moved one 
///              one position to the left to fill the gap.
static void _shift_left(struct DynamicArray *da, int index) {

    // Loop from the index of the removed element up to the second last element
    // Each element at 'i+1' is copied into 'i', moving elements left to fill the gap
    for (int i = index; i < da->length - 1; i++) {
        da->ptrData[i] = da->ptrData[i + 1];
    }
}