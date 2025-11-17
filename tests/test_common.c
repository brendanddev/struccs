#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_common.h"


/// test_common.c
/// Brendan Dileo, November 17 2025


// Creates a new LinkedList and populates it with integers
struct LinkedList* create_int_list(void) {
    struct LinkedList *linked_list = ll_init();
    for (int i = 0; i < 10; i++) {
        int rd_num = rand() % 1500;
        struct Node *node = ll_init_node(&rd_num, sizeof(int));
        ll_insert_tail(node, linked_list);
    }
    return linked_list;
}


// Creates a new LinkedList with a specified size and populates it with integers
struct LinkedList* create_int_list_from_size(int size) {
    struct LinkedList *linked_list = ll_init();
    for (int i = 0; i < size; i++) {
        int rd_num = rand() % 1500;
        struct Node *node = ll_init_node(&rd_num, sizeof(int));
        ll_insert_tail(node, linked_list);
    }
    return linked_list;
}


// Compares two integers
bool compare_int(void *a, void *b) {
    int ia = * (int *) a;
    int ib = * (int *) b;
    if (ia == ib) return true;
    return false;
}

// Prints an integer value
void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}