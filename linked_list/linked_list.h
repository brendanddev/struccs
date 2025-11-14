
/// linked_list.h
//// Header for the generic Doubly LinkedList implementation
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
    struct Node *prev;                  // Pointer to the previous Node in the Linked List
} Node;

// Defines the LinkedList struct type
typedef struct LinkedList {
    int length;                         // Length of the Linked List
    struct Node *head;                  // Pointer to the head Node (first item)
    struct Node *tail;                  // Pointer to the tail Node (last item)
} LinkedList;


struct Node * _init_node(void *val, size_t size);
struct LinkedList * _init();
bool _insert(struct Node *node, struct LinkedList *list);
void _insert_tail(struct Node *node, struct LinkedList *list);
void _insert_at(struct Node *node, struct LinkedList *list, int index);

bool _is_empty(struct LinkedList *list);
int _size(struct LinkedList *list);
void _discard_node(struct Node *node);
void _discard(struct LinkedList *linked_list);


#endif