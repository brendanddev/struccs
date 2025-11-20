
/// generic_array.h
/// Brendan Dileo - November 3 2025


#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H
#define SHRINK_THRESHOLD 5.0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Defines the GenericArray struct type
typedef struct GenericArray {
    void *ptrData;                  // Pointer to the memory where the array elements will be stored
    size_t item_size;               // The size of items stored in the array
    int capacity;                   // The current capacity of the internal array
    int initial_capacity;           // The initial capacity
    int length;                     // The length of the internal array
} GenericArray;


struct GenericArray* ga_init(size_t item_size);
bool ga_append(struct GenericArray *ga, void *item_ptr);
bool ga_add(struct GenericArray *ga, int index, void *in_ptr);
bool ga_get(struct GenericArray *ga, int index, void *out_ptr);
bool ga_set(struct GenericArray *ga, int index, void *in_ptr);
int ga_find(struct GenericArray *ga, void *item_ptr, bool (* comparator)(void*, void*));
bool ga_remove_last(struct GenericArray *ga);
bool ga_remove_at(struct GenericArray *ga, int index);
bool ga_contains(struct GenericArray *ga, bool (*funcptr)(void*, void*), void *trgtptr);
bool ga_clear(struct GenericArray *ga);
int ga_size(struct GenericArray *ga);
int ga_capacity(struct GenericArray *ga);
double ga_usage(struct GenericArray *ga);
void ga_discard(struct GenericArray *ga);
void ga_print(struct GenericArray *ga, void (* print_fn)(void*));
void ga_sort(struct GenericArray *ga, bool (* comparator)(void*, void*));
void ga_reverse(struct GenericArray *ga);
struct GenericArray* ga_copy(struct GenericArray *ga);
bool ga_binary_find(struct GenericArray *ga, void *item_ptr, int (* comparator)(void*, void*));

#endif