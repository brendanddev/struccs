#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_common.h"
#include "../linked_list/linked_list.h"


/// test_ll.c
/// The test suite for the LinkedList implementation
/// Brendan Dileo, November 17 2025


int main() {

    struct LinkedList *linked_list = create_int_list();
    ll_print(linked_list, print_int);

    ll_reverse(linked_list);
    ll_print(linked_list, print_int);



    struct LinkedList *linked_list2 = ll_init();

    int num1 = 100;
    int num2 = 999;
    struct Node *node1 = ll_init_node(&num1, sizeof(int));
    struct Node *node2 = ll_init_node(&num2, sizeof(int));
    ll_insert_tail(node1, linked_list2);
    ll_insert_tail(node2, linked_list2);
    ll_print(linked_list2, print_int);

    swap_nodes(node1, node2);
    ll_print(linked_list2, print_int);

    swap_nodes(node1, node2);
    ll_print(linked_list2, print_int);

















    
    // struct LinkedList *linked_list = ll_init();
    // printf("LinkedList - Length: %d, Head: %p, Tail: %p\n", linked_list->length, linked_list->head, linked_list->tail);

    // int value = 100;
    // void *ptr = &value;
    // struct Node *node = ll_init_node(ptr, sizeof(int));
    // printf("Node - Item Size: %zu, Next: %p, Prev: %p\n", node->item_size, node->next, node->prev);

    // ll_insert(node, linked_list);
    // printf("LinkedList - Length: %d, Head: %p, Tail: %p\n", linked_list->length, linked_list->head, linked_list->tail);


    // int value2 = 67;
    // void *ptr2 = &value2;
    // struct Node *node2 = ll_init_node(ptr2, sizeof(int));
    // ll_insert(node2, linked_list);
    // printf("LinkedList - Length: %d, Head: %p, Tail: %p\n", linked_list->length, linked_list->head, linked_list->tail);

    // ll_print(linked_list, print_int);

    // int value3 = 1600;
    // void *ptr3 = &value3;
    // struct Node *node3 = ll_init_node(ptr3, sizeof(int));
    // ll_insert(node3, linked_list);
    // ll_print(linked_list, print_int);


    // printf("DEBUG PRINT: \n");
    // ll_debug(linked_list);

    // int value4 = 888;
    // void *ptr4 = &value4;
    // struct Node *node4 = ll_init_node(ptr4, sizeof(int));
    // ll_insert_tail(node4, linked_list);

    // int value5 = 78365;
    // void *ptr5 = &value5;
    // struct Node *node5 = ll_init_node(ptr5, sizeof(int));
    // ll_insert_tail(node5, linked_list);

    // ll_print(linked_list, print_int);

    // // Insert at
    // int value6 = 10;
    // void *ptr6 = &value6;
    // struct Node *node6 = ll_init_node(ptr6, sizeof(int));
    // printf("Inserting at index 1...\n");
    // ll_insert_at(node6, linked_list, 1);
    // ll_print(linked_list, print_int);

    // int value7 = 999;
    // void *ptr7 = &value7;
    // struct Node *node7 = ll_init_node(ptr7, sizeof(int));
    // printf("Inserting at index 1...\n");
    // ll_insert_at(node7, linked_list, 1);
    // ll_print(linked_list, print_int);


    // // Get item
    // int val;
    // if (ll_get(linked_list, 1, &val)) {
    //     printf("Located value at index 1: %d\n", val);
    // } else {
    //     printf("Failed to get item at index 1\n");
    // }

    // int val2;
    // if (ll_get(linked_list, 2, &val2)) {
    //     printf("Located value at index 2: %d\n", val2);
    // } else {
    //     printf("Failed to get item at index 1\n");
    // }

    // int val3;
    // int end = linked_list->length - 1;
    // if (ll_get(linked_list, end, &val3)) {
    //     printf("Located the value at index %d: %d\n", end, val3);
    // } else {
    //     printf("Failed to get item at index: %d\n", end);
    // }

    // int val4;
    // int end2 = linked_list->length;
    // if (ll_get(linked_list, end2, &val4)) {
    //     printf("Located the value at index %d: %d\n", end2, val4);
    // } else {
    //     printf("Failed to get item at index: %d\n", end2);
    // }

    // // Set an item
    // ll_print(linked_list, print_int);
    // int num = 338;
    // if (ll_set(linked_list, 1, &num)) {
    //     printf("Set the nodes value at index 1 to: %d\n", num);
    // } else {
    //     printf("Failed to set the value of the node\n");
    // }
    // ll_print(linked_list, print_int);

    // ll_print(linked_list, print_int);
    // int num2 = 5;
    // if (ll_set(linked_list, linked_list->length - 1, &num2)) {
    //     printf("Set the nodes value at index 1 to: %d\n", num2);
    // } else {
    //     printf("Failed to set the value of the node\n");
    // }
    // ll_print(linked_list, print_int);

    // ll_print(linked_list, print_int);
    // int num3 = 21;
    // if (ll_set(linked_list, linked_list->length, &num3)) {
    //     printf("Set the nodes value at index 1 to: %d\n", num3);
    // } else {
    //     printf("Failed to set the value of the node\n");
    // }
    // ll_print(linked_list, print_int);


    // // Find an item by value
    // int to_find = 1;
    // int found = ll_find(linked_list, &to_find, compare_int);
    // printf("The index of the item found (or -1 if not found): %d\n", found);

    // int to_find2 = 5;
    // int found2 = ll_find(linked_list, &to_find2, compare_int);
    // printf("The index of the item found (or -1 if not found): %d\n", found2);

    // int to_find3 = 888;
    // int found3 = ll_find(linked_list, &to_find3, compare_int);
    // printf("The index of the item found (or -1 if not found): %d\n", found3);

    // // Contains an item
    // bool contains_num = ll_contains(linked_list, &to_find, compare_int);
    // printf("The list contains %d: %d\n", to_find, contains_num);

    // bool contains_num2 = ll_contains(linked_list, &to_find2, compare_int);
    // printf("The list contains %d: %d\n", to_find2, contains_num2);

    // bool contains_num3 = ll_contains(linked_list, &to_find3, compare_int);
    // printf("The list contains %d: %d\n", to_find3, contains_num3);

    // // Copy the linked list
    // printf("Current Linked List: \n");
    // ll_print(linked_list, print_int);

    // printf("Copy of LinkedList: \n");
    // struct LinkedList *linked_list_copy = ll_copy(linked_list);
    // ll_print(linked_list_copy, print_int);

    // Clear the linked list
    // ll_clear(linked_list);
    // ll_print(linked_list, print_int);
    // if (linked_list->length == 0) printf("The list is empty!\n");

    // Removal
    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);

    // printf("Length: %d\n", linked_list->length);
    // ll_remove(linked_list);
    // ll_print(linked_list, print_int);
    // ll_debug(linked_list);


    // Tail removal
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_debug(linked_list);

    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);
    // ll_remove_tail(linked_list);
    // ll_print(linked_list, print_int);

    // Remove at 
    // printf("Size before removal: %d\n", ll_size(linked_list));
    // printf("Linked List before removals: \n");
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 1);
    // ll_print(linked_list, print_int);
    // ll_remove_at(linked_list, 0);
    // ll_print(linked_list, print_int);
    // printf("Size after removals: %d\n", ll_size(linked_list));

    

    // Free memory allocated by the linked list
    ll_discard(linked_list);
    linked_list = NULL;
    return 0;
}