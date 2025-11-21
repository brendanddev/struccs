#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"


/// stack.c
/// A generic implementation of a stack backed by linked nodes
/// Brendan Dileo - November 21 2025


// Creates a new node to be stored in the stack
struct Node* stack_create_node(void *val, size_t size) {

    // Allocate memory for the node struct itself and
    // handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Set size of item stored in the node and initial pointer to next node to NULL
    node->item_size = size;
    node->next = NULL;

    // Allocate memory for the value the node will store and
    // handle allocation failure
    node->value = malloc(size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copies the raw bytes from the memory pointed to by `val` into
    // the memory allocated for this node at `node->value`
    memcpy(node->value, val, node->item_size);
    return node;
}

// Creates a new stack
struct Stack* stack_create() { 

    // Allocate memory for the stack struct and 
    // handle allocation failure
    struct Stack *stack = malloc(sizeof(struct Stack));
    if (stack == NULL) return NULL;

    // Set pointer to top node to NULL and length to 0 
    // as default
    stack->top = NULL;
    stack->length = 0;

    return stack;
}