// set.h
// Header for the generic set implementation, backed by a hash table.
// Brendan Dileo - 2026

#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "hash_table.h"

// Thin wrapper over HashTable: stores each element as a key mapped to a dummy
// value. element_size is the byte width of every element.
typedef struct Set {
    size_t element_size;
    HashTable *table;
} Set;

// Allocates an empty set for elements of element_size bytes. Caller frees with
// set_discard. Returns NULL on allocation failure.
Set* set_create(size_t element_size);
// Adds a copy of value. Returns true if it was inserted, false if already present.
bool set_add(Set *set, void *value);
// Removes value. Returns true if it was present.
bool set_remove(Set *set, void *value);
// Returns true if value is in the set.
bool set_contains(Set *set, void *value);
// Returns the number of elements.
int set_size(const Set *set);
// Applies printfunc(element, dummy_value) to every element.
void set_print(Set *set, void (*printfunc)(void*, void*));
// Frees the backing table and the set struct.
void set_discard(Set *set);

#endif
