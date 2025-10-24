#include <stdio.h>
#include "dynamic_array.h"

/// main.c


int main() {

    struct DynamicArray *da = _init();
    printf("\nInitial Capacity: %d", da->capacity);
    printf("\nInitial Length/Size: %d\n", da->length);

    _add(da, 100);
    _add(da, 13320);
    _add(da, 545);

    printf("\nCurrent Capacity: %d", da->capacity);
    printf("\nCurrent Length/Size: %d\n", da->length);

    _print(da);

    return 0;

}