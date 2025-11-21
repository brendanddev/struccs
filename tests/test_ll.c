#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "test_common.h"
#include "../linked_list/linked_list.h"


/// test_ll.c
/// The test suite for the LinkedList implementation
/// Brendan Dileo, November 17 2025


void test_get_set(struct LinkedList *list);
void test_find_contains(struct LinkedList *list);
void test_copy(struct LinkedList *list);
void test_swapping();
void test_sorting(struct LinkedList *list);

int main() {

    // struct LinkedList *linked_list = create_int_list();
    // ll_print(linked_list, print_int);

    // struct LinkedList *linked_list_chr = create_chr_list();
    // ll_print(linked_list_chr, print_chr);

    // ll_reverse(linked_list);
    // ll_print(linked_list, print_int);

    // test_get_set(linked_list);
    // test_find_contains(linked_list);
    // test_sorting(linked_list);
    // test_copy(linked_list);

    test_swapping();
   





    

    // Free memory allocated by the linked list
    // ll_discard(linked_list);
    // linked_list = NULL;
    return 0;
}



// Test get and set functions
void test_get_set(struct LinkedList *list) {
    int num;
    if (ll_get(list, 1, &num)) {    // should work
        printf("Value at index 1: %d\n", num);
    } else {
        printf("Could not get the item\n");
    }

    if (ll_get(list, list->length + 1, &num)) { // should fail
        printf("Value at index %d: %d\n", list->length + 1, num);
    } else {
        printf("Could not get the item\n");
    }

    
    int value = 3454;
    if (ll_set(list, 1, &value)) {      // should work
        printf("Set the item at index 1 to: %d\n", value);
    } else {
        printf("Failed to set the item\n");
    }

    if (ll_set(list, -1, &value)) {      // should fail
        printf("Set the item at index 1 to: %d\n", value);
    } else {
        printf("Failed to set the item\n");
    }
}

// Test find and contains functions
void test_find_contains(struct LinkedList *list) {
    int num = 100;
    int found = ll_find(list, &num, compare_int);
    if (found != -1) {
        printf("Found %d at index: %d\n", num, found);
    } else {
        printf("Could not find the item\n");
    }

    int value = 709;
    if (ll_contains(list, &value, compare_int)) {
        printf("Found the item %d\n", value);
    } else {
        printf("The list does not contain %d\n", value);
    }
}

void test_copy(struct LinkedList *list) {

    struct LinkedList *copy = ll_copy(list);
    printf("Copied List: \n");
    ll_print(copy, print_int);

}

// Tests the node swapping logic
void test_swapping() {
    
    struct LinkedList *list = ll_init();

    int num = 100;
    struct Node *node = ll_init_node(&num, sizeof(int));

    int num2 = 200;
    struct Node *node2 = ll_init_node(&num2, sizeof(int));

    int num3 = 300;
    struct Node *node3 = ll_init_node(&num3, sizeof(int));

    ll_insert(node, list);
    ll_insert(node2, list);
    ll_insert(node3, list);
    ll_print(list, print_int);

    swap_node_positions(list, node, node2);
    ll_print(list, print_int);

    swap_node_positions(list, node3, node2);
    ll_print(list, print_int);

    ll_discard(list);

}

// Tests the bubble sort function
void test_sorting(struct LinkedList *list) {
    ll_bsort(list, greater_than);
    ll_print(list, print_int);
}