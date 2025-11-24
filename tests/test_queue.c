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





    return 0;
}