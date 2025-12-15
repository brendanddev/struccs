#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../heap/heap.h"


/// test_heap.c
/// The test suite for the Heap implementation
/// Brendan Dileo, December 12 2025


void print_int(void *value) {
    printf("%d\n", * (int *) value);
}

int compare_int(void *a, void *b) {
    int num1 = * (int *)a;
    int num2 = * (int *)b;

    if (num1 == num2) {
        return 0;
    } else if (num1 > num2) {
        return 1;
    } else {
        return -1;
    }
}


int main() {

    // Create new heap to store integers
    struct Heap *heap = heap_create(sizeof(int));
    printf("Created Heap - Capacity: %d, Length: %d, Is Empty: %d\n", heap_capacity(heap), heap_size(heap), heap_isempty(heap));

    return 0;
}
