#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"


/// main.c


int main() {

    struct DynamicArray *da = _init();

    // This will currently produce an error: zsh: segmentation fault  ./out
    // This is due to the fact that the DynamicArray currently does not resize
    // And its initial capacity is only 4. So only space is allocated for 4 ints

    // This causes the segmentation fault because the pointer will try to access
    // memory that may be in use or will be used by another system
    for (int i = 0; i < 50; i++) {
        int rd_num = rand() % 101;
        _append(da, rd_num);
        // da->ptrData[i] = rd_num;
        // or 'da->ptrData[da->length++] = item;' with of conditional in the _add func
    }

    _print(da);
    _status(da);

    // Get item at index 0
    // int val = _get(da, 0);
    // printf("GET [0]: %d\n", val);

    // Remove last item
    // _remove_last(da);
    // _print(da);
    // _status(da);

    // printf("BEFORE REMOVE AT: \n");
    // _print(da);
    // _status(da);

    // printf("AFTER REMOVE AT: \n");
    // _remove_at(da, 0);
    // _print(da);
    // _status(da);

    printf("ADD AT INDEX: 1\n");
    _add(da, 999, 1);
    _print(da);
    _status(da);





}