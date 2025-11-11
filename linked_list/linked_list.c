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

void _insert(struct Node *node, struct LinkedList *list) {

    // Point the new Nodes `next` to the `head` of the LinkedList
    node->next = list->head;

    // Point the lists `head` to the new node
    list->head = node;

    // Increment length
    list->length++;
}

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