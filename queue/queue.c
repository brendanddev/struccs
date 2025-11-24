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


// Creates a new queue
struct Queue* queue_create() {
    // Allocate memory for the queue itself and handle allocation failure
    struct Queue *queue = malloc(sizeof(struct Queue));
    if (queue == NULL) return NULL;

    // Set initial length and pointers to head/tail
    queue->length = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

// Adds an item to the tail of the queue
void queue_enqueue(struct Queue *queue, void *val, size_t item_size) {
    
    struct Node *node = queue_create_node(val, item_size);
    
    if (queue_is_empty(queue)) {
        queue->tail = node;
        queue->head = node;
        queue->length++;
        return;
    } else {
        queue->head = queue->tail;
        queue->tail = node;
        queue->tail->next = NULL;
        queue->head->next = queue->tail;
        queue->length++;
    }
}

// Returns a boolean value indicating whether the queue is empty or not
bool queue_is_empty(struct Queue *queue) {
    if (queue->head == NULL) return true;
    return false;
}





// Private helper functions, linkage limited to this file


// Creates a new node to be stored in the queue
static struct Node* queue_create_node(void *val, size_t size) {

    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Set size of item stored in node and initialize next pointer
    node->item_size = size;
    node->next = NULL;

    // Allocate memory for the value to be stored in the node
    // and handle allocation failure
    node->value = malloc(node->item_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy memory pointed to by `val` into the memory pointed to by the node
    memcpy(node->value, val, node->item_size);
    return node;
}

// Frees the memory occupied by a single node
static void queue_discard_node(struct Node *node) {
    if (node != NULL) {
        // Free memory occupied by the value stored in the node
        // and the node itself
        free(node->value);
        free(node);
    }
}

// Frees the memory occupied by each node in the queue
static void queue_discard_all_nodes(struct Queue *queue) {
    struct Node *current = queue->head;
    while (current != NULL) {
        // Store pointer to next node in queue before freeing to prevent
        // losing reference to the rest of queue
        struct Node *next = current->next;
        queue_discard_node(current);
        current = next;
    }
}
