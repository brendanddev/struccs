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
static void heapify_down(struct Heap *heap, int current_idx, int (*compare)(void*, void*));
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

    // Check if the heaps capacity has been reached - would resize here (TODO)
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

// Removes and returns the element currently located at the root (index=0)
bool heap_remove(struct Heap *heap, void *out, int (*compare)(void*, void*)) {
    if (heap_isempty(heap)) return false;

    // Copy the value being removed into the output pointer before removal
    memcpy(out, heap->elements, heap->element_size);

    // Compute index and pointer to the last element in memory
    int last_idx = heap->length - 1;
    void *last = heap->elements + last_idx * heap->element_size;

    // Replace the root element with the last element in the heap
    memcpy(heap->elements, last, heap->element_size);
    heap->length--;

    // Heapify down to maintain the max-heap property
    heapify_down(heap, heap->elements, compare);
    return true;
}

// Returns the value stored at the root of the heap (index=0)
void* heap_peek(struct Heap *heap) {
    return heap->elements;
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

// Prints the contents of the heap with no visualization
void heap_debug(struct Heap *heap, void (* print_fn)(void*)) {
    if (heap_isempty(heap)) return;

    for (int i = 0; i < heap->length; i++) {
        print_fn((char*) heap->elements + i * heap->element_size);
    }
}

// Public interface for printing the contents of the heap in tree-like structure
void heap_print(struct Heap *heap, void (* print_fn)(void*)) {
    if (heap_isempty(heap)) return;
    heap_print_rec(heap, print_fn, 0, 0);
}

// Recursive helper for printing the contents of the heap in a tree-like structure
static void heap_print_rec(struct Heap *heap, void (* print_fn)(void*), int index, int depth) {

    // Base case - stop if current index is out of bounds
    if (index >= heap->length) return;

    // Compute right child index and recurse down on the right side
    int right_idx = 2 * index + 2;
    heap_print_rec(heap, print_fn, right_idx, depth + 1); 

    // Print current node with indentation
    for (int i = 0; i < depth; i++) printf("    ");
    void *current_element = (char*) heap->elements + index * heap->element_size;
    print_fn(current_element); 
    printf("\n");

    // Compute left child index and recurse down on left side
    int left_child = 2 * index + 1;
    heap_print_rec(heap, print_fn, left_child, depth + 1); 
}

// Private helper functions, linkage limited to this file


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
        } else {
            break;
        }
    }
}

// Repeatedly compares the element at the provided index with its children, swapping with the larger child if it exists
// to maintain the max-heap property
static void heapify_down(struct Heap *heap, int current_idx, int (*compare)(void*, void*)) {

    // Declared to hold the larger index between the left and right children
    int max_child_idx;

    // Continue looping while there is atleast a left child (if no left child, there will be no right)
    // If the calculated index for the left child is less than the total length of the array, the left childs index points
    // to a valid memory slot inside the arrays boundaries that is currently occupied by a valid element, so the left child exists.
    // Otherwise the left index falls outside of the arrays bounds, and does not exist.
    while (2 * current_idx + 1 < heap->length) {

        // Compute left and right child indexes
        int left_idx = 2 * current_idx + 1;
        int right_idx = 2 * current_idx + 2;

        // Set max child index to left child by default since we know it exists
        max_child_idx = left_idx;

        // Check if the right child exists based on whether the calculated index is within valid bounds of the array
        if (right_idx < heap->length) {

            // Compute left and right child pointers now that we know both exist
            void *left_child = (char *) heap->elements + left_idx * heap->element_size;
            void *right_child = (char *) heap->elements + right_idx * heap->element_size;
            
            // Check if the right child is larger
            if (compare(right_child, left_child) > 0) {
                max_child_idx = right_idx;
            }
        }

        // Compute pointer to the current element and larger child element in memory
        void *current = (char *) heap->elements + current_idx * heap->element_size;
        void *max_child = (char *) heap->elements + max_child_idx * heap->element_size;

        // Check if the child is larger than the current element
        if (compare(max_child, current) > 0) {

            // Swap the current and max child and 
            // set current index to max child index to walk further down the heap
            heap_swap(heap, current_idx, max_child_idx);
        } else {
            // If child is not larger, max-heap property satisfied and we can exit
            break;
        }
    }
}


