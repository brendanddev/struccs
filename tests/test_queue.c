/**
 * test_queue.c
 * The test suite for the Queue implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "test_utils.h"
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
    TEST(test_queue_create);
    TEST(test_queue_enqueue);
    TEST(test_queue_dequeue);
    TEST(test_queue_peek);
    TEST(test_queue_fifo_order);
    TEST(test_queue_empty_behavior);
    TEST(test_queue_underflow);
    TEST(test_queue_reuse_after_empty);
    TEST(test_queue_size_consistency);
    TEST(test_queue_large_operations);
    TEST(test_queue_struct_type);
    TEST(test_queue_string_pointer);

    return 0;
}

void test_queue_create(void) {
    struct Queue *q = queue_create();

    ASSERT_NOT_NULL(q);
    ASSERT_EQ(queue_length(q), 0);

    queue_discard(q);
}

void test_queue_enqueue(void) {
    struct Queue *q = queue_create();

    int a = 10;
    int b = 20;

    queue_enqueue(q, &a, sizeof(int));
    ASSERT_EQ(queue_length(q), 1);

    queue_enqueue(q, &b, sizeof(int));
    ASSERT_EQ(queue_length(q), 2);

    queue_discard(q);
}

void test_queue_dequeue(void) {
    struct Queue *q = queue_create();

    int a = 42;
    queue_enqueue(q, &a, sizeof(int));

    int out;
    ASSERT_TRUE(queue_dequeue(q, &out));
    ASSERT_EQ(out, 42);

    ASSERT_EQ(queue_length(q), 0);

    queue_discard(q);
}

void test_queue_peek(void) {
    struct Queue *q = queue_create();

    int a = 99;
    queue_enqueue(q, &a, sizeof(int));

    int out;
    ASSERT_TRUE(queue_peek(q, &out));
    ASSERT_EQ(out, 99);

    ASSERT_EQ(queue_length(q), 1);

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
    ASSERT_EQ(out, 1);

    queue_dequeue(q, &out);
    ASSERT_EQ(out, 2);

    queue_dequeue(q, &out);
    ASSERT_EQ(out, 3);

    queue_discard(q);
}

void test_queue_empty_behavior(void) {
    struct Queue *q = queue_create();

    int out;

    ASSERT_FALSE(queue_dequeue(q, &out));
    ASSERT_FALSE(queue_peek(q, &out));
    ASSERT_EQ(queue_length(q), 0);

    queue_discard(q);
}

void test_queue_underflow(void) {
    struct Queue *q = queue_create();

    int out;

    ASSERT_FALSE(queue_dequeue(q, &out));
    ASSERT_FALSE(queue_dequeue(q, &out));
    ASSERT_FALSE(queue_peek(q, &out));

    queue_discard(q);
}

void test_queue_reuse_after_empty(void) {
    struct Queue *q = queue_create();

    int a = 1, b = 2, out;

    queue_enqueue(q, &a, sizeof(int));
    queue_dequeue(q, &out);

    ASSERT_EQ(queue_length(q), 0);

    queue_enqueue(q, &b, sizeof(int));
    ASSERT_TRUE(queue_peek(q, &out));
    ASSERT_EQ(out, 2);

    queue_discard(q);
}

void test_queue_size_consistency(void) {
    struct Queue *q = queue_create();

    int a = 1, b = 2, out;

    queue_enqueue(q, &a, sizeof(int));
    queue_enqueue(q, &b, sizeof(int));

    ASSERT_EQ(queue_length(q), 2);

    queue_dequeue(q, &out);
    ASSERT_EQ(queue_length(q), 1);

    queue_dequeue(q, &out);
    ASSERT_EQ(queue_length(q), 0);

    queue_discard(q);
}

void test_queue_large_operations(void) {
    struct Queue *q = queue_create();

    for (int i = 0; i < 1000; i++) {
        queue_enqueue(q, &i, sizeof(int));
    }

    ASSERT_EQ(queue_length(q), 1000);

    for (int i = 0; i < 1000; i++) {
        int out;
        queue_dequeue(q, &out);
        ASSERT_EQ(out, i);
    }

    ASSERT_EQ(queue_length(q), 0);

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

    ASSERT_TRUE(queue_dequeue(q, &out));
    ASSERT_TRUE(out.x == 1 && out.y == 2);

    ASSERT_TRUE(queue_dequeue(q, &out));
    ASSERT_TRUE(out.x == 3 && out.y == 4);

    queue_discard(q);
}

void test_queue_string_pointer(void) {
    struct Queue *q = queue_create();

    char *a = "hello";
    char *b = "world";

    queue_enqueue(q, &a, sizeof(char*));
    queue_enqueue(q, &b, sizeof(char*));

    char *out;

    ASSERT_TRUE(queue_dequeue(q, &out));
    ASSERT_EQ(strcmp(out, "hello"), 0);

    ASSERT_TRUE(queue_dequeue(q, &out));
    ASSERT_EQ(strcmp(out, "world"), 0);

    queue_discard(q);
}
