#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../linked_list/linked_list.h"


/// test_ll.c
/// Testing and developmental file for the LinkedList implementation
/// Brendan Dileo - November 11 2025

// Address: 0x0 == NULL


int main() {

    // Create a new Node and LinkedList
    struct Node *node = _node_init(10);
    struct Node *node2 = _node_init(100);
    struct Node *node3 = _node_init(999);
    struct LinkedList *linked_list = _init();

    printf("Node Value: %d, Next Pointer: %p\n", node->value, node->next);
    printf("LinkedList Length: %d, Head Pointer: %p\n", linked_list->length, linked_list->head);

    printf("Head Insertion...\n");
    _insert(node, linked_list);
    _insert(node2, linked_list);
    _print(linked_list);

    printf("Tail Insertion...\n");
    _insert_tail(node3, linked_list);
    _print(linked_list);





    return 0;

}