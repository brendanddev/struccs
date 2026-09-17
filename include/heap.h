// heap.h
// Header for the generic heap implementation backed by an array.
// Brendan Dileo - 2025

#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Array-backed binary heap. Ordering is whatever the compare callback passed to
// insert/remove defines, pass a max-first comparator for a max-heap.
typedef struct Heap {
    void *elements;
    size_t element_size;
    int capacity;
    int length;
} Heap;


// Allocates an empty heap for elements of element_size bytes. Caller frees with
// heap_discard. Returns NULL on allocation failure.
struct Heap* heap_create(size_t element_size);
// Copies vsize bytes from value into the heap and sifts it up. vsize is expected
// to equal element_size. Returns false only if a needed resize fails.
bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*));
// Copies the root element into out, moves the last element to the root and sifts
// it down. Returns false if the heap is empty.
bool heap_remove(struct Heap *heap, void *out, int (*compare)(void*, void*));
// Returns a borrowed pointer to the root element (no bounds check - do not call
// on an empty heap).
void* heap_peek(struct Heap *heap);
// Returns the number of elements in the heap.
int heap_size(const struct Heap *heap);
// Returns the current capacity of the backing array.
int heap_capacity(const struct Heap *heap);
// Returns true if the heap has no elements.
bool heap_isempty(const struct Heap *heap);
// Resets length to 0; the backing array is kept.
void heap_clear(struct Heap *heap);
// Frees the backing array and the heap struct.
void heap_discard(struct Heap *heap);
// Applies print_fn to each element in array order (no tree layout).
void heap_debug(struct Heap *heap, void (* print_fn)(void*));
// Prints the heap rotated onto its side (root flush left, depth by indent).
void heap_print(struct Heap *heap, void (* print_fn)(void*));

#endif
