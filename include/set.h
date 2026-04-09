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

/**
 * Defines the Set struct type
 */
typedef struct Set {

} Set;

Set* set_create();
void set_discard(Set *set);

#endif
