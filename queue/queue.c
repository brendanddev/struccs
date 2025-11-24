#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"


/// queue.c
/// A generic implementation of a queue backed by linked nodes
/// Brendan Dileo - November 24 2025


// Defines the Node struct type
typedef struct Node {
    void *value;            // Pointer to the value stored in the node
    size_t item_size;       // The size of the item stored in this node
    struct Node *next;      // Pointer to the next node in the queue
} Node;


// Prototypes
static struct Node* queue_create_node(void *val, size_t size);
static void queue_discard_node(struct Node *node);
static void queue_discard_all_nodes(struct Queue *queue);


