
/// stack.h
/// Header for the generic queue implementation backed by linked nodes
/// Brendan Dileo - November 24 2025


#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Forward declaration of the struct Node stored in the queue
struct Node;


// Defines the Queue struct type
typedef struct Queue {
    struct Node *head;          // Pointer to the head node of the queue
    struct Node *tail;          // Pointer to the tail node of the queue
    int length;                 // The length of the queue
} Queue;


struct Queue* queue_create();
void queue_enqueue(struct Queue *queue, void *val, size_t item_size);
bool queue_peek(struct Queue *queue, void *out);
bool queue_dequeue(struct Queue *queue, void *out);
bool queue_is_empty(struct Queue *queue);
int queue_length(struct Queue *queue);
void queue_print(struct Queue *queue, void (* print_fn)(void*));
void queue_debug(struct Queue *queue);

void queue_clear();
void queue_discard();


#endif