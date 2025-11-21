
/// stack.h
/// Header for the generic stack implementation backed by linked nodes
/// Brendan Dileo - November 21 2025


#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines the Node struct type
typedef struct Node {
    void *value;            // pointer to the memory holding the value stored in this node
    size_t item_size;       // size of the item stored in the node
    struct Node *next;      // pointer to the next node in the stack
    struct Node *top;       // pointer to the current top node of the stack
} Node;


// Defines the Stack struct type
typedef struct Stack {
} Stack;


#endif