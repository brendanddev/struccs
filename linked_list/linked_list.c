#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Singly Linked List implementation
/// Brendan Dileo - November 12 2025



// // Initializes a new Node
// struct Node * _init_node(void *val, size_t size) {
    
//     // Define a pointer to the Node and allocate memory for the struct itself
//     struct Node *node = NULL;
//     node = malloc(sizeof(struct Node));

//     // Handle allocation failure
//     if (node == NULL) { }

//     // Set size of item stored in the node and initialize next and prev pointers to NULL
//     node->item_size = size;
//     node->next = NULL;

//     // Allocate memory for the type of data this node will store
//     void *tmp = NULL;
//     tmp = malloc(size);

//     // Handle allocation failure
//     if (tmp == NULL) { }

//     // Point the `value` pointer to the memory allocated for the value and
//     // copy the raw memory contents from the memory pointed to by `val` into `node->value`
//     node->value = tmp;
//     memcpy(node->value, val, node->item_size);

//     return node;
// }

// // Initializes a new LinkedList
// struct LinkedList * _init() {

//     // Allocate memory for the linked list itself
//     struct LinkedList *list = NULL;
//     list = malloc(sizeof(struct LinkedList));

//     // Handle allocation failure
//     if (list == NULL) { }

//     list->length = 0;
//     list->head = NULL;
//     list->tail = NULL;
//     return list;
// }

// // Inserts a new node at the head of the linked list
// void _insert(struct Node *node, struct LinkedList *list) {

//     // Check if list is empty
//     if (list->head == NULL) {
//         node->next = list->head;                    // Assign the node being inserted `next` to the head of the list
//         list->head = node;                          // Set the head of the list to the node being inserted
//         list->tail = node;                          // Set the tail of the list to the node being inserted since its the only node
//         list->length++;             

//     // List is not empty, reassign head
//     } else {
//         struct Node *old_head = list->head;
//         node->next = old_head;
//         old_head->prev = node;
//         list->head = node;
//         list->length++;



//     }
// }



// // Returns whether the linked list is empty or not
// bool _is_empty(struct LinkedList *list) {
//     if (list->head == NULL) return true;
//     return false;
// }

// // Returns the current size (length) of the linked list
// int _size(struct LinkedList *list) {
//     return list->length;
// }


// // Free the memory allocated by the Node
// void _discard_node(struct Node *node) { 
//     if (node != NULL) {
//         free(node->next);
//         free(node->prev);
//         free(node->value);
//         free(node);
//     }
// }

// // Free the memory allocated by the LinkedList
// void _discard(struct LinkedList *linked_list) { 
//     if (linked_list != NULL) {
//         free(linked_list);
//     }
// }