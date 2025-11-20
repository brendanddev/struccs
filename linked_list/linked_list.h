
/// linked_list.h
/// Header for the generic doubly linked list implementation
/// Brendan Dileo - November 14 2025


#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Definess the doubly Node struct type
typedef struct Node {
    void *value;                        // Pointer to the value stored in this node
    size_t item_size;                   // The size of the item stored in the node
    struct Node *next;                  // Pointer to the next node in the list
    struct Node *prev;                  // Pointer to the previous node in the list
} Node;

// Defines the LinkedList struct type
typedef struct LinkedList {
    int length;
    struct Node *head;                  // Pointer to the head node (first element)
    struct Node *tail;                  // Pointer to the tail node (last element)
} LinkedList;


struct Node* ll_init_node(void *val, size_t size);
struct LinkedList* ll_init();
void ll_insert(struct Node *node, struct LinkedList *list);
void ll_insert_tail(struct Node *node, struct LinkedList *list);
void ll_insert_at(struct Node *node, struct LinkedList *list, int index);
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
void ll_bsort(struct LinkedList *list, bool (* comparator)(void*, void*));
void swap_nodes(struct Node *a, struct Node *b);
int ll_size(struct LinkedList *list);
bool ll_is_empty(struct LinkedList *list);
void ll_discard_node(struct Node *node);
void ll_discard_all_nodes(struct LinkedList *list);
void ll_discard(struct LinkedList *list);
void ll_print(struct LinkedList *list, void (* print_fn)(void*));
void ll_debug(struct LinkedList *list);

void swap_node_positions(struct LinkedList *list, struct Node *a, struct Node *b);

#endif