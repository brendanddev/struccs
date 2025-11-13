#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../linked_list/linked_list.h"


/// test_ll.c
/// Testing and developmental file for the LinkedList implementation
/// Brendan Dileo - November 11 2025

// Address: 0x0 == NULL


int main() {

    // Create a new Node and LinkedList
    int val = 100;
    void *ptr = &val;
    struct Node *node = _node_init(ptr, sizeof(int));
    printf("Value: %d, Value: %d, Item Size: %zu, \n", * (int *) node->value, node->value, node->item_size);

    return 0;
}