#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H

/// generic_array.h
/// Brendan Dileo - November 3 2025


// Defines the GenericArray struct type
typedef struct GenericArray {
    void *ptrData;                  // Pointer to the memory where the array elements will be stored
    size_t item_size;               // The size of items stored in the array
    int capacity;
    int length;
} GenericArray;


struct GenericArray * _init(size_t item_size);
bool _append(struct GenericArray *ga, void *item_ptr);
bool _add(struct GenericArray *ga, int index, void *in_ptr);
bool _get(struct GenericArray *ga, int index, void *out_ptr);
bool _set(struct GenericArray *ga, int index, void *in_ptr);
bool _remove_last(struct GenericArray *ga);
bool _remove_at(struct GenericArray *ga, int index);
int _size(struct GenericArray *ga);
int _capacity(struct GenericArray *ga);
void _discard(struct GenericArray *ga);

#endif
