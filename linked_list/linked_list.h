
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
    int length;
    struct Node *head;              // A pointer to the head Node (first element)

} LinkedList;







#endif