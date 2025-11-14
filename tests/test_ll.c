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

    // Create a new Node and LinkedList
    struct LinkedList *linked_list = _init();


    int val = 100;
    void *ptr = &val;
    struct Node *node = _init_node(ptr, sizeof(int));
    printf("Value: %d, Item Size: %zu, Next: %p, Previous: %p\n", * (int *) node->value, node->item_size, node->next, node->prev);

    if (_insert(node, linked_list)) {
        printf("Inserted at head...\n");
        printf("Value: %d, Item Size: %zu, Next: %p, Previous: %p\n", * (int *) node->value, node->item_size, node->next, node->prev);
    }

    print_int_linked_list(linked_list);


    int val2 = 999;
    struct Node *node2 = _init_node(&val2, sizeof(int));
    if (_insert(node2, linked_list)) {
        printf("Inserted at head...\n");
        printf("Value: %d, Item Size: %zu, Next: %p, Previous: %p\n", * (int *) node->value, node->item_size, node->next, node->prev);
    }

    print_int_linked_list(linked_list);

    int val3 = 10000;
    struct Node *node3 = _init_node(&val3, sizeof(int));
    if (_insert(node3, linked_list)) {
        printf("Inserted at head...\n");
        printf("Value: %d, Item Size: %zu, Next: %p, Previous: %p\n", * (int *) node->value, node->item_size, node->next, node->prev);
    }

    print_int_linked_list(linked_list);

    // int val4 = 2346;
    // struct Node *node4 = _init_node(&val4, sizeof(int));
    // if (_insert_tail(node4, linked_list)) {
    //     printf("Inserted at tail...\n");
    //     printf("Value: %d, Item Size: %zu, Next: %p, Previous: %p\n", * (int *) node->value, node->item_size, node->next, node->prev);
    // }

    // print_int_linked_list(linked_list);

    _discard_node(node);
    _discard(linked_list);

    return 0;
}


void print_int_linked_list(struct LinkedList *list) {
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        printf("%d ", * (int *) current->value);
    }
    printf("\n");
}