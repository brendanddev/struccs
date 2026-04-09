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

void print_info(GenericArray *ga) {
    if (ga != NULL) {
        printf(">>> Length: %d\n", ga_size(ga));
        printf(">>> Capacity: %d\n", ga_capacity(ga));
        printf(">>> Usage: %f\n", ga_usage(ga));
        ga_print(ga, print_int);
        printf("\n");
    }
}

bool compare_int(void *a, void *b) {
    int num1 = * (int *)a;
    int num2 = * (int *)b;

    if (num1 == num2) {
        return true;
    } else {
        return false;
    }
}

int main(void) {
    GenericArray *ga = ga_init(sizeof(int));
    if (ga == NULL) return -1;
    print_info(ga);

    printf(">>> Adding values to the GenericArray...\n");
    for (int i = 0; i < 16; i++) {
        int num = i * 5;
        ga_add(ga, i, &num);
        printf(">>> Usage: %f\n", ga_usage(ga));
    }
    print_info(ga);

    void *val;
    if (ga_get(ga, 1, val)) {
        printf(">>> [GET] Found value=%d\n", *(int *)val);
    } else {
        printf(">>> [GET] Could not get the value at the specified index.\n");
    }

    // Should fail
    if (ga_get(ga, 1000, val)) {
        printf(">>> [GET] Found value=%d\n", *(int *)val);
    } else {
        printf(">>> [GET] Could not get the value at the specified index.\n");
    }

    int num = 222;
    if (ga_set(ga, 0, &num)) {
        printf(">>> [SET] Set value=%d\n", num);
    } else {
        printf(">>> [SET] Could not set the value at the specified index.\n");
    }

    // Should fail
    if (ga_set(ga, 888, &num)) {
        printf(">>> [SET] Set value=%d\n", num);
    } else {
        printf(">>> [SET] Could not set the value at the specified index.\n");
    }
    print_info(ga);

    num = 50;
    int idx = ga_find(ga, &num, compare_int);
    if (idx == -1) {
        printf(">>> [FIND] Could not find the value '%d'.\n", num);
    } else {
        printf(">>> [FIND] Found value at index=%d\n", idx);
    }

    // Should fail
    num = 5051;
    idx = ga_find(ga, &num, compare_int);
    if (idx == -1) {
        printf(">>> [FIND] Could not find the value '%d'.\n", num);
    } else {
        printf(">>> [FIND] Found value at index=%d\n", idx);
    }

    if (ga_remove_last(ga)) {
        printf(">>> [REMOVE_LAST] Removed the last value in the array.\n");
    } else {
        printf(">>> [REMOVE_LAST] Failed to remove the last value in the array.\n");
    }
    print_info(ga);

    if (ga_remove_at(ga, 1)) {
        printf(">>> [REMOVE_AT] Removed the value at index '1' in the array.\n");
    } else {
        printf(">>> [REMOVE_AT] Failed to remove the value at index '1' in the array.\n");
    }
    print_info(ga);

    // Should fail
    if (ga_remove_at(ga, 999)) {
        printf(">>> [REMOVE_AT] Removed the value at index '999' in the array.\n");
    } else {
        printf(">>> [REMOVE_AT] Failed to remove the value at index '999' in the array.\n");
    }
    print_info(ga);

    num = 5;
    if (ga_contains(ga, compare_int, &num)) {
        printf(">>> [CONTAINS] Found value=%d\n", num);
    } else {
        printf(">>> [CONTAINS] Could not access the '%d' value in the array.\n", num);
    }

    // Should fail
    num = 999;
    if (ga_contains(ga, compare_int, &num)) {
        printf(">>> [CONTAINS] Found value=%d\n", num);
    } else {
        printf(">>> [CONTAINS] Could not access the '%d' value in the array.\n", num);
    }

    ga_clear(ga);
    print_info(ga);

    ga_discard(ga);
    ga = NULL;
    return 0;
}