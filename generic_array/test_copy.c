#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/// test_copy.c
/// Source code for testing/developing the copy logic for the GenericArray
/// Brendan Dileo, November 10 2025



// - **Copy Function** - Deep/shallow copy of arrays
//   - Copy array structure and all elements
//   - Consider deep copy with custom copy function for complex types

// Ideas: 
// memcpy --> Copy the required number of bytes from the initial memory location to the new memory location?
int main() {

    // Initial array to be copied
    int n = 4;
    int arr[4] = { 100, 999, 56, 22 };      // allocated on stack

    printf("Initial Array: \n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Allocate new memory for the new array
    int *new_arr = NULL;
    new_arr = malloc(sizeof(int) * n);      // dynamically allocated on heap

    // Copy raw memory from the initial array to the copy of the array
    memcpy(new_arr, arr, sizeof(int) * n);

    printf("Copied Array Contents: \n");
    for (int i = 0; i < n; i++) printf("%d ", new_arr[i]);



    return 0;
}

