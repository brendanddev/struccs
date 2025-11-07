#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/// sort.c
/// Designated development and testing file
/// Brendan Dileo, November 7 2025




// Swaps two elements in an array
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


    void *ptr = NULL;
    ptr = malloc(sizeof(int) * 5);
    printf("%p\n", ptr);

    void *first = (char *) ptr + 0 * sizeof(int);
    printf("%p\n", first);

    void *scnd = (char *) ptr + 1 * sizeof(int);
    printf("%p\n", scnd);

    void *thrd = (char *) ptr + 2 * sizeof(int);
    printf("%p\n", thrd);

    void *frth = (char *) ptr + 3 * sizeof(int);
    printf("%p\n", frth);

    void *ffth = (char *) ptr + 4 * sizeof(int);
    printf("%p\n", ffth);

    void *sth = (char *) ptr + 5 * sizeof(int);
    printf("%p\n", sth);

    void *svnth = (char *) ptr + 6 * sizeof(int);
    printf("%p\n", svnth);



    int num = 100;
    void *item = &num;                  // Point the void pointer to the address of `num`
    memcpy(first, item, sizeof(int));   // Copy the contents of the value in memory pointed to by `item` into `first`

    printf("%d ", * (int *) first);
    printf("%d ", * (int *) scnd);

    return 0;

}
