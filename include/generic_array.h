/**
 * generic_array.h
 * Header for the generic array implementation.
 * Brendan Dileo - 2025
 */

#ifndef GENERIC_ARRAY_H
#define GENERIC_ARRAY_H
// Percent-full below which the backing array is shrunk on removal.
#define SHRINK_THRESHOLD 5.0

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct GenericArray {
    void *ptrData;
    size_t item_size;
    int capacity;
    int initial_capacity;       // floor used when shrinking
    int length;
} GenericArray;


// Allocates an empty array for items of item_size bytes. Caller frees with
// ga_discard. Exits the process on allocation failure.
struct GenericArray* ga_init(size_t item_size);
// Copies item_size bytes from item_ptr onto the end, growing if full. Returns true.
bool ga_append(struct GenericArray *ga, void *item_ptr);
// Inserts a copy of in_ptr at index (0..length), shifting later items right.
// Returns false if index is out of range.
bool ga_add(struct GenericArray *ga, int index, void *in_ptr);
// Copies the item at index into out_ptr. Returns false if index is out of range.
bool ga_get(struct GenericArray *ga, int index, void *out_ptr);
// Overwrites the item at index with in_ptr. Returns false if index is out of range.
bool ga_set(struct GenericArray *ga, int index, void *in_ptr);
// Returns the index of the first item for which comparator(item_ptr, elem) is
// true, or -1 if none.
int ga_find(struct GenericArray *ga, void *item_ptr, bool (* comparator)(void*, void*));
// Drops the last item, shrinking the backing array if it falls below
// SHRINK_THRESHOLD. Returns false if already empty.
bool ga_remove_last(struct GenericArray *ga);
// Drops the item at index and shifts later items left. Returns false if index
// is out of range.
bool ga_remove_at(struct GenericArray *ga, int index);
// Returns true if any item satisfies funcptr(elem, trgtptr).
bool ga_contains(struct GenericArray *ga, bool (*funcptr)(void*, void*), void *trgtptr);
// Resets length to 0; the backing array and its bytes are left in place.
bool ga_clear(struct GenericArray *ga);
// Returns the number of items stored.
int ga_size(struct GenericArray *ga);
// Returns the current capacity of the backing array.
int ga_capacity(struct GenericArray *ga);
// Returns how full the array is, as a percentage (length / capacity * 100).
double ga_usage(struct GenericArray *ga);
// Frees the backing array and the struct.
void ga_discard(struct GenericArray *ga);
// Applies print_fn to each item in order.
void ga_print(struct GenericArray *ga, void (* print_fn)(void*));
// In-place bubble sort; comparator returns true when its first arg should sort
// after its second.
void ga_sort(struct GenericArray *ga, bool (* comparator)(void*, void*));
// Reverses the items in place.
void ga_reverse(struct GenericArray *ga);
// Returns a newly allocated deep copy; caller frees it with ga_discard.
struct GenericArray* ga_copy(struct GenericArray *ga);
// Binary search over an already-sorted array. comparator must return a value
// that is exactly -1, 0, or 1 (not just a sign). Returns true if found.
bool ga_binary_find(struct GenericArray *ga, void *item_ptr, int (* comparator)(void*, void*));

#endif
