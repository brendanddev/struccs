#include <stdio.h>

/// dynamic_array.h

/// Declares the DynamicArray struct and functions associated with the DynamicArray

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define INITIAL_CAPACITY 4

// Defines the DynamicArray struct and creates a type alias 'DynamicArray'
typedef struct DynamicArray {
    int *ptrData;       // Pointer to the data where the array will store its elements
    int length;         // The length of the array
    int capacity;       // The initial capacity of the array
} DynamicArray;


struct DynamicArray * _init();
void _add(struct DynamicArray *da, int element);
void _add_at(struct DynamicArray *da, int index, int element);
int _get(struct DynamicArray *da, int index);
void _remove_at(struct DynamicArray *da, int index);
void _remove(struct DynamicArray *da, int element);
void _remove_back(struct DynamicArray *da);
void _discard(struct DynamicArray *da);
int _size(struct DynamicArray *da);
int _capacity(struct DynamicArray *da);
void _print(struct DynamicArray *da);
void _status(struct DynamicArray *da);


#endif