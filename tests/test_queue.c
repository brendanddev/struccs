#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../queue/queue.h"


/// test_queue.c
/// The test suite for the Queue implementation
/// Brendan Dileo, November 24 2025


int main() {


    struct Queue *queue = queue_create();
    printf("Initial State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value = 5000;
    queue_enqueue(queue, &value, sizeof(int));
    printf("State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value2 = 999;
    queue_enqueue(queue, &value2, sizeof(int));
    printf("State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    // void queue_enqueue(struct Queue *queue, void *val, size_t item_size) {





    return 0;
}