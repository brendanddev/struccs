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




void _node_discard(struct Node *node) {
}
void _discard(struct LinkedList *linked_list) {
}