#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../stack/stack.h"


/// test_stack.c
/// The test suite for the Stack implementation
/// Brendan Dileo, November 21 2025


void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}

int main() {

    int value = 100;
    struct Stack *stack = stack_create();

    printf("Stack is empty? %d  (1 = true, 0 = false) \n", stack_is_empty(stack));
    printf("Stack Size: %d\n", stack_size(stack));

    stack_push(stack, &value, sizeof(int));
    stack_push(stack, &value, sizeof(int));
    stack_push(stack, &value, sizeof(int));
    stack_push(stack, &value, sizeof(int));
    stack_push(stack, &value, sizeof(int));

    printf("Stack is empty? %d  (1 = true, 0 = false) \n", stack_is_empty(stack));
    printf("Stack Size: %d\n", stack_size(stack));
    stack_print(stack, print_int);
    printf("\n");

    int peekval;
    if (stack_peek(stack, &peekval)) {
        printf("Peek Value: %d\n", peekval);
    }
    
    printf("Stack Size: %d\n", stack_size(stack));    // should still be 5

    // stack_clear(stack);
    int popval;
    if (stack_pop(stack, &popval)) {
        printf("Popped the value %d off the stack\n", popval);
    }
    printf("Stack Size: %d\n", stack_size(stack));    // should be 0
    stack_print(stack, print_int);
    printf("\n");

    stack_discard(stack);
    stack = NULL;
    return 0;
}

