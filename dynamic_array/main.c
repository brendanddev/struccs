#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"


/// main.c

int main() {

    struct DynamicArray *da = _init();

    _status(da);
    _add(da, 10);


    _print(da);
    _status(da);


    printf("GET [0]: %d\n", _get(da, 0));

}