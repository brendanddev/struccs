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