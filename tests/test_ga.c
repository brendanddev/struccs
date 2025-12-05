#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../generic_array/generic_array.h"


/// test_ga.c
/// The test suite for the GenericArray implementation
/// Brendan Dileo, November 20 2025


void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}

int main() {

    struct GenericArray *generic_array = create_int_ga();
    ga_print(generic_array, print_int);
}