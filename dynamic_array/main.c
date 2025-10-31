#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"


/// main.c

// Prototypes
void test_add_at();
void test_get();
void test_remove_at();
void test_contains();
void test_shrink();

int main() {

    test_add_at();
    test_get();
    test_remove_at();
    test_contains();
    test_shrink();
    return 0;


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


void test_add_at() {
    printf("\nADD_AT TEST: \n");
    struct DynamicArray *da = _init();
    for (int i = 0; i < 10; i++) _append(da, i);

    printf("Before add_at: \n");
    _print(da);

    printf("Adding an item (999) at Index: 1\n");
    _add(da, 999, 1);
    _print(da);

    _discard(da);
    da = NULL;
}

void test_get() {
    printf("\nGET TEST: \n");
    struct DynamicArray *da = _init();
    for (int i = 0; i < 10; i++) _append(da, i);

    int value = _get(da, 0);
    printf("\nValue at index 0: %d\n", value);

    _discard(da);
    da = NULL;
}

void test_remove_at() {
    printf("\nREMOVE_AT TEST: \n");
    struct DynamicArray *da = _init();
    for (int i = 0; i < 10; i++) _append(da, i);

    printf("BEFORE REMOVAL: \n");
    _print(da);

    printf("Removing item at index 0: \n");
    printf("SHOULD REMOVE ITEM: %d\n", _get(da, 0));
    _remove_at(da, 0);  // TODO: Bug - Removes item at index '1' not '0' ?
    _print(da);

    printf("Removing item at index 4: \n");
    printf("SHOULD REMOVE ITEM: %d\n", _get(da, 4));
    _remove_at(da, 4);
    _print(da);

    _discard(da);
    da = NULL;
}

void test_contains() {
    printf("\nCONTAINS TEST: \n");
    struct DynamicArray *da = _init();
    for (int i = 0; i < 10; i++) _append(da, i);

    int itemOne = 999;
    int itemTwo = 1;
    bool existsOne = _contains(da, itemOne);
    bool existsTwo = _contains(da, itemTwo);

    printf("The array contains %d: %s\n", itemOne, existsOne ? "true" : "false");
    printf("The array contains %d: %s\n", itemTwo, existsTwo ? "true" : "false");

    _discard(da);
    da = NULL;
}


void test_shrink() {
    printf("\nSHRINK TEST: \n");
    struct DynamicArray *da = _init();
    printf("Initial State: Capacity=%d, Length=%d\n", _capacity(da), _size(da));

    // Append 100 items to the array
    for (int i = 0; i < 100; i++) {
        int rd_num = rand() % 101;
        _append(da, rd_num);
    }

    printf("Before removals: Capacity=%d, Length=%d\n", _capacity(da), _size(da));

    // Remove 95 items from the array
    while (_size(da) > 5) {
        _remove_last(da);
    }

    printf("After removals: Capacity=%d, Length=%d\n", _capacity(da), _size(da));

    // Free memory previously occupied by the internal array and struct
    _discard(da);
    da = NULL;
}