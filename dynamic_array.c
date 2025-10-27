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


/// @brief Adds an integer to the back of the DynamicArray
/// @param da A pointer to the DynamicArray structure
/// @param element The element being added to the array
void _add(struct DynamicArray *da, int element) { 

    // Check if array is full
    if (da->length == da->capacity) {
        // Array is full - resize to make room
        _resize(da);
    }
    
    // Insert the new element at the end and increment length
    da->ptrData[da->length++] = element;
}


/// @brief Adds an integer at a specified index in the DynamicArray
/// @param da A pointer to the DynamicArray structure
/// @param index The index where the element is added into the array
/// @param element The element being added to the array
void _add_at(struct DynamicArray *da, int index, int element) {

    // Check if array is full
    if (da->length == da->capacity) {
        // Array is full - resize to make room
        _resize(da);
    }

    // Check if insertion is at the end
    if (index == da->length) {
        // Insert the new element at the end and increment length
        da->ptrData[da->length++] = element;

    // Shift is needed
    } else {
        _shift_right(da, index);
        da->ptrData[index] = element;
        da->length++;
    }
}


/// Get an element from the array at the specified index
int _get(struct DynamicArray *da, int index) {
    if (index < 0 || index > da->length) return -1;
    return da->ptrData[index];
}


/// @brief Removes an element at the specified index in the DynamicArray.
///        All elements after the removed element are shifted to the left to fill the gap.
/// @param da A pointer to the DynamicArray structure.
/// @param index The index of the element to remove.
void _remove_at(struct DynamicArray *da, int index) { 

    // Check index is within bounds of array

    // Check that index is within valid range of the array
    if (index >= 0 && index < da->length) {

        // Shift all elements after the specified index one position to the left
        // Overrides the element at 'index' and fills the gap
        _shift_left(da, index);

        // Decrement length since array contains one less element
        da->length--;
    }
}


/// @brief Removes the first occurrence of a specified element from the DynamicArray.
///        If the element is found, all subsequent elements are shifted left to fill the gap.
/// @param da A pointer to the DynamicArray structure.
/// @param element The value to remove from the array.
void _remove(struct DynamicArray *da, int element) { 
    
    // Iterate through to find the specified element
    for (int i = 0; i < da->length; i++) {
        if (da->ptrData[i] == element) {
            // If found, remove element at index 'i'
            _remove_at(da, i);
            return;
        }
    }
}


/// @brief Removes an element from the back of the array by decrementing the length.
/// @param da A pointer to the DynamicArray structure.
void _remove_back(struct DynamicArray *da) { 
    da->length--;
}


/// @brief Frees the memory in use by the DynamicArray.
/// @param da A pointer to the DynamicArray structure.
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