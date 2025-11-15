#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Doubly Linked List implementation
/// Brendan Dileo - November 14 2025

// // Defines the LinkedList struct type
// typedef struct LinkedList {
//     int length;
//     struct Node *head;                  // Pointer to the head node (first element)
//     struct Node *tail;                  // Pointer to the tail node (last element)
// } LinkedList;


// // Definess the doubly Node struct type
// typedef struct Node {
//     void *value;                        // Pointer to the value stored in this node
//     size_t item_size;                   // The size of the item stored in the node
//     struct Node *next;                  // Pointer to the next node in the list
//     struct Node *prev;                  // Pointer to the previous node in the list
// } Node;


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


struct LinkedList * ll_init() {
}