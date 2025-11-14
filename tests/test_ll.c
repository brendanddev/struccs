#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../linked_list/linked_list.h"


/// test_ll.c
/// Testing and developmental file for the LinkedList implementation
/// Brendan Dileo - November 11 2025

// Address: 0x0 == NULL


void print_int_linked_list(struct LinkedList *list);
bool compare_int(void *a, void *b);

int main() {

    // Create a new LinkedList
    struct LinkedList *linked_list = _init();
    printf("LinkedList - Length: %d, Head: %p, Tail: %p\n", linked_list->length, linked_list->head, linked_list->tail);

    // Create a new Node
    int val = 100;
    void *ptr = &val;
    struct Node *node = _init_node(ptr, sizeof(int));
    printf("Node - Item Size: %zu, Next: %p\n", node->item_size, node->next);

    // Check if list is empty, it should be
    printf("The list is empty: %d\n", _is_empty(linked_list));

    // Print current length/size, should be 0
    printf("LinkedList Length: %d\n", _size(linked_list));

    
    // Insert at head
    _insert(node, linked_list);
    print_int_linked_list(linked_list);


    // Insert at head
    int val2 = 450;
    void *ptr2 = &val2;
    struct Node *node2 = _init_node(ptr2, sizeof(int));
    _insert(node2, linked_list);
    print_int_linked_list(linked_list);

    // Insert at head
    int val3 = 9734;
    void *ptr3 = &val3;
    struct Node *node3 = _init_node(ptr3, sizeof(int));
    _insert(node3, linked_list);
    print_int_linked_list(linked_list);


    // Insert at tail
    int val4 = 83272;
    void *ptr4 = &val4;
    struct Node *node4 = _init_node(ptr4, sizeof(int));
    _insert_tail(node4, linked_list);
    print_int_linked_list(linked_list);

    // Insert at tail
    int val5 = 832;
    void *ptr5 = &val5;
    struct Node *node5 = _init_node(ptr5, sizeof(int));
    _insert_tail(node5, linked_list);
    print_int_linked_list(linked_list);

    // Insert at tail
    int val6 = 1;
    void *ptr6 = &val6;
    struct Node *node6 = _init_node(ptr6, sizeof(int));
    _insert_tail(node6, linked_list);
    print_int_linked_list(linked_list);

    // Insert at head
    int val7 = 4006;
    void *ptr7 = &val7;
    struct Node *node7 = _init_node(ptr7, sizeof(int));
    _insert(node7, linked_list);
    print_int_linked_list(linked_list);


    // Insert at index
    int val8 = 888;
    void *ptr8 = &val8;
    struct Node *node8 = _init_node(ptr8, sizeof(int));
    _insert_at(node8, linked_list, 1);
    print_int_linked_list(linked_list);


    // Insert at index
    int val9 = 23429;
    void *ptr9 = &val9;
    struct Node *node9 = _init_node(ptr9, sizeof(int));
    _insert_at(node9, linked_list, 5);
    print_int_linked_list(linked_list);


    // Remove head node
    _remove(linked_list);
    print_int_linked_list(linked_list);

    _remove(linked_list);
    print_int_linked_list(linked_list);

    _remove(linked_list);
    print_int_linked_list(linked_list);


    // Remove tail node
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);
    // _remove_tail(linked_list);
    // print_int_linked_list(linked_list);         // should be empty at this point


    // Remove at index
    _remove_at(linked_list, 4);
    print_int_linked_list(linked_list);
    // _remove_at(linked_list, 3);
    // print_int_linked_list(linked_list);
    // _remove_at(linked_list, 2);
    // print_int_linked_list(linked_list);
    // _remove_at(linked_list, 1);
    // print_int_linked_list(linked_list);
    // _remove_at(linked_list, 0);
    // print_int_linked_list(linked_list);


    // Get an item at a index
    int get_val;
    if (_get(linked_list, 0, &get_val)) {
        printf("Item at index 0: %d\n", get_val);
    } else {
        printf("Could not get item\n");
    }

    int get_val1;
    if (_get(linked_list, 1, &get_val1)) {
        printf("Item at index 1: %d\n", get_val1);
    } else {
        printf("Could not get item\n");
    }

    int get_val2;
    if (_get(linked_list, -1, &get_val2)) {
        printf("Item at index -1: %d\n", get_val2);
    } else {
        printf("Could not get item\n");
    }

    int get_val3;
    if (_get(linked_list, 10, &get_val3)) {
        printf("Item at index 10: %d\n", get_val3);
    } else {
        printf("Could not get item\n");
    }


    // Set a item at index
    int set_val = 82;
    if (_set(linked_list, 1, &set_val)) {
        printf("Item set at index 1: %d\n", set_val);
    } else {
        printf("Could not set item\n");
    }
    print_int_linked_list(linked_list);

    int set_val2 = 1000;
    if (_set(linked_list, 2, &set_val2)) {
        printf("Item set at index 2: %d\n", set_val2);
    } else {
        printf("Could not set item\n");
    }
    print_int_linked_list(linked_list);

    if (_set(linked_list, -1, &set_val2)) {
        printf("Item set at index 2: %d\n", set_val2);
    } else {
        printf("Could not set item\n");
    }

    if (_set(linked_list, 100, &set_val2)) {
        printf("Item set at index 2: %d\n", set_val2);
    } else {
        printf("Could not set item\n");
    }


    // Find an item
    int it = 82;
    int is_found = _find(linked_list, &it, compare_int);
    printf("The index of the item: %d\n", is_found);

    int it2 = 1;
    int is_found2 = _find(linked_list, &it2, compare_int);
    printf("The index of the item: %d\n", is_found2);

    int it3 = 150;
    int is_found3 = _find(linked_list, &it3, compare_int);
    printf("The index of the item: %d\n", is_found3);


    // Check if the linked list contains an item
    int item = 1000;
    bool contains_item = _contains(linked_list, &item, compare_int);
    printf("The list contains %d: %d\n", item, contains_item);

    int item2 = 5;
    bool contains_item2 = _contains(linked_list, &item2, compare_int);
    printf("The list contains %d: %d\n", item2, contains_item2);





    




    // Free all nodes
    _discard_all_nodes(linked_list);

    // Free linked list
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

bool compare_int(void *a, void *b) {
    if ((* (int *) a) == (* (int *) b)) return true;
    return false;
}