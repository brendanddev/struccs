

/// utils.h
/// Brendan Dileo - November 4 2025

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct GenericArray * create_int_array();
struct GenericArray * create_dbl_array();
void print_arr_int(struct GenericArray *ga);
void print_arr_dbl(struct GenericArray *ga);

#endif