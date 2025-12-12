
/// heap.h
/// Header for the generic heap implementation backed by an array
/// Brendan Dileo - December 12 2025


#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines the Heap (max heap) struct type
typedef struct Heap {
    void *elements;             // Pointer to an array in memory where the heaps elements will be stored
    size_t element_size;        // The size in bytes of each element stored in the heap
    int capacity;               // The capacity of the heap
    int length;                 // The length of the heap
} Heap;


struct Heap* heap_create(size_t element_size);
int heap_size(struct Heap *heap);
int heap_capacity(struct Heap *heap);
bool heap_isempty(struct Heap *heap);

void heap_insert(struct Heap *heap, void *value, size_t vsize);
void heap_remove(struct Heap *heap, void *value, size_t vsize);
void* heap_peek(struct Heap *heap);

void heap_print(struct Heap *heap);
void heap_clear(struct Heap *heap);
void heap_discard(struct Heap *heap);


#endif