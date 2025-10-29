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
        int rd_num = rand() % 100;
        da->ptrData[i] = rd_num;
    }

    _status(da);
    _add(da, 10);


    _print(da);
    _status(da);


    printf("GET [0]: %d\n", _get(da, 0));

}