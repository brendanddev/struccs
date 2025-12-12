#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

/// heap.c
/// A generic implementation of a heap backed by an array
/// Brendan Dileo - December 12 2025


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


// Returns the current size (length) of the heap
int heap_size(struct Heap *heap) {
    return heap->length;
}

// Returns the capacity of the heap
int heap_capacity(struct Heap *heap) {
    return heap->capacity;
}

bool heap_isempty(struct Heap *heap);