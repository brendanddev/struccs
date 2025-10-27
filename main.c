#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

/// main.c


int main() {

    struct DynamicArray *da = _init();
    _status(da);

    for (int i = 0; i <= 1000; i++) {
        int r = rand();     // Generate a random value to add
        _add(da, r);
        // _status(da);
    }


    for (int i = 0; i < 750; i++) {
        _remove_back(da);
    }

    _status(da);


    for (int i = 0; i < 150; i++) {
        _remove_back(da);
    }

    _status(da);

    // printf("GET: %d\n", _get(da, 4));
    // printf("BEFORE REMOVE: \n");
    // _print(da);

    // // Remove (1)
    // _remove_back(da);
    // printf("AFTER REMOVE: \n");
    // _print(da);

    // // Remove (2)
    // _remove_back(da);
    // printf("AFTER REMOVE: \n");
    // _print(da);

    // printf("\nLength and Capacity After Removals: ");
    // _status(da);


    // // Add at
    // _add_at(da, 3, 999);
    // printf("\nAFTER ADD_AT AT INDEX 3: \n");
    // _print(da);

    // printf("\nLength and Capacity After Adding: ");
    // _status(da);


    // // Remove at
    // printf("\nElement at Index 4: %d\n", _get(da, 4));
    // printf("REMOVING AT: INDEX 4\n");
    // _remove_at(da, 4);
    // printf("AFTER REMOVE AT: \n");
    // _print(da);


    // // Remove element
    // printf("\nREMOVING ELEMENT: 999\n");
    // _remove(da, 999);
    // printf("AFTER REMOVING ELEMENT 999: \n");
    // _print(da);

    _discard(da);


    return 0;

}