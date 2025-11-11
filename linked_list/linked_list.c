#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


/// linked_list.c
/// Brendan Dileo - November 11 2025



// Creates a new struct Node
struct Node * _node_init(int value) {
    // Allocate memory for the Node struct itself
    struct Node *node = NULL;
    node = malloc(sizeof(struct Node));

    // Store the value inside the Node
    node->value = value;

    // Set the `next` pointer to NULL since it is not linked yet
    node->next = NULL;

    return node;
}

// Creates a new struct LinkedList
struct LinkedList * _init() {
    // Allocate memory for the LinkedList itself
    struct LinkedList *linked_list = NULL;
    linked_list = malloc(sizeof(struct LinkedList));

    // Point the `head` pointer to NULL since no Nodes are linked
    linked_list->head = NULL;
    linked_list->length = 0;

    return linked_list;
}

// Inserts a new Node into the LinkedList at the head
void _insert(struct Node *node, struct LinkedList *list) {

    // Point the new Nodes `next` to the `head` of the LinkedList
    node->next = list->head;

    // Point the lists `head` to the new node
    list->head = node;

    // Increment length
    list->length++;
}

// Inserts a new Node into the LinkedList at the tail of the list
void _insert_tail(struct Node *node, struct LinkedList *list) {

    // Check if the head of the list is NULL, meaning the list is empty
    if (list->head == NULL) {
        // If the list is empty, set the new node as the first node in the list
        // The node added now becomes the head node in the list (first node) 
        list->head = node;
        list->length++;

    // List is not empty, need to traverse from the head node to the tail node
    } else {

        // Start from head node, traverse the list until we reach a node where next == NULL, this is the tail node
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check if the current node does not point to another node with its `next` ptr
            // This is the tail node
            if (current->next == NULL) {
                // Insert the node at the end by setting the current tails `next` ptr to the node inserted
                current->next = node;
                list->length++;
                return;
            }
        }
    }
}


// Inserts a new Node into the LinkedList at a specified index
void _insert_at(struct Node *node, struct LinkedList *list, int index) {

    // List is empty? --> Either indicate error or just insert at closest index?
    // The `next` ptrs at the position i - 1 and i + 1 neeed to be adjusted to account for the node being inserted at index
    // Shift all subsequent elements right?s

    if (index < 0 || index > list->length) return;

    printf("Inserting At: %d\n", index);

    // Traverse the list starting from the head
    int i = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        i++;

        // Found the position where the node will be inserted
        if (i == index) {
            struct Node *next = current->next;          // Store the the `next` pointer that initially points to the next item before insertion
            current->next = node;                       // Set the `next` ptr of the current node to the node being added
            node->next = next->next;                    // Set the `next` ptr of the node being inserted to point to the node after the node being inserted
            list->length++;
            return;
        }
    }
}








// Prints the contents of the LinkedList by traversing Node through Node
void _print(struct LinkedList *list) {
    printf("Printing Contents...\n");
    int index = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        printf("Value: %d, Index: %d\n", current->value, index);
        index++;
    }
}

// Frees any memory allocated by the Node
void _node_discard(struct Node *node) {
    if (node != NULL) {
        free(node->next);
        free(node);
    }
}

// Frees any memory allocated by the LinkedList
void _discard(struct LinkedList *linked_list) {
    if (linked_list != NULL) {
        free(linked_list->head);
        free(linked_list);
    }
}





