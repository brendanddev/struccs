#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"


/// main.c
/// Brendan Dileo - November 3 2025

void _print(struct GenericArray *ga);

int main() {

    struct GenericArray *ga = _init(sizeof(int));
    printf("Capacity: %d, Length: %d, Item Size: %zu bytes\n", ga->capacity, ga->length, ga->item_size);

    int num = 100;
    void *ptr = &num;
    _append(ga, ptr);
    printf("Capacity: %d, Length: %d, Item Size: %zu bytes\n", ga->capacity, ga->length, ga->item_size);

    int num2 = 200;
    void *ptr2 = &num2;
    _append(ga, ptr2);
    
    int num3 = 300;
    void *ptr3 = &num3;
    _append(ga, ptr3);

    printf("Capacity: %d, Length: %d, Item Size: %zu bytes\n", ga->capacity, ga->length, ga->item_size);

    _print(ga);

    _discard(ga);
    ga = NULL;
    return 0;
}



void _print(struct GenericArray *ga) {
    for (int i = 0; i < ga->length; i++) {
        printf("[%d] - %d\n", i, *(int *)((char *)ga->ptrData + i * ga->item_size));
    }
}