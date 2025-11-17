#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_common.h"


/// test_common.c
/// Brendan Dileo, November 17 2025








bool compare_int(void *a, void *b) {
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia == ib) return true;
    return false;
}

void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}