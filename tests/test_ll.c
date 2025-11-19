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

int main() {

    struct LinkedList *linked_list = create_int_list();
    ll_print(linked_list, print_int);

    ll_reverse(linked_list);
    ll_print(linked_list, print_int);

    test_get_set(linked_list);

   





    

    // Free memory allocated by the linked list
    ll_discard(linked_list);
    linked_list = NULL;
    return 0;
}



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
