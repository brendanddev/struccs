
/// linked_list.h
//// Header for the generic Singly LinkedList implementation
/// Brendan Dileo - November 11 2025

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines the Node struct type
typedef struct Node {
    void *value;                        // Pointer to the value stored in the Node
    size_t item_size;                   // The size of the item stored in this Node
    struct Node *next;                  // Pointer to the next Node in the Linked List
} Node;

// Defines the LinkedList struct type
typedef struct LinkedList {
    int length;                         // Length of the Linked List
    struct Node *head;                  // Pointer to the head Node (first item)
    struct Node *tail;                  // Pointer to the tail Node (last item)
} LinkedList;


struct Node * _init_node(void *val, size_t size);
struct LinkedList * _init();
void _insert(struct Node *node, struct LinkedList *list);
void _insert_tail(struct Node *node, struct LinkedList *list);
void _insert_at(struct Node *node, struct LinkedList *list, int index);
void _remove(struct LinkedList *list);
void _remove_tail(struct LinkedList *list);
void _remove_at(struct LinkedList *list, int index);
bool _get(struct LinkedList *list, int index, void *out);
bool _set(struct LinkedList *list, int index, void *in);
int _find(struct LinkedList *list, void *item, bool (* comparator)(void*, void*));
bool _contains(struct LinkedList *list, void *item, bool (* comparator)(void*, void*));
void _clear(struct LinkedList *list);
bool _is_empty(struct LinkedList *list);
int _size(struct LinkedList *list);
void _discard_node(struct Node *node);
void _discard_all_nodes(struct LinkedList *list);
void _discard(struct LinkedList *linked_list);
void _print(struct LinkedList *list, void (* print_fn)(void*));


#endif