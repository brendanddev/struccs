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

    printf("Copied Array: \n");
    for (int i = 0; i < n; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * ga->item_size));
    _reverse(new_ga);
    printf("\n");
    for (int i = 0; i < n; i++) printf("[%d] ", *(int *)((char *) new_ga->ptrData + i * ga->item_size));

    printf("Copied Memory Addresses: \n");
    printf("GenericArray (struct): %p\nInternal Array: %p\n", new_ga, new_ga->ptrData);


    // Output:

    // Initial Array: 
    // Initial Memory Addresses: 
    // GenericArray (struct): 0x144605f60
    // Internal Array: 0x144605ee0

    // Copied Array: 
    // Copied Memory Addresses: 
    // GenericArray (struct): 0x144606060
    // Internal Array: 0x144605ee0

    // Issue: Internal array still points to the same address in memory



    // Free allocated memory
    _discard(ga);
    ga = NULL;
    free(new_ga);
    new_ga = NULL;


    // // Initial array to be copied
    // int n = 4;
    // int arr[4] = { 100, 999, 56, 22 };      // allocated on stack

    // printf("Initial Array: \n");
    // for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    // printf("\n");

    // // Allocate new memory for the new array
    // int *new_arr = NULL;
    // new_arr = malloc(sizeof(int) * n);      // dynamically allocated on heap

    // // Copy raw memory from the initial array to the copy of the array
    // memcpy(new_arr, arr, sizeof(int) * n);

    // printf("Copied Array Contents: \n");
    // for (int i = 0; i < n; i++) printf("%d ", new_arr[i]);



    return 0;
}

