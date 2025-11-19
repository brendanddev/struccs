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

   





    

    // Free memory allocated by the linked list
    ll_discard(linked_list);
    linked_list = NULL;
    return 0;
}