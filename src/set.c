/**
 * set.c
 * A generic implementation of a set backed by a hash table.
 * Brendan Dileo - 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

static const char SET_DUMMY = 1;

/**
 * Creates and returns a new Set.
 */
Set* set_create(size_t element_size) {
    Set *set = malloc(sizeof(Set));
    if (set == NULL) return NULL;

    set->element_size = element_size;
    set->table = ht_create();

    if (set->table == NULL) {
        free(set);
        return NULL;
    }

    return set;
}

/**
 * Inserts a new value into the set if it does not already exist.
 * 
 * @return true if the value did not exist in the set and was inserted, otherwise false.
 */
bool set_add(Set *set, void *value) {
    if (!ht_contains(set->table, value, set->element_size)) {
        ht_insert(set->table, value, set->element_size, (void*) &SET_DUMMY, sizeof(char));
        return true;
    }
    return false;
}

/**
 * Removes a value from the set if it exists.
 * 
 * @return true if the value was removed, false otherwise.
 */
bool set_remove(Set *set, void *value) {
    return ht_remove(set->table, value, set->element_size);
}

/**
 * Checks if the Set contains a given value.
 * 
 * @return true if the value is found in the set, otherwise false.
 */
bool set_contains(Set *set, void *value) {
    return ht_contains(set->table, value, set->element_size);
}

/**
 * Returns the size (length) of the set.
 */
int set_size(Set *set) {
    return ht_size(set->table);
}

/**
 * Prints the contents of the set.
 */
void set_print(Set *set, void (*printfunc)(void*, void*)) {
    ht_print(set->table, printfunc);
}

/**
 * Frees the memory previous allocated by the set.
 */
void set_discard(Set *set) {
    if (set != NULL) {
        ht_discard(set->table);
        free(set);
    }
}
