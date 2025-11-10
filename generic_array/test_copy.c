#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generic_array.h"


/// test_copy.c
/// Source code for testing/developing the copy logic for the GenericArray
/// Brendan Dileo, November 10 2025



// Copy Function: Deep copy of GenericArrays
// For a deep copy, memory needs to be allocated for the copy of the struct itself, but also memory for the data it points to

// Ideas: 
// memcpy --> Copy the required number of bytes from the initial memory location to the new memory location?
int main() {

    // Initialize a GenericArray to hold integers, populate, and print initial state
    int n = 5;
    struct GenericArray *ga = _init(sizeof(int));
    for (int i = 0; i < n; i++) _append(ga, &i);
    printf("Initial Array: \n");
    for (int i = 0; i < n; i++) printf("[%d] ", *(int *)((char *)ga->ptrData + i * ga->item_size));
    printf("\n");

    printf("Initial Memory Addresses: \n");
    printf("GenericArray (struct): %p\nInternal Array: %p\n", ga, ga->ptrData);

    // Allocate new memory for the copy of the array
    void *new_ga_ptrData = NULL;
    new_ga_ptrData = malloc(ga->item_size * ga->capacity);

    // Allocate new memory for the copy of the struct (GenericArray)
    struct GenericArray *new_ga = NULL;
    new_ga = malloc(sizeof(struct GenericArray));

    // Copy raw memory from the original struct to the copy
    memcpy(new_ga, ga, sizeof(struct GenericArray));

    // Copy raw memory from the original array pointed to, to the copy
    memcpy(new_ga_ptrData, ga->ptrData, ga->item_size * ga->length);

    new_ga->ptrData = new_ga_ptrData;
    // ga->ptrData = new_ga_ptrData;

    printf("Copied Array: \n");
    for (int i = 0; i < n; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * ga->item_size));
    _reverse(new_ga);
    printf("\n");
    for (int i = 0; i < n; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * ga->item_size));

    printf("\nCopied Memory Addresses: \n");
    printf("GenericArray (struct): %p\nInternal Array: %p\n", new_ga, new_ga->ptrData);

    // Free the original GenericArray that has been copied
    _discard(ga);
    ga = NULL;

    // Should still be able to access/operate on the copy
    printf("\nREVERSING COPY: \n");
    _reverse(new_ga);
    for (int i = 0; i < new_ga->length; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * new_ga->item_size));
    printf("\n");

    printf("Removing Last Element: \n");
    _remove_last(new_ga);
    for (int i = 0; i < new_ga->length; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * new_ga->item_size));
    printf("\n");




    // Free allocated memory
    free(new_ga);
    new_ga = NULL;



    return 0;
}

