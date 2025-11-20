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
static void swap(struct GenericArray *ga, void *val1, void *val2);


// Initializes a new GenericArray
struct GenericArray * ga_init(size_t item_size) {

    // Allocate memory for the struct
    struct GenericArray *ga = NULL;
    ga = malloc(sizeof(struct GenericArray));

    // Handle allocation failure
    if (ga == NULL) {
        fprintf(stderr, "Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }

    ga->initial_capacity = 4;
    ga->capacity = ga->initial_capacity;
    ga->length = 0;
    ga->item_size = item_size;

    // Allocate memory for the internal array
    void *pTmp = malloc(item_size * ga->capacity);
    if (pTmp == NULL) {
        fprintf(stderr, "Memory allocation failed for internal array.\n");
        free(ga);               // Free previously allocated struct to avoid memory leak
        exit(EXIT_FAILURE);
    }

    ga->ptrData = pTmp;
    return ga;
}

// Adds an item to the end of the array
bool ga_append(struct GenericArray *ga, void *itemPtr) { 

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
bool ga_add(struct GenericArray *ga, int index, void *in_ptr) {
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
bool ga_get(struct GenericArray *ga, int index, void *out_ptr) {
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

bool ga_set(struct GenericArray *ga, int index, void *in_ptr) {
    if (index < 0 || index >= ga->length) return false;

    // Calculate the memory address of the item at the given index
    // Start from base pointer which is the first byte of the allocated memory block
    // and move the offset (index * item_size) in bytes from base pointer to find
    // the specified index
    void *dest = (char *) ga->ptrData + index * ga->item_size;
    memcpy(dest, in_ptr, ga->item_size);
    return true;
}

// Find the index of a specified item in the array
int ga_find(struct GenericArray *ga, void *item_ptr, bool (*comparator)(void*, void*)) {

    for (int i = 0; i < ga->length; i++) {
        void *curr = (char *) ga->ptrData + i * ga->item_size;

        // Compare the item being searched for to the current item
        // based on the caller provided definition
        if (comparator(item_ptr, curr)) {
            return i;
        }
    }
    return -1;
}

// Removes the last item in the GenericArray
bool ga_remove_last(struct GenericArray *ga) {
    if (!ga || ga->length == 0) return false;
    ga->length--;

    // Check if memory is underutilized
    if (ga_usage(ga) < SHRINK_THRESHOLD) { 
        printf("SHRINKING...\n");
        shrink(ga);
    }
    return true;
}

// Removes an item from the specified index in the GenericArray
bool ga_remove_at(struct GenericArray *ga, int index) {
    if (index < 0 || index >= ga->length) return false;
    ga->length--;

    // Check if memory is underutilized
    if (ga_usage(ga) < SHRINK_THRESHOLD) { 
        printf("SHRINKING...\n");
        shrink(ga);
    }

    // Shift every element after the index of the item being removed
    shift_left(ga, index);
    return true;
}

// Checks if the GenericArray contains another item
// Takes a pointer to another function that defines how the two items will be compared,
// and another pointer to the target item we are searching the array for
bool ga_contains(struct GenericArray *ga, bool (*funcptr)(void*, void*), void *trgtptr) {
    for (int i = 0; i < ga->length; i++) {
        // Current address = start of memory + index * item_size
        // For the item at index i: Start at base address of the array
        // Move forward i * item_size bytes to reach the i-th element
        void *curr = (char *) ga->ptrData + i * ga->item_size;

        // If the user provided function for comparison returns true,
        // items are equal and we return true
        if (funcptr(curr, trgtptr)) {
            return true;
        }
    }
    return false;
}

// Clears the contents of the array by setting the length to 0
// The allocated memory and existing data remain intact but are marked as unused
// Old values will be overwritten when new items are added
bool ga_clear(struct GenericArray *ga) {
    if (!ga) return false;
    ga->length = 0;
    return true;
}

// Returns the length of the GenericArray
int ga_size(struct GenericArray *ga) {
    return ga->length;
}

// Returns the current capacity of the GenericArray
int ga_capacity(struct GenericArray *ga) {
    return ga->capacity;
}

// Calculates how full the array is internally based on the current number of elements and total allocated space
double ga_usage(struct GenericArray *ga) {
    double usage = (double) ga->length / ga->capacity * 100;
    return usage;
}

// Frees any memory allocated by the GenericArray internal array and struct
void ga_discard(struct GenericArray *ga) {
    if (ga != NULL) {
        free(ga->ptrData);
        free(ga);
    }
}

// Prints the current state of the GenericArray
void ga_print(struct GenericArray *ga, void (* print_fn)(void*)) {
    if (ga->length == 0) return;
    for (int i = 0; i < ga->length; i++) {
        void *curr = (char *) ga->ptrData + i * ga->item_size;
        print_fn(curr);
    }
}

// Bubble Sort implementation for an array of integers with a caller defined 
// comparator function to determine how to order elements
void ga_sort(struct GenericArray *ga, bool (* comparator)(void*, void*)) { 
    bool is_swapped;
    for (int i = 0; i < ga->length - 1; i++) {
        
        is_swapped = false;
        for (int j = 0; j < ga->length - i - 1; j++) {
            
            // Starting from the first address in the allocated memory pointed to by the base pointer (ga->ptrData)
            // Calculate the address of the current item and the next item in the array based on the index bytes offset
            void *curr = (char *) ga->ptrData + j * ga->item_size;
            void *next = (char *) ga->ptrData + (j + 1) * ga->item_size;

            // Call the user defined comparator function through the function pointer
            if (comparator(curr, next)) {
                swap(ga, curr, next);
                is_swapped = true;
            }
        }

        if (is_swapped == false) {
            break;
        }
    }
}

// Reverses items in-place within the array
void ga_reverse(struct GenericArray *ga) {

    // Loop until the middle index of the array to swap front/back pairs in each iteration
    // Once half the array is handled, the entire array is reversed
    for (int i = 0; i < ga->length / 2; i++) {

        // Calculate the memory addresses of the pair of items being swapped,
        // which will be the item at index `i` and the item at index `length - i - 1`
        void *front = (char *) ga->ptrData + i * ga->item_size;
        void *back = (char *) ga->ptrData + (ga->length - i - 1) * ga->item_size;
        swap(ga, front, back);
    }
}

// Makes and returns a deep copy of the GenericArray provided
struct GenericArray* ga_copy(struct GenericArray *ga) {

    // Allocate memory for the copy of the struct itself
    struct GenericArray *ga_copy = NULL;
    ga_copy = malloc(sizeof(struct GenericArray));

    // Allocate memory for the copy of the internal array
    void *new_ga_ptrData = NULL;
    new_ga_ptrData = malloc(ga->item_size * ga->capacity);

    // Copy raw memory from the original structs memory location to the new location
    // This copies all fields, including the pointer to the internal array,
    // which will be immediately overriden to point to the new array
    memcpy(ga_copy, ga, sizeof(struct GenericArray));

    // Copy raw memory from the original internal array to the new memory allocated for the copy of the internal array
    // Where the size in bytes is based on the size of the original array
    memcpy(new_ga_ptrData, ga->ptrData, ga->item_size * ga->length);

    // Point the pointer to the memory allocated for the copy of the internal array
    // instead of the pointer to the old data in memory
    ga_copy->ptrData = new_ga_ptrData;

    return ga_copy;
}

// Searches for an item within a sorted array using a Binary Search implementation and a caller defined comparator function
// to determine how items in the array should be compared
bool ga_binary_find(struct GenericArray *ga, void *item_ptr, int (* comparator)(void*, void*)) {
    // Initialize low and high indexes
    int low = 0;
    int high = ga->length - 1;

    while (low <= high) {
        // Calculate the middle items address based on the middle index
        int mid_idx = low + (high - low) / 2;
        void *mid = (char *) ga->ptrData + mid_idx * ga->item_size;

        int cmp = comparator(mid, item_ptr);

        if (cmp == 0) {
            return true;
        // Check if `mid < item_ptr`
        } else if (cmp == -1) {
            low = mid_idx + 1;
        // `mid > item_ptr`
        } else {
            high = mid_idx - 1;
        }
    }
    return false;
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
        fprintf(stderr, "Memory allocation failed during resizing!\n");
        exit(EXIT_FAILURE);
    }

    // Set new capacity and reassign pointer to memory
    ga->capacity = new_capacity;
    ga->ptrData = tmp_ptr;
}

// Shrinks the internal array when its underutilized by reallocating less memory
static void shrink(struct GenericArray *ga) {

    // Determine new capacity
    // If the current size is larger than the initial capacity, grow to 2.5x the current length
    // Otherwise, grow to 1.5x the initial capacity to avoid reallocating too little memory
    int new_capacity;
    // Length is larger than initial capacity (default = > 4) 
    if (ga->length > ga->initial_capacity) { 
        new_capacity = (int)(ga->length * 2.5); 
    } else { 
        new_capacity = (int)(ga->initial_capacity * 1.5); 
    }

    // Reallocate less memory
    void *tmp = NULL;
    tmp = realloc(ga->ptrData, new_capacity * ga->item_size);

    // Handle reallocation failure
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed during shrinking!\n");
        exit(EXIT_FAILURE);
    }

    // Set new capacity and reassign pointer
    ga->capacity = new_capacity;
    ga->ptrData = tmp;
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

// Shifts items to the left starting at 'index', filling the gap created by the removed item
static void shift_left(struct GenericArray *ga, int index) {
    // Loop from index to end
    for (int i = index; i < ga->length - 1; i++) {
        // Calculate memory address of the source item and the destination item
        void *src = (char *) ga->ptrData + (i + 1) * ga->item_size;
        void *dest = (char *) ga->ptrData + i * ga->item_size;

        // Copies the memory contents at the source location into the destination effectively moving the value into the new position
        memcpy(dest, src, ga->item_size);
    }
}

// Swaps two items in the array
static void swap(struct GenericArray *ga, void *val1, void *val2) { 

    // Declare and initialize a pointer to memory allocated for the temporary var
    void *temp = NULL;
    temp = malloc(ga->item_size);

    // Copy the raw memory pointed to by `val1` into the memory location pointed to by the `temp` pointer
    memcpy(temp, val1, ga->item_size);
    memcpy(val1, val2, ga->item_size);
    memcpy(val2, temp, ga->item_size);

    // Free the memory allocated for the temporary pointer
    free(temp);
}


