
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


struct GenericArray * _init(size_t item_size);
bool _append(struct GenericArray *ga, void *item_ptr);
bool _add(struct GenericArray *ga, int index, void *in_ptr);
bool _get(struct GenericArray *ga, int index, void *out_ptr);
bool _set(struct GenericArray *ga, int index, void *in_ptr);
bool _remove_last(struct GenericArray *ga);
bool _remove_at(struct GenericArray *ga, int index);
bool _contains(struct GenericArray *ga, bool (*funcptr)(void*, void*), void *trgtptr);
bool _clear(struct GenericArray *ga);
int _size(struct GenericArray *ga);
int _capacity(struct GenericArray *ga);
double _usage(struct GenericArray *ga);
void _discard(struct GenericArray *ga);
void _print(struct GenericArray *ga);


void _sort(struct GenericArray *ga, bool (* comparator)(void*, void*));
void _swap(struct GenericArray *ga, void *val1, void *val2);

#endif