/**
 * queue.c
 * A generic implementation of a queue backed by linked nodes.
 * Brendan Dileo - 2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "queue.h"

// Each node owns a heap copy of its value (item_size bytes).
typedef struct Node {
    void *value;
    size_t item_size;
    struct Node *next;
} Node;

// Prototypes
static struct Node* queue_create_node(void *val, size_t size);
static void queue_discard_node(struct Node *node);
static void queue_discard_all_nodes(struct Queue *queue);

struct Queue* queue_create() {
    struct Queue *queue = malloc(sizeof(struct Queue));
    if (queue == NULL) return NULL;

    queue->length = 0;
    queue->head = NULL;
    queue->tail = NULL;
    return queue;
}

void queue_enqueue(struct Queue *queue, void *val, size_t item_size) {
    struct Node *node = queue_create_node(val, item_size);
    if (queue_is_empty(queue)) {
        // First node is both head and tail.
        queue->tail = node;
        queue->head = node;
        queue->length++;
        return;
    } else {
        queue->tail->next = node;
        queue->tail = node;
        queue->length++;
    }
}

bool queue_peek(struct Queue *queue, void *out) {
    if (queue_is_empty(queue)) return false;
    memcpy(out, queue->head->value, queue->head->item_size);
    return true;
}

bool queue_dequeue(struct Queue *queue, void *out) {
    if (queue_is_empty(queue)) return false;

    memcpy(out, queue->head->value, queue->head->item_size);

    struct Node *temp = queue->head->next;
    queue_discard_node(queue->head);
    queue->head = temp;
    queue->length--;
    return true;
}

bool queue_is_empty(struct Queue *queue) {
    if (queue->head == NULL) return true;
    return false;
}

int queue_length(struct Queue *queue) {
    return queue->length;
}

void queue_clear(struct Queue *queue) {
    if (queue_is_empty(queue)) return;
    queue_discard_all_nodes(queue);
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;
}

void queue_print(struct Queue *queue, void (* print_fn)(void*)) {
    struct Node *current = queue->head;
    while (current != NULL) {
        print_fn(current->value);
        current = current->next;
    }
    printf("\n");
}

void queue_debug(struct Queue *queue) {
    if (queue_is_empty(queue)) return;
    printf("Queue: Length: %d, Head: %p, Head Next: %p, Tail: %p, Tail Next: %p\n", queue_length(queue), queue->head, queue->head->next, queue->tail, queue->tail->next);
}

void queue_discard(struct Queue *queue) {
    if (queue != NULL) {
        queue_discard_all_nodes(queue);
        free(queue);
    }
}


// Private helper functions - linkage limited to this file


// Deep-copies size bytes from val; the returned node owns the copy.
static struct Node* queue_create_node(void *val, size_t size) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    node->item_size = size;
    node->next = NULL;

    node->value = malloc(node->item_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->value, val, node->item_size);
    return node;
}

static void queue_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

static void queue_discard_all_nodes(struct Queue *queue) {
    struct Node *current = queue->head;
    while (current != NULL) {
        // Grab next before freeing current.
        struct Node *next = current->next;
        queue_discard_node(current);
        current = next;
    }
}
