#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../stack_queue/stack.h"


/// test_stack.c
/// The test suite for the Stack implementation
/// Brendan Dileo, November 21 2025



int main() {

    int value = 100;
    struct Node *stack_node = stack_create_node(&value, sizeof(int));
    struct Stack *stack = stack_create();

    printf("Node - Item Size: %zu\n", stack_node->item_size);
    printf("Stack - Length: %d\n", stack->length);

    return 0;
}

