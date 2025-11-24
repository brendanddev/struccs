#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"


/// stack.c
/// A generic implementation of a stack backed by linked nodes
/// Brendan Dileo - November 21 2025


// Prototypes
static void stack_discard_node(struct Node *node);
static void stack_discard_all_nodes(struct Stack *stack);


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

// Pushes an item to the top of the stack
bool stack_push(struct Stack *stack, void *value, size_t size) {

    struct Node *node = stack_create_node(value, size);

    if (stack_is_empty(stack)) {
        // Set the node as the top of the stack
        stack->top = node;
        stack->top->next = NULL;
        stack->length++;
        return true;
    } else {
        // Store pointer to the current top node, reassign the top to the 
        // node being pushed, and relink nodes to maintain stack
        struct Node *temp = stack->top;
        stack->top = node;                     
        stack->top->next = temp;
        stack->length++;
        return true;
    }
}

// Returns the value stored in the node at the top of the stack without removing the node
bool stack_peek(struct Stack *stack, void *out) {
    if (stack_is_empty(stack)) return false;
    memcpy(out, stack->top->value, stack->top->item_size);
    return true;
}

// Pops the node stored at the top of the stack
bool stack_pop(struct Stack *stack, void *out) {
    if (stack_is_empty(stack)) return false;

    // store pointer to the current top node
    // free the top node value + struct
    // set new top to next pointed to by temp pointer

    struct Node *temp = stack->top->next;       // new top after pop
    memcpy(out, stack->top->value, stack->top->item_size);
    stack_discard_node(stack->top);
    stack->top = temp;
    stack->length--;
    return true;



    // stack_discard_node(stack->top);
    // stack->top = temp->next;
    // memcpy(out, temp->value, stack->top->item_size);
    // return true;
}

// Clears the contents of the stack but keeps the stack itself
void stack_clear(struct Stack *stack) { 
    stack_discard_all_nodes(stack);
    stack->top = NULL;
    stack->length = 0;
}

// Returns a boolean value indicating whether the stack is empty or not
bool stack_is_empty(struct Stack *stack) {
    if (stack->top == NULL) return true;
    return false;
}

// Returns the current size of the stack (length)
int stack_size(struct Stack *stack) {
    return stack->length;
}

// Prints the contents of the stack from top to bottom
void stack_print(struct Stack *stack, void (* print_fn)(void*)) {
    for (struct Node *current = stack->top; current != NULL; current = current->next) {
        print_fn(current->value);
    }
}

// Frees the memory occupied by the stack
void stack_discard(struct Stack *stack) {
    if (stack != NULL) {
        stack_discard_all_nodes(stack);
        free(stack);
    }
}


// Private helper functions, linkage limited to this file


// Frees the memory occupied by a single node
static void stack_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Frees the memory occupied by each node in the stack
static void stack_discard_all_nodes(struct Stack *stack) {
    struct Node *current = stack->top;
    while (current != NULL) {
        struct Node *next = current->next;
        stack_discard_node(current);
        current = next;
    }
}