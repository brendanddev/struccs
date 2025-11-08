#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// test.c
/// Temporary development/testing file to plan out the reverse() function for the GenericArray
/// Brendan Dileo, November 7


int main() {


    // Reverse Function - Reverse elements in-place

    int n = 4;
    int arr[4] = { 100, 63, 11, 99 };

    // In order
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Reverse order
    for (int i = n - 1; i >= 0; i--) printf("%d ", arr[i]);

    int n_rev = 4;
    int arr_rev[4];
    int idx = 0;
    for (int i = n_rev - 1; i >= 0; i--) {
        arr_rev[i] = arr[idx++];
    }

    printf("\nREVERSE ARRAY: \n");
    for (int i = 0; i < n_rev; i++) printf("%d ", arr_rev[i]);



    return 0;
}