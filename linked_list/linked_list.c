#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Singly Linked List implementation
/// Brendan Dileo - November 12 2025

// Initializes a new node
struct Node * _init_node(void *val, size_t size) {

    // Define a pointer to the Node and allocate memory for the struct node itself
    struct Node *node = NULL;
    node = malloc(sizeof(struct Node));

    // Handle allocation failure
    if (node == NULL) { 
        return NULL;
    }

    // Set size of item stored in the node and initialize its next pointer
    node->item_size = size;
    node->next = NULL;

    // Allocate memory for the type of data this node will store
    node->value = malloc(size);
    
    // Handle allocation failure
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy the raw memory contents from the memory pointed to by `val` into `node->value`
    memcpy(node->value, val, node->item_size);
    return node;
}

// Initializes a new LinkedList
struct LinkedList * _init() { 

    // Allocate memory for the linked list itself
    struct LinkedList *list = NULL;
    list = malloc(sizeof(struct LinkedList));

    // Handle allocation failure
    if (list == NULL) {
        return NULL;
    }

    // Set the lists initial length and the initial pointers for the head and tail nodes
    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Inserts a new node at the head of the linked list
void _insert(struct Node *node, struct LinkedList *list) {

    node->next = list->head;                // Point the node being inserted `next` pointer to the head of the list (what head currently points to)
    list->head = node;                      // Point the head of the list to the node being inserted

    // Check if the tail of the list is NULL, meaning the list is empty
    // If it is, we set the tail to the node being inserted since its the only node
    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
}

// Inserts a new node at the tail of the linked list
void _insert_tail(struct Node *node, struct LinkedList *list) {

    // If the list is empty, insert at the head as this is the only node and will be the tail too
    if (list->head == NULL) {
        node->next = list->head;
        list->head = node;
        list->tail = node;
        list->length++;
    
    // List is not empty, use tail pointer to insert at tail
    } else {
        list->tail->next = node;            // Point the tails `next` pointer to the node being inserted
        node->next = NULL;                  // Point the node being inserted `next` to NULL since its the new tail
        list->tail = node;                  // Set the tail of the list to the newly inserted node
        list->length++;
    }
}

// Inserts a new node at the specified location in the linked list
void _insert_at(struct Node *node, struct LinkedList *list, int index) {

    if (index < 0 || index > list->length) return;

    // If index = 0, the insertion point is the head so insert at head
    if (index == 0) {
        _insert(node, list);    // insert at head
    
    // If index = length, the insertion point is the tail so insert at tail
    } else if (index == list->length) {
        _insert_tail(node, list);   // insert at tail
    
    // Otherwise need to find insertion point
    } else {

        // Traverse the list starting from the head to find the insertion point
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check to see if weve reached the node before the insertion point
            // This is so we can reassign the surrounding nodes to insert the node
            if (idx == (index - 1)) {

                struct Node *prev = current;                // The 'current' node which is the node before the insertion point
                struct Node *curr = current->next;          // The node at the insertion point

                // Set the node before the insertion point `next` pointer to the node being inserted
                // Set the node being inserted `next` to the node previosly at the insertion point to relink the nodes
                prev->next = node;
                node->next = curr;
                list->length++;
                break;
            }
            idx++;
        }
    }
}




// Returns whether the linked list is empty or not
bool _is_empty(struct LinkedList *list) {
    if (list->head == NULL) return true;
    return false;
}

// Returns the current size (length) of the linked list
int _size(struct LinkedList *list) {
    return list->length;
}



// Frees the memory allocated by the node
void _discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Frees the memory allocated by the linked list
void _discard(struct LinkedList *list) {
    if (list != NULL) {
        free(list);
    }
}

