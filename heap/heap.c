#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

/// heap.c
/// A generic implementation of a heap backed by an array
/// Brendan Dileo - December 12 2025


// Prototypes
static void heap_swap(void *a, void *b, size_t element_size);


// Creates a new max heap
struct Heap* heap_create(size_t element_size) {

    // Allocate memory for the heap itself and handle allocation failure
    struct Heap *heap = malloc(sizeof(struct Heap));
    if (heap == NULL) return NULL;

    // Set initial capacity, length, and size of elements stored in the heap
    heap->capacity = 8;
    heap->length = 0;
    heap->element_size = element_size;

    // Allocate memory for the heaps internal array and handle allocation failure
    heap->elements = malloc(heap->element_size * heap->capacity);
    if (heap->elements == NULL) {
        free(heap);
        return NULL;
    }

    return heap;
}

// Inserts a new value into the heap
bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*)) {
    
    // If the heap is empty, insert the value into the root
    if (heap_isempty(heap)) {
        memcpy(heap->elements, value, vsize);
        heap->length++;
        return true;
    }

    // Compute the destination pointer and store the index of the element being inserted
    void* current = (char *) heap->elements + heap->length * heap->element_size;
    int current_idx = heap->length;

    // Copy the new element into the array
    memcpy(current, value, vsize);
    heap->length++;

    // Walk up the heap to ensure max-heap property is maintained
    while (current_idx > 0) {

        // Compute parent index and pointer to the parent element
        int parent_idx = (current_idx - 1) / 2;
        void *parent = (char *) heap->elements + parent_idx * heap->element_size;

        // Check if the current value is larger than the parent value
        if (compare(current, parent) > 0) {

            // Swap them to maintain max-heap property and
            // set the current index to the parent index so the heap continues to walk up from the parent,
            // which is now the element that was just inserted
            heap_swap(current, parent, heap->element_size);
            current_idx = parent_idx;
        } else {
            // If child inserted is less than the parent value, we can assume the max-heap property is valid
            break;
        }
    }
    return true;
}

// Returns the value stored at the root of the heap
void* heap_peek(struct Heap *heap) {
    if (heap_isempty(heap)) return NULL;
    return (char *) heap->elements;
}


// Returns the current size (length) of the heap
int heap_size(struct Heap *heap) {
    return heap->length;
}

// Returns the capacity of the heap
int heap_capacity(struct Heap *heap) {
    return heap->capacity;
}

// Checks whether the heap is empty
bool heap_isempty(struct Heap *heap) {
    return heap->length == 0;
}

// Clears the contents of the heap
void heap_clear(struct Heap *heap) {
    if (heap != NULL) {
        heap->length = 0;
    }
}

// Frees the memory previously allocated by the heap
void heap_discard(struct Heap *heap) {
    if (heap != NULL) {
        free(heap->elements);
        free(heap);
    }
}

// Prints the contents of the heap
void heap_debug(struct Heap *heap, void (* print_fn)(void*)) {
    for (int i = 0; i < heap->length; i++) {
        print_fn((char *) heap->elements + i * heap->element_size);
    }
}


// Private helper functions, linkage limited to this file


// Swaps the positions of two elements in the heap
static void heap_swap(void *a, void *b, size_t element_size) {

    // Temporarily allocate a block of memory to hold the value being swapped,
    // swap the contents in memory pointed to by the two pointers to swap the
    // values stored in memory, and free the temporary memory allocated
    void *temp = malloc(element_size);
    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);
    free(temp);
}