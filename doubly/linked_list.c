#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Doubly Linked List implementation
/// Brendan Dileo - November 14 2025


// Initalizes a new node
struct Node * ll_init_node(void *val, size_t size) {

    // Allocate memory for the node itself and
    struct Node *node = malloc(sizeof(struct Node));
    
    // Handle allocation failure
    if (node == NULL) {
        return NULL;
    }

    // Set the size of the item stored in the node and initalize
    // the nodes next and prev pointers to NULL
    node->item_size = size;
    node->next = NULL;
    node->prev = NULL;

    // Allocate memory for the value that will be stored in the node
    node->value = malloc(node->item_size);

    // Handle allocation failure
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    return node;
}

// Creates a new linked list
struct LinkedList * ll_init() {
    // Allocate mmeory for the linked list itself
    struct LinkedList *linked_list = malloc(sizeof(struct LinkedList));

    // Handle allocation failure
    if (linked_list == NULL) { }

    linked_list->length = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

// Inserts a node at the head of the linked list
void ll_insert(struct Node *node, struct LinkedList *list) {

    // Check if list is emptu,
    if (list->head == NULL) {

    // List is not empty
    } else {


    }
}