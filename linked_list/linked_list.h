
/// linked_list.h
/// Brendan Dileo - November 11 2025

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


// Defines the Node struct type
typedef struct Node {
    int value;                      // The value stored in the Node
    struct Node *next;              // A pointer to the next Node in the list
} Node;


// Defines the LinkedList struct type
typedef struct LinkedList {
    int length;                     // The length of the LinkedList
    struct Node *head;              // A pointer to the head Node (first element)

} LinkedList;


struct Node * _node_init(int value);
struct LinkedList * _init();
void _insert(struct Node *node, struct LinkedList *list);
void _insert_tail(struct Node *node, struct LinkedList *list);
void _insert_at(struct Node *node, struct LinkedList *list, int index);
void _remove(struct LinkedList *list, int value);
void _remove_at(struct LinkedList *list, int index);

void _print(struct LinkedList *list);
void _node_discard(struct Node *node);
void _discard(struct LinkedList *linked_list);

#endif