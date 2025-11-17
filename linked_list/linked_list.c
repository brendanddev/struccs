#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic implementation of a doubly linked list
/// Brendan Dileo - November 14 2025


// Initalizes a new node
struct Node * ll_init_node(void *val, size_t size) {

    // Allocate memory for the node itself and
    struct Node *node = malloc(sizeof(struct Node));
    
    // Handle allocation failure
    if (node == NULL) {
        return NULL;
    }

    // Set the size of the item stored in the node and initialize
    // the nodes `next` and `prev` pointers to NULL
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

    // Copy the raw memory contents from the memory pointed to by `val` into `node->value`
    memcpy(node->value, val, node->item_size);

    return node;
}


// Creates a new linked list
struct LinkedList * ll_init() {
    // Allocate mmeory for the linked list itself
    struct LinkedList *linked_list = malloc(sizeof(struct LinkedList));

    // Handle allocation failure
    if (linked_list == NULL) { 
        return NULL;
    }

    // Set initial length of the linked list and pointers to head/tail to NULL
    linked_list->length = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

// Inserts a node at the head of the linked list
void ll_insert(struct Node *node, struct LinkedList *list) {

    // ISSUE: OLD HEADS PREV PTR NEVER SET

    // Check if the `head` of the list points to NULL since we 
    // can only update the old heads `prev` pointer if there is an old head
    if (list->head != NULL) {
        list->head->prev = node;
    }

    node->next = list->head;                                // Point the node being inserted `next` pointer to the head of the list (what head currently points to)
    node->prev = NULL;                                      // Point the node being inserted `prev` pointer to NULL since its the new head
    list->head = node;                                      // Point the head of the list to the node being inserted

    // Check if the tail of the list is NULL, meaning list is empty
    // If it is, set the tail to the node being inserted since its the only node in the list
    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
}

// Prints all items stored in the linked list, requiring a caller defined print function that knows how to print each value
void ll_print(struct LinkedList *list, void (* print_fn)(void*)) {
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        print_fn(current->value);
    }
    printf("\n");
}


// Prints each node in the linked list with its address, value, and next/prev pointers for debugging
void ll_debug(struct LinkedList *list) {
    struct Node *curr = list->head;
    while (curr != NULL) {
        printf("Node %p | value=%d | prev=%p | next=%p\n", 
            (void *) curr, 
            * (int *) curr->value, 
            (void *) curr->prev, 
            (void *) curr->next);
        curr = curr->next;
    }
}


