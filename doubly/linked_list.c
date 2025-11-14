#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Doubly Linked List implementation
/// Brendan Dileo - November 14 2025




// // Definess the doubly Node struct type
// typedef struct Node {
//     void *value;                        // Pointer to the value stored in this node
//     size_t item_size;                   // The size of the item stored in the node
//     struct Node *next;                  // Pointer to the next node in the list
//     struct Node *prev;                  // Pointer to the previous node in the list
// } Node;

// // Defines the LinkedList struct type
// typedef struct LinkedList {
//     int length;
//     struct Node *head;                  // Pointer to the head node (first element)
//     struct Node *tail;                  // Pointer to the tail node (last element)
// } LinkedList;

struct Node * ll_init_node(void *val, size_t size) {
    struct Node *node = 
}


struct LinkedList * ll_init() {
}