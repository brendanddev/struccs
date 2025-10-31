#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"


/// main.c


int main() {

    // Create an instance of the DynamicArray
    struct DynamicArray *da = _init();

    // Print current status and contents of the arr
    _print(da);


    // Append 50 random ints to the arr
    for (int i = 0; i < 50; i++) {
        int rd_num = rand() % 101;
        _append(da, rd_num);
    }

    // Print current status and contents after appending 50 ints
    _print(da);


    // Add an item at a specified index
    printf("Adding an item at index: 0\n");
    _add(da, 999, 0);
    _print(da);


    // Get the item at index 0
    int value = _get(da, 0);
    printf("\nValue at index 0: %d\n", value);


    // Remove the last item in the arr
    printf("Removing the last item...\n");
    _remove_last(da);
    _print(da);


    // Remove an item at a specified index
    printf("Removing item at index 0: \n");
    _remove_at(da, 0);          // TODO: Bug - Removes item at index '1' not '0' ?
    _print(da);


    // Retrieve current size and capacity of the array
    int size = _size(da);
    int cap = _capacity(da);
    printf("Size: %d, Capacity: %d\n", size, cap);


    // Check if the array contains an item
    int item = 999;
    bool exists = _contains(da, item);
    printf("The array contains %d: %s\n", item, exists ? "true" : "false");


    // Clear the contents of the array
    _clear(da);
    _print(da);





    // Free memory previously occupied by the internal array and struct
    _discard(da);
    da = NULL;










    // This will currently produce an error: zsh: segmentation fault  ./out
    // This is due to the fact that the DynamicArray currently does not resize
    // And its initial capacity is only 4. So only space is allocated for 4 ints

    // This causes the segmentation fault because the pointer will try to access
    // memory that may be in use or will be used by another system
    // for (int i = 0; i < 50; i++) {
    //     int rd_num = rand() % 101;
    //     _append(da, rd_num);
    //     // da->ptrData[i] = rd_num;
    //     // or 'da->ptrData[da->length++] = item;' with of conditional in the _add func
    // }







}