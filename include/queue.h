// queue.h
// Header for the generic queue implementation backed by linked nodes.
// Brendan Dileo - 2025

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node is opaque to callers; its layout lives in queue.c.
struct Node;

typedef struct Queue {
    struct Node *head;
    struct Node *tail;
    int length;
} Queue;

// Allocates an empty queue. Caller frees with queue_discard. NULL on failure.
struct Queue* queue_create();
// Appends a node holding a copy of item_size bytes from val (adds at the tail).
void queue_enqueue(struct Queue *queue, void *val, size_t item_size);
// Copies the head value into out without removing it. False if the queue is empty.
bool queue_peek(struct Queue *queue, void *out);
// Copies the head value into out and removes the head. False if the queue is empty.
bool queue_dequeue(struct Queue *queue, void *out);
// Returns true if the queue has no nodes.
bool queue_is_empty(struct Queue *queue);
// Returns the number of nodes in the queue.
int queue_length(struct Queue *queue);
// Frees every node but keeps the queue struct for reuse.
void queue_clear(struct Queue *queue);
// Frees every node and the queue struct.
void queue_discard(struct Queue *queue);
// Applies print_fn to each value from head to tail.
void queue_print(struct Queue *queue, void (* print_fn)(void*));
// Prints the queue's length and its head/tail links for debugging.
void queue_debug(struct Queue *queue);

#endif
