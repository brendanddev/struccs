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

bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*)) {
    return false;
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