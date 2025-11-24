#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../queue/queue.h"


/// test_queue.c
/// The test suite for the Queue implementation
/// Brendan Dileo, November 24 2025


void print_int(void *value) {
    printf("[%d] ", * (int *) value);
}

int main() {


    struct Queue *queue = queue_create();
    printf("Initial State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value = 5000;
    queue_enqueue(queue, &value, sizeof(int));
    printf("State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value2 = 999;
    queue_enqueue(queue, &value2, sizeof(int));
    printf("State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    int value3 = 159;
    queue_enqueue(queue, &value3, sizeof(int));
    printf("State of Queue: Length: %d, Head: %p, Tail: %p\n", queue->length, queue->head, queue->tail);

    queue_print(queue, print_int);




    return 0;
}