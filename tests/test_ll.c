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
    struct Node *node4 = _node_init(1003);
    struct Node *node5 = _node_init(55);
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
    _insert_tail(node4, linked_list);
    _print(linked_list);

    printf("Head Insertion... (again)\n");
    _insert(node5, linked_list);
    _print(linked_list);

    printf("Inserting At [Index = %d]...\n", linked_list->length);
    struct Node *node6 = _node_init(1234);
    _insert_at(node6, linked_list, linked_list->length);
    _print(linked_list);

    printf("Inserting at [Index = %d]...\n", 0);
    struct Node *node7 = _node_init(888);
    _insert_at(node7, linked_list, 0);
    _print(linked_list);

    // printf("Removing tail of LinkedList...\n");
    // _remove_tail(linked_list);
    // _print(linked_list);
    // _remove_tail(linked_list);
    // _print(linked_list);
    // _remove_tail(linked_list);
    // _print(linked_list);

    int removeidx = 3;
    printf("Removing at index = %d\n", removeidx);
    _remove_at(linked_list, removeidx);
    _print(linked_list);
    printf("Removing at index = 0...\n");
    _remove_at(linked_list, 0);
    _print(linked_list);
    printf("Removing at index = %d...\n", linked_list->length - 1);
    _remove_at(linked_list, linked_list->length - 1);
    _print(linked_list);





    // printf("Removing head of LinkedList...\n");
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);
    // _remove(linked_list);
    // _print(linked_list);



    // Nodes are not freed yet!!!!
    // _discard(linked_list);
    // linked_list = NULL;
    // _node_discard(node);
    // node = NULL;
    // _node_discard(node2);
    // node2 = NULL;
    // _node_discard(node3);
    // node3 = NULL;
    // _node_discard(node4);
    // node4 = NULL;
    // _node_discard(node5);
    // node5 = NULL;



    return 0;
}