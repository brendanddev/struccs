// linked_list.h
// Header for the generic doubly linked list implementation
// Brendan Dileo - 2025

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node is opaque to callers, its layout lives in linked_list.c.
struct Node;

typedef struct LinkedList {
    int length;
    struct Node *head;
    struct Node *tail;
} LinkedList;

// Allocates an empty list. Caller frees with ll_discard. Returns NULL on failure.
struct LinkedList* ll_create();
// Prepends a node holding a copy of item_size bytes from value.
void ll_insert(struct LinkedList *list, const void *value, size_t item_size);
// Appends a node holding a copy of item_size bytes from value.
void ll_insert_tail(struct LinkedList *list, const void *value, size_t item_size);
// Inserts a copy of value at position index (0..length). Out-of-range is a no-op.
void ll_insert_at(struct LinkedList *list, const void *value, size_t item_size, int index);
// Removes the head node. No-op on an empty list.
void ll_remove(struct LinkedList *list);
// Removes the tail node. No-op on an empty list.
void ll_remove_tail(struct LinkedList *list);
// Removes the node at index. Out-of-range is a no-op.
void ll_remove_at(struct LinkedList *list, int index);
// Copies the value at index into out. Returns false if index is out of range.
bool ll_get(const struct LinkedList *list, int index, void *out);
// Overwrites the value at index from in. Returns false if index is out of range.
bool ll_set(struct LinkedList *list, int index, const void *in);
// Returns the index of the first node for which comparator(node_value, item) is
// true, or -1 if none.
int ll_find(const struct LinkedList *list, const void *item, bool (* comparator)(const void*, const void*));
// Returns true if any node satisfies comparator(node_value, item).
bool ll_contains(const struct LinkedList *list, const void *item, bool (* comparator)(const void*, const void*));
// Frees every node but keeps the list struct for reuse.
void ll_clear(struct LinkedList *list);
// Returns a newly allocated deep copy; caller frees it with ll_discard.
struct LinkedList* ll_copy(const struct LinkedList *orig);
// Reverses the list in place (swapping each node's next/prev, then head/tail).
void ll_reverse(struct LinkedList *list);
// Returns the number of nodes.
int ll_size(const struct LinkedList *list);
// Returns true if the list has no nodes.
bool ll_is_empty(const struct LinkedList *list);
// Frees every node and the list struct.
void ll_discard(struct LinkedList *list);
// Applies print_fn to each value from head to tail.
void ll_print(const struct LinkedList *list, void (* print_fn)(const void*));
// Dumps each node's address and links. Assumes an int payload.
void ll_debug(const struct LinkedList *list);
// In-place bubble sort by value; comparator returns true when the first value
// should sort after the second.
void ll_bsort(struct LinkedList *list, bool (* comparator)(const void*, const void*));

#endif
