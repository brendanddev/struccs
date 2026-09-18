// set.c
// A generic implementation of a set backed by a hash table.
// Brendan Dileo - 2026

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "set.h"

// Stand-in value stored against every key; the set only cares about presence.
static const char SET_DUMMY = 1;

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

bool set_add(Set *set, const void *value) {
    if (!ht_contains(set->table, value, set->element_size)) {
        ht_insert(set->table, value, set->element_size, (const void*) &SET_DUMMY, sizeof(char));
        return true;
    }
    return false;
}

bool set_remove(Set *set, const void *value) {
    return ht_remove(set->table, value, set->element_size);
}

bool set_contains(const Set *set, const void *value) {
    return ht_contains(set->table, value, set->element_size);
}

int set_size(const Set *set) {
    return ht_size(set->table);
}

void set_print(const Set *set, void (*printfunc)(const void*, const void*)) {
    ht_print(set->table, printfunc);
}

void set_discard(Set *set) {
    if (set != NULL) {
        ht_discard(set->table);
        free(set);
    }
}
