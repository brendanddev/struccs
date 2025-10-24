#include <stdio.h>

/// dynamic_array.h

/// Declares the DynamicArray struct and functions associated with the DynamicArray

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// Defines the DynamicArray struct
struct DynamicArray {
    int *ptrData;       // Pointer to the data where the array will store its elements
    int length;         // The length of the array
    int capacity;       // The initial capacity of the array
};


struct DynamicArray * _init();
int _get(int index);
int _add(struct DynamicArray *da, int element);
int _remove(int element);
void _discard(struct DynamicArray);
void _print(struct DynamicArray *da);


#endif