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

    // Check if the `head` of the list points to NULL since we 
    // can only update the old heads `prev` pointer if there is an old head
    if (list->head != NULL) {
        list->head->prev = node;
    }

    // Point the node being inserted `next` pointer to whatever the head of the list 
    // currently points to, and the `prev` pointer of the node being inserted to NULL
    // since its the new head of the list. Point the head of the list to the node being
    // inserted
    node->next = list->head;                                
    node->prev = NULL;                                      
    list->head = node;

    // Check if the tail of the list is NULL, meaning list is empty
    // If it is, set the tail to the node being inserted since its the only node in the list
    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
}

// Inserts a node at the tail of the linked list
void ll_insert_tail(struct Node *node, struct LinkedList *list) {

    // Check if list is empty
    if (list->head == NULL) {
        // If list is empty, point the node being inserted `next` pointer to whatever the head of
        // the list currently points to, the node being inserted `prev` to NULL since its the new
        // head of the list, and the tail to the node inserted since its the only node in the list
        node->next = list->head;
        node->prev = NULL;
        list->head = node;
        list->tail = node;
        list->length++;

    // List not empty, need to access and insert at tail
    } else {
        // If list is not empty, set the current tail `next` pointer to the node being inserted,
        // and the node being inserted `next` to NULL since its the new tail. To link the new tail
        // with the old, set the `prev` pointer of the node being inserted to point to the old tail
        list->tail->next = node;
        node->next = NULL;
        node->prev = list->tail;
        list->tail = node;
        list->length++;
    }
}

// Inserts a node at the specified location in the linked list
void ll_insert_at(struct Node *node, struct LinkedList *list, int index) {

    if (index < 0 || index > list->length) return;

    // Check if insertion point is the head of the list
    if (index == 0) {
        ll_insert(node, list);
        return;

    // Check if insertion point is the tail of the list
    } else if (index == list->length) {
        ll_insert_tail(node, list);
        return;

    // If insertion point is not head or tail, its somewhere in between
    } else {

        // Traverse the list starting from the head to find the insertion point 
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check if weve reached the insertion point
            if (idx == index) {

                // To insert the new node:
                // 1. Link the previous nodes `next` to point to the node being inserted
                // 2. Linked the node being inserted `next` to point to the node previously at the insertion point

                struct Node *previous = current->prev;
                struct Node *next = current->next;

                previous->next = node;
                node->next = next;
                list->length++;
                break;
            }

            idx++;
        }
    }
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


