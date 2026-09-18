// heap.c
// A generic implementation of a heap backed by an array
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

// Prototypes
static bool heap_resize(struct Heap *heap);
static void heap_swap(void *a, void *b, size_t element_size);
static void heapify_up(struct Heap *heap, int current_idx, int (*compare)(const void*, const void*));
static void heapify_down(struct Heap *heap, int current_idx, int (*compare)(const void*, const void*));
static void heap_print_rec(const struct Heap *heap, void (* print_fn)(const void*), int index, int depth);

struct Heap* heap_create(size_t element_size) {
    struct Heap *heap = malloc(sizeof(struct Heap));
    if (heap == NULL) return NULL;

    heap->capacity = 8;
    heap->length = 0;
    heap->element_size = element_size;

    heap->elements = malloc(heap->element_size * heap->capacity);
    if (heap->elements == NULL) {
        free(heap);
        return NULL;
    }

    return heap;
}

bool heap_insert(struct Heap *heap, const void *value, size_t vsize, int (*compare)(const void*, const void*)) {
    if (heap->length >= heap->capacity) {
        if (!heap_resize(heap)) return false;
    }

    // vsize is trusted to equal heap->element_size.
    memcpy((char*) heap->elements + heap->length * heap->element_size, value, vsize);
    heap->length++;

    // New element sits at the end of the array; sift it up into place.
    int current_idx = heap->length - 1;
    heapify_up(heap, current_idx, compare);
    return true;
}

bool heap_remove(struct Heap *heap, void *out, int (*compare)(const void*, const void*)) {
    if (heap_isempty(heap)) return false;

    // Hand back the root before it is overwritten.
    memcpy(out, heap->elements, heap->element_size);

    int last_idx = heap->length - 1;
    void *last = (char *) heap->elements + last_idx * heap->element_size;

    // Promote the last element to the root, then sift it down.
    memcpy(heap->elements, last, heap->element_size);
    heap->length--;

    heapify_down(heap, 0, compare);
    return true;
}

void* heap_peek(const struct Heap *heap) {
    return heap->elements;
}

int heap_size(const struct Heap *heap) {
    return heap->length;
}

int heap_capacity(const struct Heap *heap) {
    return heap->capacity;
}

bool heap_isempty(const struct Heap *heap) {
    return heap->length == 0;
}

void heap_clear(struct Heap *heap) {
    // Length only; the backing array stays allocated and gets overwritten.
    heap->length = 0;
}

void heap_discard(struct Heap *heap) {
    if (heap != NULL) {
        free(heap->elements);
        free(heap);
    }
}

void heap_debug(const struct Heap *heap, void (* print_fn)(const void*)) {
    if (heap_isempty(heap)) return;

    for (int i = 0; i < heap->length; i++) {
        print_fn((char*) heap->elements + i * heap->element_size);
    }
}

void heap_print(const struct Heap *heap, void (* print_fn)(const void*)) {
    if (heap_isempty(heap)) return;
    heap_print_rec(heap, print_fn, 0, 0);
}


// Private helper functions - linkage limited to this file


static void heap_print_rec(const struct Heap *heap, void (* print_fn)(const void*), int index, int depth) {
    if (index >= heap->length) return;

    // Right subtree, then node, then left subtree: prints the heap on its side
    // with the root flush left.
    int right_idx = 2 * index + 2;
    heap_print_rec(heap, print_fn, right_idx, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");
    void *current_element = (char*) heap->elements + index * heap->element_size;
    print_fn(current_element);
    printf("\n");

    int left_child = 2 * index + 1;
    heap_print_rec(heap, print_fn, left_child, depth + 1);
}

// Doubles the backing array. Returns false if realloc fails (heap unchanged).
static bool heap_resize(struct Heap *heap) {
    int new_capacity = heap->capacity * 2;
    void *new_elements = realloc(heap->elements, new_capacity * heap->element_size);
    if (new_elements == NULL) return false;

    heap->capacity = new_capacity;
    heap->elements = new_elements;
    return true;
}

// Byte-wise swap of two element_size-byte elements.
static void heap_swap(void *a, void *b, size_t element_size) {
    void *temp = malloc(element_size);
    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);

    free(temp);
    temp = NULL;
}

// Sift up: while this element outranks its parent by compare(), swap them and
// keep walking toward the root.
static void heapify_up(struct Heap *heap, int current_idx, int (*compare)(const void*, const void*)) {
    while (current_idx > 0) {
        void *current = (char*) heap->elements + current_idx * heap->element_size;
        int parent_idx = (current_idx - 1) / 2;
        void *parent = (char*) heap->elements + parent_idx * heap->element_size;

        if (compare(current, parent) > 0) {
            heap_swap(current, parent, heap->element_size);
            current_idx = parent_idx;
            current = parent;
        } else {
            break;
        }
    }
}

// Sift down: repeatedly swap with the higher-ranked child until neither child
// outranks this element.
static void heapify_down(struct Heap *heap, int current_idx, int (*compare)(const void*, const void*)) {
    int max_child_idx;

    // Loop as long as a left child is in bounds (no left child => no right child).
    while (2 * current_idx + 1 < heap->length) {

        int left_idx = 2 * current_idx + 1;
        int right_idx = 2 * current_idx + 2;

        // Left child is known to exist; prefer the right one only if it also
        // exists and outranks the left.
        max_child_idx = left_idx;

        if (right_idx < heap->length) {
            void *left_child = (char *) heap->elements + left_idx * heap->element_size;
            void *right_child = (char *) heap->elements + right_idx * heap->element_size;

            if (compare(right_child, left_child) > 0) {
                max_child_idx = right_idx;
            }
        }

        void *current = (char *) heap->elements + current_idx * heap->element_size;
        void *max_child = (char *) heap->elements + max_child_idx * heap->element_size;

        if (compare(max_child, current) > 0) {
            heap_swap(current, max_child, heap->element_size);
            current_idx = max_child_idx;
        } else {
            // Neither child outranks current: heap order is restored.
            break;
        }
    }
}
