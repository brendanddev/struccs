/**
 * test_queue.c
 * The test suite for the Queue implementation.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}

int main() {
    struct Queue *queue = queue_create();
    printf("Initial State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value = 5000;
    queue_enqueue(queue, &value, sizeof(int));
    queue_print(queue, print_int);
    queue_debug(queue);

    int value2 = 999;
    queue_enqueue(queue, &value2, sizeof(int));
    queue_print(queue, print_int);
    queue_debug(queue);

    int value3 = 159;
    queue_enqueue(queue, &value3, sizeof(int));
    queue_print(queue, print_int);
    queue_debug(queue);

    int value4 = 9;
    queue_enqueue(queue, &value4, sizeof(int));
    queue_print(queue, print_int);
    queue_debug(queue);

    int head;
    if (queue_peek(queue, &head)) {
        printf("Peeked the value: %d at the head of the queue\n", head);
    } else {
        printf("Could not peek the queue\n");
    }
    queue_print(queue, print_int);
    queue_debug(queue);

    int dequeue;
    if (queue_dequeue(queue, &dequeue)) {
        printf("Dequeued the value: %d at the head of the queue\n", dequeue);
    } else {
        printf("Could not dequeue from the queue\n");
    }
    queue_print(queue, print_int);

    int dequeue2;
    if (queue_dequeue(queue, &dequeue2)) {
        printf("Dequeued the value: %d at the head of the queue\n", dequeue2);
    } else {
        printf("Could not dequeue from the queue\n");
    }
    queue_print(queue, print_int);

    queue_clear(queue);
    queue_print(queue, print_int);
    printf("Queue Size: %d\n", queue_length(queue));
    queue_debug(queue);

    queue_discard(queue);
    queue = NULL;
    return 0;
}