/**
 * stack.h
 * Header for the generic stack implementation backed by linked nodes.
 * Brendan Dileo - 2025
 */

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node is opaque to callers; its layout lives in stack.c.
struct Node;

typedef struct Stack {
    struct Node *top;
    int length;
} Stack;

// Allocates an empty stack. Caller frees with stack_discard. NULL on failure.
struct Stack* stack_create();
// Pushes a node holding a copy of size bytes from value. Returns true.
bool stack_push(struct Stack *stack, void *value, size_t size);
// Copies the top value into out without popping. False if the stack is empty.
bool stack_peek(struct Stack *stack, void *out);
// Copies the top value into out and pops it. False if the stack is empty.
bool stack_pop(struct Stack *stack, void *out);
// Frees every node but keeps the stack struct for reuse.
void stack_clear(struct Stack *stack);
// Returns true if the stack has no nodes.
bool stack_is_empty(struct Stack *stack);
// Returns the number of nodes on the stack.
int stack_size(struct Stack *stack);
// Applies print_fn to each value from top to bottom.
void stack_print(struct Stack *stack, void (* print_fn)(void*));
// Frees every node and the stack struct.
void stack_discard(struct Stack *stack);

#endif
