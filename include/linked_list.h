/**
 * linked_list.h
 * Header for the generic doubly linked list implementation
 * Brendan Dileo - 2025
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Forward declaration of the struct Node stored in the linked list
struct Node;

/**
 * Defines the LinkedList (doubly) struct type
 */
typedef struct LinkedList {
    int length;
    struct Node *head;                  // Pointer to the head node (first element)
    struct Node *tail;                  // Pointer to the tail node (last element)
} LinkedList;

struct LinkedList* ll_create();
void ll_insert(struct LinkedList *list, void *value, size_t item_size);
void ll_insert_tail(struct LinkedList *list, void *value, size_t item_size);
void ll_insert_at(struct LinkedList *list, void *value, size_t item_size, int index);
void ll_remove(struct LinkedList *list);
void ll_remove_tail(struct LinkedList *list);
void ll_remove_at(struct LinkedList *list, int index);
bool ll_get(struct LinkedList *list, int index, void *out);
bool ll_set(struct LinkedList *list, int index, void *in);
int ll_find(struct LinkedList *list, void *item, bool (* comparator)(void*, void*));
bool ll_contains(struct LinkedList *list, void *item, bool (* comparator)(void*, void*));
void ll_clear(struct LinkedList *list);
struct LinkedList* ll_copy(struct LinkedList *orig);
void ll_reverse(struct LinkedList *list);
int ll_size(struct LinkedList *list);
bool ll_is_empty(struct LinkedList *list);
void ll_discard(struct LinkedList *list);
void ll_print(struct LinkedList *list, void (* print_fn)(void*));
void ll_debug(struct LinkedList *list);
void ll_bsort(struct LinkedList *list, bool (* comparator)(void*, void*));

#endif