/**
 * set.h
 * Header for the generic set implementation, backed by a hash table.
 * Brendan Dileo - 2026
 */

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_table.h"

/**
 * Defines the Set struct type
 */
typedef struct Set {
    size_t element_size;
    HashTable *table;
} Set;

Set* set_create(size_t element_size);
bool set_add(Set *set, void *value);
bool set_remove(Set *set, void *value);
bool set_contains(Set *set, void *value);
int set_size(Set *set);
void set_print(Set *set, void (*printfunc)(void*, void*));
void set_discard(Set *set);

#endif
