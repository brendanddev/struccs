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
static void heapify_up(int index);
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

// Insertion - O(log n) Time and O(n) Space

// Insertion in a Max-Heap involves the following steps:

//     Add the new element to the end of the heap, in the next available position in the last level of the tree.
//     Compare the new element with its parent. If the parent is smaller than the new element, swap them.
//     Repeat step 2 until the parent is greater than or equal to the new element, or until the new element reaches the root of the tree.


// Add a new element to the end of the heap, in the next available position in the last level of the tree.
// Compare the new element with its parent. If the parent is smaller than the new element, swap them.
// Repeat step 2 until the parent is greater than or equal to the new element, or until the new element reaches the root of the tree.

bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*)) {

    // Heap is empty, can insert at root
    if (heap_isempty(heap)) {
        // Copy raw bytes in memory from the input pointer into the memory at the base address of the array
        // to insert at first index
        memcpy(heap->elements, value, vsize);
        heap->length++;
        return true;
    }

    // If the heap is not empty, copy the value into the array and increment length
    memcpy((char*) heap->elements + heap->length * heap->capacity, value, vsize);
    heap->length++;

    // Compute the index of the newly inserted element and pointer to the element in memory
    int current_idx = heap->length - 1;
    void *current = (char*) heap->elements + current_idx * heap->element_size;

    // Compute parent index and pointer to the parent element in memory
    int parent_idx = (heap->length - 1) / 2;
    void *parent = (char*) heap->elements + parent_idx * heap->element_size;
    
    // Compare the newly added element with parent to see if parent is smaller
    if (compare(current, parent) > 0) {

        // If parent is smaller, swap the current value with parent to maintain max heap property
        // and set the current index to the parent to continue heapifying up
        heap_swap(current, parent, heap->element_size);
        current_idx = parent_idx;
    }

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
        print_fn((char*) heap->elements + i * heap->capacity);
    }
}