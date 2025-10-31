#include <stdio.h>
#include <stdlib.h>

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/// dynamic_array.h

// Defines the struct DynamicArray
typedef struct DynamicArray {
    int *ptrData;               // A pointer to the memory where the array elements will be stored
    int capacity;               // The capacity of the array
    int length;                 // The length of the array
    size_t item_size;           // The size of the items stored in the array    (not needed rn)
} DynamicArray;

struct DynamicArray * _init();
void _add(struct DynamicArray *da, int item, int index);
void _append(struct DynamicArray *da, int item);

int _get(struct DynamicArray *da, int index);

void _remove_last(struct DynamicArray *da);
void _remove_at(struct DynamicArray *da, int index);
void _remove(struct DynamicArray *da, int item);

void _discard(struct DynamicArray *da);
void _print(struct DynamicArray *da);

#endif