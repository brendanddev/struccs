#include <stdio.h>

#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H

/// generic_array.h

typedef struct GenericArray {
    void *ptrData;
    int capacity;
    int length;
    size_t item_size;
} GenericArray;


struct GenericArray * _init();
void _add(struct GenericArray *ga);
void _get(struct GenericArray *ga);
void _remove(struct GenericArray *ga);
void _discard(struct GenericArray *ga);


#endif