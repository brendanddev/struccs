#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"

/// heap.c
/// A generic implementation of a heap backed by an array
/// Brendan Dileo - December 12 2025


// Prototypes
static void heap_swap(void *a, void *b, size_t element_size);
static void heap_print_rec(struct Heap *heap, void (* print_fn)(void*), int index, int depth);