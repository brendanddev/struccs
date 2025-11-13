#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Doubly Linked List implementation
/// Brendan Dileo - November 12 2025



// Initializes a new Node
struct Node * _node_init(void *val, size_t size) {
    
    // Define a pointer to the Node and allocate memory for the struct itself
    struct Node *node = NULL;
    node = malloc(sizeof(struct Node));

    // Handle allocation failure
    if (node == NULL) { }

    // Point the value pointer to the value passed and set the item size
    node->value = val;
    node->item_size = size;

    // Initially the Node will not point to any other nodes
    node->next = NULL;
    node->prev = NULL;

    return node;
}


struct LinkedList * _init() {

    struct LinkedList *list = NULL;

}