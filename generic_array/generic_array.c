#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generic_array.h"


/// generic_array.c
/// Brendan Dileo - November 3 2025


struct GenericArray * _init(size_t item_size) {

    // Allocate memory for the struct
    struct GenericArray *ga = NULL;
    ga = malloc(sizeof(struct GenericArray));

    // Handle allocation failure
    if (ga == NULL) {
        fprintf(stderr, "Memory allocation failed during initialization.\n");
        exit(EXIT_FAILURE);
    }

    ga->capacity = 4;
    ga->length = 0;
    ga->item_size = item_size;

    // Allocate memory for the internal array
    int *pTmp = malloc(item_size * ga->capacity);
    if (pTmp == NULL) {
        printf(stderr, "Memory allocation failed for internal array.\n");
        free(ga);               // Free previously allocated struct to avoid memory leak
        exit(EXIT_FAILURE);
    }

    ga->ptrData = pTmp;
    return ga;
}



bool _append(struct GenericArray *ga, void *itemPtr) { 
    void *dest = (char *)ga->ptrData + ga->length * ga->item_size;
    memcpy(dest, itemPtr, ga->item_size);
    ga->length++;
}