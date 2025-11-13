#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

    // Set size of item stored in the node and initialize next and prev pointers to NULL
    node->item_size = size;
    node->next = NULL;
    node->prev = NULL;

    // Allocate memory for the type of data this node will store
    void *tmp = NULL;
    tmp = malloc(size);

    // Handle allocation failure
    if (tmp == NULL) { }

    // Point the `value` pointer to the memory allocated for the value and
    // copy the raw memory contents from the memory pointed to by `val` into `node->value`
    node->value = tmp;
    memcpy(node->value, val, node->item_size);

    return node;
}

// Initializes a new LinkedList
struct LinkedList * _init() {

    struct LinkedList *list = NULL;
    list = malloc(sizeof(struct LinkedList));

    if (list == NULL) { }

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}


// Free the memory allocated by the Node
void _node_discard(struct Node *node) { 
    if (node != NULL) {
        free(node->next);
        free(node->prev);
        free(node->value);
        free(node);
    }
}

// Free the memory allocated by the LinkedList
void _discard(struct LinkedList *linked_list) { 
    if (linked_list != NULL) {
        free(linked_list);
    }
}