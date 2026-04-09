/**
 * test_heap.c
 * The test suite for the Heap implementation
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

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
    struct Heap *heap = heap_create(sizeof(int));
    printf("Created Heap - Capacity: %d, Length: %d, Is Empty: %d\n", heap_capacity(heap), heap_size(heap), heap_isempty(heap));

    for (int i = 0; i < 25; i++) {
        int num = i;
        heap_insert(heap, &num, sizeof(int), compare_int);
    }
    printf("Current Heap - Capacity: %d, Length: %d, Is Empty: %d\n", heap_capacity(heap), heap_size(heap), heap_isempty(heap));
    printf("Peeked value: %d\n", *(int*) heap->elements);
    heap_debug(heap, print_int);
    heap_print(heap, print_int);

    int value;
    if (heap_remove(heap, &value, compare_int)) {
        printf("Removed the value: %d from the heap\n", value);
    } else {
        printf("Failed to remove the value from the heap\n");
    }

    printf("Current Heap - Capacity: %d, Length: %d, Is Empty: %d\n", heap_capacity(heap), heap_size(heap), heap_isempty(heap));

    heap_debug(heap, print_int);
    heap_print(heap, print_int);

    if (heap_remove(heap, &value, compare_int)) {
        printf("Removed the value: %d from the heap\n", value);
    } else {
        printf("Failed to remove the value from the heap\n");
    }

    heap_debug(heap, print_int);
    heap_print(heap, print_int);

    heap_discard(heap);
    heap = NULL;
    return 0;
}
