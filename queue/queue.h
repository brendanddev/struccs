
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


#endif