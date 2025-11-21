
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
} Node;


// Defines the Stack struct type
typedef struct Stack {
    struct Node *top;       // pointer to the top node in the stack
    int length;             // current length of the stack
} Stack;


struct Node* stack_create_node(void *val, size_t size);
struct Stack* stack_create();
void stack_push();
void stack_pop();
void stack_peek();

bool stack_is_empty();
int stack_size();

void stack_print();

void stack_discard_node();
void stack_discard_all_nodes();
void stack_discard();

#endif