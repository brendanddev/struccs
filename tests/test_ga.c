/**
 * test_ga.c
 * The test suite for the GenericArray implementation.
 * Brendan Dileo - 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "generic_array.h"

void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}

int main() {

    struct GenericArray *generic_array = create_int_ga();
    ga_print(generic_array, print_int);
}