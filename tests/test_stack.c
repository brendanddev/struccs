/**
 * test_stack.c
 * The test suite for the Stack implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

// Prototypes
void test_stack_create(void);
void test_stack_push(void);
void test_stack_peek(void);
void test_stack_pop(void);
void test_stack_lifo_order(void);
void test_stack_empty_behavior(void);
void test_stack_pop_until_empty(void);
void test_stack_peek_after_pop(void);
void test_stack_mixed_operations(void);
void test_stack_large_push(void);
void test_stack_reuse_after_empty(void);
void test_stack_multiple_underflow(void);
void test_stack_struct_type(void);
void test_stack_string_pointer(void);

int main(void) {
    test_stack_create();
    test_stack_push();
    test_stack_peek();
    test_stack_pop();
    test_stack_lifo_order();
    test_stack_empty_behavior();
    test_stack_pop_until_empty();
    test_stack_peek_after_pop();
    test_stack_mixed_operations();
    test_stack_large_push();
    test_stack_reuse_after_empty();
    test_stack_multiple_underflow();
    test_stack_struct_type();
    test_stack_string_pointer();

    printf("All Stack tests passed.\n");
    return 0;
}

void test_stack_create(void) {
    struct Stack *stack = stack_create();

    assert(stack != NULL);
    assert(stack_is_empty(stack) == true);
    assert(stack_size(stack) == 0);

    stack_discard(stack);
}

void test_stack_push(void) {
    struct Stack *stack = stack_create();

    int a = 10;
    int b = 20;

    stack_push(stack, &a, sizeof(int));
    assert(stack_size(stack) == 1);

    stack_push(stack, &b, sizeof(int));
    assert(stack_size(stack) == 2);

    stack_discard(stack);
}

void test_stack_peek(void) {
    struct Stack *stack = stack_create();

    int a = 42;
    stack_push(stack, &a, sizeof(int));

    int out = 0;
    assert(stack_peek(stack, &out) == true);
    assert(out == 42);

    // should not remove element
    assert(stack_size(stack) == 1);

    stack_discard(stack);
}

void test_stack_pop(void) {
    struct Stack *stack = stack_create();

    int a = 5;
    stack_push(stack, &a, sizeof(int));

    int out = 0;
    assert(stack_pop(stack, &out) == true);
    assert(out == 5);

    assert(stack_size(stack) == 0);

    // popping empty stack should fail
    assert(stack_pop(stack, &out) == false);

    stack_discard(stack);
}

void test_stack_lifo_order(void) {
    struct Stack *stack = stack_create();

    int a = 1, b = 2, c = 3;

    stack_push(stack, &a, sizeof(int));
    stack_push(stack, &b, sizeof(int));
    stack_push(stack, &c, sizeof(int));

    int out;

    stack_pop(stack, &out);
    assert(out == 3);

    stack_pop(stack, &out);
    assert(out == 2);

    stack_pop(stack, &out);
    assert(out == 1);

    stack_discard(stack);
}

void test_stack_empty_behavior(void) {
    struct Stack *stack = stack_create();

    int out;

    assert(stack_peek(stack, &out) == false);
    assert(stack_pop(stack, &out) == false);
    assert(stack_is_empty(stack) == true);

    stack_discard(stack);
}

void test_stack_pop_until_empty(void) {
    struct Stack *stack = stack_create();

    int a = 1, b = 2;

    stack_push(stack, &a, sizeof(int));
    stack_push(stack, &b, sizeof(int));

    int out;

    assert(stack_pop(stack, &out) == true);
    assert(stack_pop(stack, &out) == true);

    // now truly empty
    assert(stack_is_empty(stack) == true);
    assert(stack_size(stack) == 0);

    // further pop should fail consistently
    assert(stack_pop(stack, &out) == false);

    stack_discard(stack);
}

void test_stack_peek_after_pop(void) {
    struct Stack *stack = stack_create();

    int a = 10, b = 20;

    stack_push(stack, &a, sizeof(int));
    stack_push(stack, &b, sizeof(int));

    int out;

    stack_pop(stack, &out); // removes 20

    assert(stack_peek(stack, &out) == true);
    assert(out == 10);

    stack_discard(stack);
}

void test_stack_mixed_operations(void) {
    struct Stack *stack = stack_create();

    int a = 1, b = 2, c = 3;

    stack_push(stack, &a, sizeof(int));
    stack_push(stack, &b, sizeof(int));

    int out;

    stack_pop(stack, &out);
    assert(out == 2);

    stack_push(stack, &c, sizeof(int));

    stack_pop(stack, &out);
    assert(out == 3);

    stack_pop(stack, &out);
    assert(out == 1);

    assert(stack_is_empty(stack));

    stack_discard(stack);
}

void test_stack_large_push(void) {
    struct Stack *stack = stack_create();

    for (int i = 0; i < 1000; i++) {
        stack_push(stack, &i, sizeof(int));
    }

    assert(stack_size(stack) == 1000);

    for (int i = 999; i >= 0; i--) {
        int out;
        stack_pop(stack, &out);
        assert(out == i);
    }

    assert(stack_is_empty(stack));

    stack_discard(stack);
}

void test_stack_reuse_after_empty(void) {
    struct Stack *stack = stack_create();

    int a = 1, b = 2;

    stack_push(stack, &a, sizeof(int));
    stack_pop(stack, &a);

    assert(stack_is_empty(stack));

    stack_push(stack, &b, sizeof(int));

    int out;
    assert(stack_peek(stack, &out) == true);
    assert(out == 2);

    stack_discard(stack);
}

void test_stack_multiple_underflow(void) {
    struct Stack *stack = stack_create();

    int out;

    assert(stack_pop(stack, &out) == false);
    assert(stack_pop(stack, &out) == false);
    assert(stack_pop(stack, &out) == false);

    assert(stack_peek(stack, &out) == false);
    assert(stack_peek(stack, &out) == false);

    stack_discard(stack);
}

typedef struct {
    int x;
    int y;
} Point;

void test_stack_struct_type(void) {
    struct Stack *stack = stack_create();

    Point a = {1, 2};
    Point b = {3, 4};

    stack_push(stack, &a, sizeof(Point));
    stack_push(stack, &b, sizeof(Point));

    Point out;

    stack_pop(stack, &out);
    assert(out.x == 3 && out.y == 4);

    stack_pop(stack, &out);
    assert(out.x == 1 && out.y == 2);

    stack_discard(stack);
}

void test_stack_string_pointer(void) {
    struct Stack *stack = stack_create();

    char *a = "hello";
    char *b = "world";

    stack_push(stack, &a, sizeof(char*));
    stack_push(stack, &b, sizeof(char*));

    char *out;

    stack_pop(stack, &out);
    assert(strcmp(out, "world") == 0);

    stack_pop(stack, &out);
    assert(strcmp(out, "hello") == 0);

    stack_discard(stack);
}