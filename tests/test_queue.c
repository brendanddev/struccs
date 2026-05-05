/**
 * test_queue.c
 * The test suite for the Queue implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "queue.h"

// Prototypes
void test_queue_create(void);
void test_queue_enqueue(void);
void test_queue_dequeue(void);
void test_queue_peek(void);
void test_queue_fifo_order(void);
void test_queue_empty_behavior(void);
void test_queue_underflow(void);
void test_queue_reuse_after_empty(void);
void test_queue_size_consistency(void);
void test_queue_large_operations(void);
void test_queue_struct_type(void);
void test_queue_string_pointer(void);

int main(void) {
    test_queue_create();
    test_queue_enqueue();
    test_queue_dequeue();
    test_queue_peek();
    test_queue_fifo_order();
    test_queue_empty_behavior();
    test_queue_underflow();
    test_queue_reuse_after_empty();
    test_queue_size_consistency();
    test_queue_large_operations();
    test_queue_struct_type();
    test_queue_string_pointer();

    printf("All Queue tests passed.\n");
    return 0;
}

void test_queue_create(void) {
    struct Queue *q = queue_create();

    assert(q != NULL);
    assert(queue_length(q) == 0);

    queue_discard(q);
}

void test_queue_enqueue(void) {
    struct Queue *q = queue_create();

    int a = 10;
    int b = 20;

    queue_enqueue(q, &a, sizeof(int));
    assert(queue_length(q) == 1);

    queue_enqueue(q, &b, sizeof(int));
    assert(queue_length(q) == 2);

    queue_discard(q);
}

void test_queue_dequeue(void) {
    struct Queue *q = queue_create();

    int a = 42;
    queue_enqueue(q, &a, sizeof(int));

    int out;
    assert(queue_dequeue(q, &out) == true);
    assert(out == 42);

    assert(queue_length(q) == 0);

    queue_discard(q);
}

void test_queue_peek(void) {
    struct Queue *q = queue_create();

    int a = 99;
    queue_enqueue(q, &a, sizeof(int));

    int out;
    assert(queue_peek(q, &out) == true);
    assert(out == 99);

    assert(queue_length(q) == 1);

    queue_discard(q);
}

void test_queue_fifo_order(void) {
    struct Queue *q = queue_create();

    int a = 1, b = 2, c = 3;

    queue_enqueue(q, &a, sizeof(int));
    queue_enqueue(q, &b, sizeof(int));
    queue_enqueue(q, &c, sizeof(int));

    int out;

    queue_dequeue(q, &out);
    assert(out == 1);

    queue_dequeue(q, &out);
    assert(out == 2);

    queue_dequeue(q, &out);
    assert(out == 3);

    queue_discard(q);
}

void test_queue_empty_behavior(void) {
    struct Queue *q = queue_create();

    int out;

    assert(queue_dequeue(q, &out) == false);
    assert(queue_peek(q, &out) == false);
    assert(queue_length(q) == 0);

    queue_discard(q);
}

void test_queue_underflow(void) {
    struct Queue *q = queue_create();

    int out;

    assert(queue_dequeue(q, &out) == false);
    assert(queue_dequeue(q, &out) == false);
    assert(queue_peek(q, &out) == false);

    queue_discard(q);
}

void test_queue_reuse_after_empty(void) {
    struct Queue *q = queue_create();

    int a = 1, b = 2, out;

    queue_enqueue(q, &a, sizeof(int));
    queue_dequeue(q, &out);

    assert(queue_length(q) == 0);

    queue_enqueue(q, &b, sizeof(int));
    assert(queue_peek(q, &out) == true);
    assert(out == 2);

    queue_discard(q);
}

void test_queue_size_consistency(void) {
    struct Queue *q = queue_create();

    int a = 1, b = 2, out;

    queue_enqueue(q, &a, sizeof(int));
    queue_enqueue(q, &b, sizeof(int));

    assert(queue_length(q) == 2);

    queue_dequeue(q, &out);
    assert(queue_length(q) == 1);

    queue_dequeue(q, &out);
    assert(queue_length(q) == 0);

    queue_discard(q);
}

void test_queue_large_operations(void) {
    struct Queue *q = queue_create();

    for (int i = 0; i < 1000; i++) {
        queue_enqueue(q, &i, sizeof(int));
    }

    assert(queue_length(q) == 1000);

    for (int i = 0; i < 1000; i++) {
        int out;
        queue_dequeue(q, &out);
        assert(out == i);
    }

    assert(queue_length(q) == 0);

    queue_discard(q);
}

typedef struct {
    int x;
    int y;
} Point;

void test_queue_struct_type(void) {
    struct Queue *q = queue_create();

    Point a = {1, 2};
    Point b = {3, 4};

    queue_enqueue(q, &a, sizeof(Point));
    queue_enqueue(q, &b, sizeof(Point));

    Point out;

    assert(queue_dequeue(q, &out) == true);
    assert(out.x == 1 && out.y == 2);

    assert(queue_dequeue(q, &out) == true);
    assert(out.x == 3 && out.y == 4);

    queue_discard(q);
}

void test_queue_string_pointer(void) {
    struct Queue *q = queue_create();

    char *a = "hello";
    char *b = "world";

    queue_enqueue(q, &a, sizeof(char*));
    queue_enqueue(q, &b, sizeof(char*));

    char *out;

    assert(queue_dequeue(q, &out) == true);
    assert(strcmp(out, "hello") == 0);

    assert(queue_dequeue(q, &out) == true);
    assert(strcmp(out, "world") == 0);

    queue_discard(q);
}