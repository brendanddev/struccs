#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../linked_list/linked_list.h"


/// test_ll.c
/// Testing and developmental file for the LinkedList implementation
/// Brendan Dileo - November 11 2025

// Address: 0x0 == NULL


void print_int_linked_list(struct LinkedList *list);

int main() {

    // Create a new LinkedList
    struct LinkedList *linked_list = _init();
    printf("LinkedList - Length: %d, Head: %p, Tail: %p\n", linked_list->length, linked_list->head, linked_list->tail);

    // Create a new Node
    int val = 100;
    void *ptr = &val;
    struct Node *node = _init_node(ptr, sizeof(int));
    printf("Node - Item Size: %zu, Next: %p\n", node->item_size, node->next);

    
    // Insert at head
    _insert(node, linked_list);
    print_int_linked_list(linked_list);

    int val2 = 450;
    void *ptr2 = &val2;
    struct Node *node2 = _init_node(ptr2, sizeof(int));
    _insert(node2, linked_list);
    print_int_linked_list(linked_list);

    int val3 = 9734;
    void *ptr3 = &val3;
    struct Node *node3 = _init_node(ptr3, sizeof(int));
    _insert(node3, linked_list);
    print_int_linked_list(linked_list);


    _discard_node(node);
    node = NULL;
    _discard_node(node2);
    node2 = NULL;
    _discard_node(node3);
    node3 = NULL;

    _discard(linked_list);
    linked_list = NULL;





    return 0;
}


void print_int_linked_list(struct LinkedList *list) {
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        printf("[%d] ", * (int *) current->value);
    }
    printf("\n");
}