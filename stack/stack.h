
/// stack.h
/// Header for the generic stack implementation backed by linked nodes
/// Brendan Dileo - November 21 2025


#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the stack
struct Node;


// Defines the Stack struct type
typedef struct Stack {
    struct Node *top;       // Pointer to the top node in the stack
    int length;             // current length of the stack
} Stack;


struct Stack* stack_create();
bool stack_push(struct Stack *stack, void *value, size_t size);
bool stack_peek(struct Stack *stack, void *out);
bool stack_pop(struct Stack *stack, void *out);
void stack_clear(struct Stack *stack);
bool stack_is_empty(struct Stack *stack);
int stack_size(struct Stack *stack);
void stack_print(struct Stack *stack, void (* print_fn)(void*));
void stack_discard(struct Stack *stack);

#endif