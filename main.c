#include <stdio.h>
#include "dynamic_array.h"

/// main.c


int main() {

    struct DynamicArray *da = _init();

    for (int i = 0; i <= 10; i++) {
        printf("\nInitial Capacity: %d", da->capacity);
        printf("\nInitial Length/Size: %d\n", da->length);
        _add(da, i);
    }

    _print(da);

    return 0;

}