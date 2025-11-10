

/// test_helpers.h
/// Brendan Dileo - November 4 2025

#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include "../generic_array/generic_array.h"
#include <stdbool.h>

struct GenericArray * create_int_array();
struct GenericArray * create_int_array_from_size(int size);
struct GenericArray * create_dbl_array();
struct GenericArray * create_chr_array();
bool contains_int(void *a, void *b);
int is_less_than(void *a, void *b);
bool equals_int(void *a, void *b);
bool contains_dbl(void *a, void *b);
void print_arr_int(struct GenericArray *ga);
void print_arr_dbl(struct GenericArray *ga);
void print_arr_chr(struct GenericArray *ga);

#endif