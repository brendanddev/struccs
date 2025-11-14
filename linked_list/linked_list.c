#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic Doubly Linked List implementation
/// Brendan Dileo - November 12 2025



// Initializes a new Node
struct Node * _init_node(void *val, size_t size) {
    
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

    // Allocate memory for the linked list itself
    struct LinkedList *list = NULL;
    list = malloc(sizeof(struct LinkedList));

    // Handle allocation failure
    if (list == NULL) { }

    list->length = 0;
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Inserts a new node at the head of the linked list
bool _insert(struct Node *node, struct LinkedList *list) {

    // Check if the list is empty
    if (list->head == NULL) {
        // Assign the node being inserted as the new head
        // Assign the tail to the node being inserted as this is the only node in the list
        // Since its the only node in the list, it will act as the tail and the head, and
        // both next and prev pointers from the node will be NULL
        node->next = list->head;
        list->head = node;
        list->tail = node;
        list->length++;
        return true;

    } else {
        // If there is already a head node
        // Create a temp pointer to hold the original head
        // Set the node as the new head, and point its `next` pointer to the old head
        // Which should relink the lists nodes
        struct Node *old_head = list->head;
        node->next = old_head;
        old_head->prev = node;
        list->head = node;
        list->length++;
        return true;



        // node->next = list->head;
        // list->head = node;
        // list->head->next = temp;
        // list->length++;
        // return true;




    }




    // Check if the list is empty
    // if (list->head == NULL) {
    //     node->next = list->head;                // Point the node being inserted `next` to the head of the list
    //     list->head = node;                      // Point the head of the list at the node inserted
    //     list->tail = node;                      // Point the tail of the list to the node inserted since its the only node
    //     list->length++;
    //     return true;
    // } else {
    //     node->next = list->head;
    //     list->head = node;
    //     list->tail = list->head->next;
    //     list->length++;
    //     return true;

    // }
}

// Inserts a new node at the tail of the linked list
bool _insert_tail(struct Node *node, struct LinkedList *list) {


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


// Free the memory allocated by the Node
void _discard_node(struct Node *node) { 
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