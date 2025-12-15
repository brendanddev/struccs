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
static void heapify_up(struct Heap *heap, int current_idx, int (*compare)(void*, void*));
static void heapify_down(int index);
static void heap_print_rec(struct Heap *heap, void (* print_fn)(void*), int index, int depth);



// Creates a new empty heap storing elements of the provided size
struct Heap* heap_create(size_t element_size) {

    // Initialize a pointer to the address of the memory allocated for the heap struct
    // and handle allocation failure
    struct Heap *heap = malloc(sizeof(struct Heap));
    if (heap == NULL) return NULL;

    // Set initial capacity, length, and size of elements that the heap will store
    heap->capacity = 8;
    heap->length = 0;
    heap->element_size = element_size;

    // Initialize a pointer to the address of the memory allocated for the values
    // to be stored in the heap, and handle allocation failure
    heap->elements = malloc(heap->element_size * heap->capacity);
    if (heap->elements == NULL) {
        free(heap);
        return NULL;
    }

    return heap;
}

// Inserts a new element at the next available position in the last level of the heaps underlying tree
bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*)) {

    // Check if the heaps capacity has been reached - would resize here
    if (heap->length >= heap->capacity) {
        return false;
    }

    // Copy the value into the array and increment length to insert the element
    memcpy((char*) heap->elements + heap->length * heap->element_size, value, vsize);
    heap->length++;

    // Compute the index of the newly inserted element and heapify up to maintain max heap
    int current_idx = heap->length - 1;
    heapify_up(heap, current_idx, compare);
    return true;
}

void heap_remove(struct Heap *heap, int index, int (*compare)(void*, void*)) {
}

// Returns the value stored at the root of the heap (index=0)
void* heap_peek(struct Heap *heap) {
    return NULL;
}

// Returns the size (length) of the heap
int heap_size(struct Heap *heap) {
    return heap->length;
}

// Returns the current capacity of the heap
int heap_capacity(struct Heap *heap) {
    return heap->capacity;
}

// Checks whether the heap is empty or not
bool heap_isempty(struct Heap *heap) {
    return heap->length == 0;
}

// Clears the contents of the heap (meory remains allocated to be overwritten)
void heap_clear(struct Heap *heap) {
    heap->length = 0;
}

// Frees the memory block previously allocated for the heap
void heap_discard(struct Heap *heap) {
    if (heap != NULL) {
        free(heap->elements);
        free(heap);
    }
}

// Prints the contents of the heap
void heap_debug(struct Heap *heap, void (* print_fn)(void*)) {
    if (heap_isempty(heap)) return;

    for (int i = 0; i < heap->length - 1; i++) {
        print_fn((char*) heap->elements + i * heap->element_size);
    }
}


// Private helper functions, linkage limited to this file


// Repeatedly compares the element at the provided index with its parent, swapping if the parent is smaller to maintain
// the max heap property
static void heapify_up(struct Heap *heap, int current_idx, int (*compare)(void*, void*)) {
    
    // Continue moving up the heap until we reach the root
    while (current_idx > 0) {

        // Compute the pointer to the element at the current index, the parent index,
        // and the pointer to the parent element in memory
        void *current = (char*) heap->elements + current_idx * heap->element_size;
        int parent_idx = (current_idx - 1) / 2;
        void *parent = (char*) heap->elements + parent_idx * heap->element_size;
        
        // Compare the newly added element with parent to see if parent is smaller
        if (compare(current, parent) > 0) {
            // If parent is smaller, swap the current value with parent to maintain max heap property
            // and advance current index and current pointer to continue walking up the heap
            heap_swap(current, parent, heap->element_size);
            current_idx = parent_idx;
            current = parent;
        }
    }
}

// Swaps the raw bytes between two memory locations to swap the values stored in two variables
static void heap_swap(void *a, void *b, size_t element_size) {

    // Allocate memory to temporarily store the memory of the value being swapped
    // and copy value into it
    void *temp = malloc(element_size);
    memcpy(temp, a, element_size);

    // Copy contents from `b` into `a`
    memcpy(a, b, element_size); 

    // Copy contents from `temp` into `b`
    memcpy(b, temp, element_size);

    // Free memory used by the memory allocated for the temporary
    free(temp);
    temp = NULL;
}