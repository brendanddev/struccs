// stack.c
// A generic implementation of a stack backed by linked nodes.
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "stack.h"

// Each node owns a heap copy of its value (item_size bytes).
typedef struct Node {
    void *value;
    size_t item_size;
    struct Node *next;
} Node;

// Prototypes
static struct Node* stack_create_node(const void *val, size_t size);
static void stack_discard_node(struct Node *node);
static void stack_discard_all_nodes(struct Stack *stack);

struct Stack* stack_create() {
    struct Stack *stack = malloc(sizeof(struct Stack));
    if (stack == NULL) return NULL;

    stack->top = NULL;
    stack->length = 0;

    return stack;
}

bool stack_push(struct Stack *stack, const void *value, size_t size) {
    struct Node *node = stack_create_node(value, size);

    if (stack_is_empty(stack)) {
        stack->top = node;
        stack->top->next = NULL;
        stack->length++;
        return true;
    } else {
        // Link the new node on top of the current top.
        struct Node *temp = stack->top;
        stack->top = node;
        stack->top->next = temp;
        stack->length++;
        return true;
    }
}

bool stack_peek(const struct Stack *stack, void *out) {
    if (stack_is_empty(stack)) return false;
    memcpy(out, stack->top->value, stack->top->item_size);
    return true;
}

bool stack_pop(struct Stack *stack, void *out) {
    if (stack_is_empty(stack)) return false;

    struct Node *temp = stack->top->next;
    memcpy(out, stack->top->value, stack->top->item_size);
    stack_discard_node(stack->top);
    stack->top = temp;
    stack->length--;
    return true;
}

void stack_clear(struct Stack *stack) {
    stack_discard_all_nodes(stack);
    stack->top = NULL;
    stack->length = 0;
}

bool stack_is_empty(const struct Stack *stack) {
    if (stack->top == NULL) return true;
    return false;
}

int stack_size(const struct Stack *stack) {
    return stack->length;
}

void stack_print(const struct Stack *stack, void (* print_fn)(const void*)) {
    for (struct Node *current = stack->top; current != NULL; current = current->next) {
        print_fn(current->value);
    }
}

void stack_discard(struct Stack *stack) {
    if (stack != NULL) {
        stack_discard_all_nodes(stack);
        free(stack);
    }
}


// Private helper functions - linkage limited to this file


// Deep-copies size bytes from val; the returned node owns the copy.
static struct Node* stack_create_node(const void *val, size_t size) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    node->item_size = size;
    node->next = NULL;

    node->value = malloc(size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->value, val, node->item_size);
    return node;
}

static void stack_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

static void stack_discard_all_nodes(struct Stack *stack) {
    struct Node *current = stack->top;
    while (current != NULL) {
        struct Node *next = current->next;
        stack_discard_node(current);
        current = next;
    }
}
