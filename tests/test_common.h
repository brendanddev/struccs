
/// test_common.h
/// Brendan Dileo - November 4 2025

#ifndef TEST_COMMON_H
#define TEST_COMMON_H
#include "../generic_array/generic_array.h"
#include "../linked_list/linked_list.h"


// Factory functions
struct GenericArray* create_int_array(void);
struct GenericArray* create_int_array_from_size(int size);

struct LinkedList* create_int_list(void);
struct LinkedList* create_int_list_from_size(int size);


// Print functions
void print_arr_int(struct GenericArray *ga);
void print_int(void *value);

// Comparators
bool compare_int(void *a, void *b);
bool equals_int(void *a, void *b);


#endif