#include <stdio.h>
#include "dynamic_array.h"

/// main.c


int main() {

    struct DynamicArray *da = _init();
    printf("\nInitial Capacity: %d", da->capacity);
    printf("\nInitial Length/Size: %d\n", da->length);

    for (int i = 0; i <= 10; i++) {
        _add(da, i);
        printf("\nCurrent Capacity: %d", da->capacity);
        printf("\nCurrent Length/Size: %d\n", da->length);
    }

    printf("GET: %d\n", _get(da, 4));
    printf("BEFORE REMOVE: \n");
    _print(da);

    _remove_back(da);

    printf("AFTER REMOVE: \n");
    _print(da);


    return 0;

}