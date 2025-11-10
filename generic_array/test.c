#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// test.c
/// Temporary development/testing file to plan out the reverse() function for the GenericArray
/// Brendan Dileo, November 7


int main() {


    // Reverse Function - Reverse elements in-place

    int n = 5;
    int arr[5] = { 100, 63, 11, 99, 777 };

    // In order
    printf("Regular Order: \n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Reverse order
    printf("Reverse Order: \n");
    for (int i = n - 1; i >= 0; i--) printf("%d ", arr[i]);
    printf("\n");

    // int n_rev = 4;
    // int arr_rev[4];
    // int idx = 0;
    // for (int i = n_rev - 1; i >= 0; i--) {
    //     arr_rev[i] = arr[idx++];
    // }

    // printf("\nREVERSE ARRAY: \n");
    // for (int i = 0; i < n_rev; i++) printf("%d ", arr_rev[i]);


    // In place reverse

    printf("In place Reversal: \n");
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");




    return 0;
}