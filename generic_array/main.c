#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"


/// main.c

int main() {

    struct GenericArray *ga = _init(sizeof(int));
    printf("Capacity: %d, Length: %d, Item Size: %d\n", ga->capacity, ga->length, ga->item_size);


    return 0;
}