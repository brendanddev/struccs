
/// test_common.h
/// Brendan Dileo - November 4 2025

#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include "../generic_array/generic_array.h"
#include "../linked_list/linked_list.h"


// Linked List factory functions
struct LinkedList* create_int_list(void);
struct LinkedList* create_int_list_from_size(int size);


// Print functions
void print_int(void *value);

// Comparators
bool compare_int(void *a, void *b);
bool greater_than(void *a, void *b);

#endif