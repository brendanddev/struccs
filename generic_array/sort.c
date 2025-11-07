#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/// sort.c
/// Designated development and testing file
/// Brendan Dileo, November 7 2025



// // Swaps two elements in an array
void _swap(int *num1, int *num2) {
    int temp = *num1;       // Store the value pointed to by the `num1` pointer into `temp`
    *num1 = *num2;          // Store the value pointed to by the `num2` pointer at the memory location pointed to by `num1`
    *num2 = temp;           // Store the temp variable back into the memory location pointed to by `num2`
}

// Basic Bubble Sort implementation for an array of integers
void _sort(int arr[], int n) {
    bool is_swapped;

    for (int i = 0; i < n; i++) {
        is_swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                _swap(&arr[j], &arr[j + 1]);
                is_swapped = true;
            }
        }

        if (is_swapped == false) {
            break;
        }
    }
}


// Bubble Sort implementation for an array of integers with a 
// caller defined comparator function to determine how to order elements
void _sort_cmp(int arr[], int n, bool (* comparator)(int, int)) {

    bool is_swapped;
    for (int i = 0; i < n; i++) {
        is_swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (comparator(arr[j], arr[j + 1])) {
                _swap(&arr[j], &arr[j + 1]);
                is_swapped = true;
            }
        }
        if (is_swapped == false) {
            break;
        }
    }
}

// Comparator func
bool largest_first(int a, int b) {
    if (b > a) return true;
    return false;
}


int main() {

    int n = 10;
    int arr[10] = { 9, 76, 899, 155, 9075, 10200, 28475, 8342, 22, 100 };
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Basic sort
    _sort(arr, n);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    // Sort with comparator function
    _sort_cmp(arr, n, largest_first);
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");


    return 0;

}