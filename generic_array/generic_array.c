#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generic_array.h"


/// generic_array.c
/// Brendan Dileo - November 3 2025


// Prototypes
static void resize(struct GenericArray *ga);
static void shrink(struct GenericArray *ga);
static void shift_right(struct GenericArray *ga, int index);
static void shift_left(struct GenericArray *ga, int index);


// Initializes a new GenericArray
struct GenericArray * _init(size_t item_size) {

    // Allocate memory for the struct
    struct GenericArray *ga = NULL;
    ga = malloc(sizeof(struct GenericArray));

    // Handle allocation failure
    if (ga == NULL) {
        fprintf(stderr, "Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }

    ga->capacity = 4;
    ga->length = 0;
    ga->item_size = item_size;

    // Allocate memory for the internal array
    int *pTmp = malloc(item_size * ga->capacity);
    if (pTmp == NULL) {
        fprintf(stderr, "Memory allocation failed for internal array.\n");
        free(ga);               // Free previously allocated struct to avoid memory leak
        exit(EXIT_FAILURE);
    }

    ga->ptrData = pTmp;
    return ga;
}

// Adds an item to the end of the array
bool _append(struct GenericArray *ga, void *itemPtr) { 

    // Check if resize is needed
    if (ga->length == ga->capacity) {
        resize(ga);
    }

    // Calculate the address where the new item should be stored
    // Starting at the base of the internal array (ga->ptrData)
    // Move forward by (length * item_size) bytes to reach the next free slot
    // Gets casted to (char *) so the pointer arithmetic is done in bytes
    void *dest = (char *)ga->ptrData + ga->length * ga->item_size;

    // Copy the memory of the item into the calculated destination
    // Takes the raw bytes starting at 'itemPtr' the item passed to the func,
    // and copies them into the memory at the destination, which is the next free slot in the array
    memcpy(dest, itemPtr, ga->item_size);
    ga->length++;
    return true;
}

// Inserts a new item at a specified index within the GenericArray
bool _add(struct GenericArray *ga, int index, void *in_ptr) {
    if (index < 0 || index > ga->length) return false;

    // Check if resize is needed
    if (ga->length == ga->capacity) {
        resize(ga);
    }

    // Shift subsequent items to the right to make room for item being inserted
    shift_right(ga, index);

    // Calculate the memory location for the item being inserted
    void *dest_ptr = (char *) ga->ptrData + index * ga->item_size;

    // Copy the memory of the item into destination and increment length
    memcpy(dest_ptr, in_ptr, ga->item_size);
    ga->length++;
    return true;
}

// Retrieves an item from a specified index in the array
bool _get(struct GenericArray *ga, int index, void *out_ptr) {
    if (index < 0 || index >= ga->length) return false;

    // Calculate the memory address of the item at the given index by
    // Starting from the base pointer of the array (ga->ptrData)
    // Casting to (char *) so pointer arithmetic is in bytes
    // Adding index * item_size to move to the correct element
    // And using memcpy to copy the bytes of that element into the output ptr
    void *dest = (char *)ga->ptrData + index * ga->item_size;
    memcpy(out_ptr, dest, ga->item_size);
    return true;
}

bool _set(struct GenericArray *ga, int index, void *in_ptr) {
    if (index < 0 || index >= ga->length) return false;

    // Calculate the memory address of the item at the given index
    // Start from base pointer which is the first byte of the allocated memory block
    // and move the offset (index * item_size) in bytes from base pointer to find
    // the specified index
    void *dest = (char *) ga->ptrData + index * ga->item_size;
    memcpy(dest, in_ptr, ga->item_size);
    return true;
}

// Removes the last item in the GenericArray
bool _remove_last(struct GenericArray *ga) {
    if (!ga || ga->length == 0) return false;
    ga->length--;
    return true;
}

bool _remove_at(struct GenericArray *ga, int index) {
    if (index < 0 || index >= ga->length) return false;

    shift_left(ga, index);
    ga->length--;
    return true;
}


// Returns the length of the GenericArray
int _size(struct GenericArray *ga) {
    return ga->length;
}

// Returns the current capacity of the GenericArray
int _capacity(struct GenericArray *ga) {
    return ga->capacity;
}

// Frees any memory allocated by the GenericArray internal array and struct
void _discard(struct GenericArray *ga) {
    if (ga != NULL) {
        free(ga->ptrData);
        free(ga);
    }
}

// Prints the current state of the GenericArray
void _print(struct GenericArray *ga) {
    printf("Capacity: %d, Length: %d, Item Size: %zu bytes\n", ga->capacity, ga->length, ga->item_size);
}



// Private helper functions, linkage limited to this file


// Resizes the internal array when its limit is reached
static void resize(struct GenericArray *ga) {
    // Calculate new capacity
    int new_capacity = ga->capacity * 2;

    // Reallocate more memory for the new array size
    void *tmp_ptr = NULL;
    tmp_ptr = realloc(ga->ptrData, new_capacity * ga->item_size);

    // Handle reallocation failure
    if (tmp_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed during shrinking\n");
        exit(EXIT_FAILURE);
    }

    // Set new capacity and reassign pointer to memory
    ga->capacity = new_capacity;
    ga->ptrData = tmp_ptr;
}


// Shifts items to the right, starting from the end to the index to make room for the item being added
static void shift_right(struct GenericArray *ga, int index) {
    // Loop from end to insertion point
    for (int i = ga->length - 1; i >= index; i--) {
        // Calculate the memory address of the source item at index i and the destination item at index i + 1
        void *src = (char *) ga->ptrData + i * ga->item_size;
        void *dest = (char *) ga->ptrData + (i + 1) * ga->item_size;

        // Copy the memory from src* into dest* effectively doing i + 1 = i
        memcpy(dest, src, ga->item_size);
        // memmove(dest, src, ga->item_size);
    }
}

// Shifts items to the left, starting from the index?
// Shift item being removed to the end to allow for decrementing length for removal
static void shift_left(struct GenericArray *ga, int index) {
    // Loop from index to end
    for (int i = index; i < ga->length; i++) {
        void *src = (char *) ga->ptrData + (i + 1) * ga->item_size;
        void *dest = (char *) ga->ptrData + i * ga->item_size;
        memcpy(dest, src, ga->item_size);
    }
}