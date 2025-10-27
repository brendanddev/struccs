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

    // Remove (1)
    _remove_back(da);
    printf("AFTER REMOVE: \n");
    _print(da);

    // Remove (2)
    _remove_back(da);
    printf("AFTER REMOVE: \n");
    _print(da);

    printf("\nLength and Capacity After Removals: ");
    printf("\nCurrent Capacity: %d", da->capacity);
    printf("\nCurrent Length/Size: %d\n", da->length);


    // Add at
    _add_at(da, 3, 999);
    printf("\nAFTER ADD_AT AT INDEX 3: \n");
    _print(da);

    printf("\nLength and Capacity After Adding: ");
    printf("\nCurrent Capacity: %d", da->capacity);
    printf("\nCurrent Length/Size: %d\n", da->length);



    return 0;

}