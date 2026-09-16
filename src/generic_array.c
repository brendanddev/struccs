// generic_array.c
// A generic implementation of a resizing array.
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "generic_array.h"

// Prototypes
static void resize(struct GenericArray *ga);
static void shrink(struct GenericArray *ga);
static void shift_right(struct GenericArray *ga, int index);
static void shift_left(struct GenericArray *ga, int index);
static void swap(struct GenericArray *ga, void *val1, void *val2);

struct GenericArray * ga_init(size_t item_size) {
    struct GenericArray *ga = NULL;
    ga = malloc(sizeof(struct GenericArray));
    if (ga == NULL) {
        return NULL;
    }

    ga->initial_capacity = 4;
    ga->capacity = ga->initial_capacity;
    ga->length = 0;
    ga->item_size = item_size;

    void *pTmp = malloc(item_size * ga->capacity);
    if (pTmp == NULL) {
        free(ga);
        return NULL;
    }
    ga->ptrData = pTmp;
    return ga;
}

bool ga_append(struct GenericArray *ga, void *itemPtr) {
    if (ga->length == ga->capacity) {
        resize(ga);
    }

    void *dest = (char *)ga->ptrData + ga->length * ga->item_size;
    memcpy(dest, itemPtr, ga->item_size);
    ga->length++;
    return true;
}

bool ga_add(struct GenericArray *ga, int index, void *in_ptr) {
    if (index < 0 || index > ga->length) return false;

    if (ga->length == ga->capacity) {
        resize(ga);
    }

    shift_right(ga, index);

    void *dest_ptr = (char *) ga->ptrData + index * ga->item_size;
    memcpy(dest_ptr, in_ptr, ga->item_size);
    ga->length++;
    return true;
}

bool ga_get(struct GenericArray *ga, int index, void *out_ptr) {
    if (index < 0 || index >= ga->length) return false;

    void *dest = (char *)ga->ptrData + index * ga->item_size;
    memcpy(out_ptr, dest, ga->item_size);
    return true;
}

bool ga_set(struct GenericArray *ga, int index, void *in_ptr) {
    if (index < 0 || index >= ga->length) return false;

    void *dest = (char *) ga->ptrData + index * ga->item_size;
    memcpy(dest, in_ptr, ga->item_size);
    return true;
}

int ga_find(struct GenericArray *ga, void *item_ptr, bool (*comparator)(void*, void*)) {
    for (int i = 0; i < ga->length; i++) {
        void *curr = (char *) ga->ptrData + i * ga->item_size;

        if (comparator(item_ptr, curr)) {
            return i;
        }
    }
    return -1;
}

bool ga_remove_last(struct GenericArray *ga) {
    if (!ga || ga->length == 0) return false;
    ga->length--;

    if (ga_usage(ga) < SHRINK_THRESHOLD) {
        shrink(ga);
    }
    return true;
}

bool ga_remove_at(struct GenericArray *ga, int index) {
    if (index < 0 || index >= ga->length) return false;
    ga->length--;

    if (ga_usage(ga) < SHRINK_THRESHOLD) {
        shrink(ga);
    }

    shift_left(ga, index);
    return true;
}

bool ga_contains(struct GenericArray *ga, bool (*funcptr)(void*, void*), void *trgtptr) {
    for (int i = 0; i < ga->length; i++) {
        void *curr = (char *) ga->ptrData + i * ga->item_size;
        if (funcptr(curr, trgtptr)) {
            return true;
        }
    }
    return false;
}

// Length only; the backing bytes are left untouched and get overwritten as new
// items are appended.
bool ga_clear(struct GenericArray *ga) {
    if (!ga) return false;
    ga->length = 0;
    return true;
}

int ga_size(struct GenericArray *ga) {
    return ga->length;
}

int ga_capacity(struct GenericArray *ga) {
    return ga->capacity;
}

double ga_usage(struct GenericArray *ga) {
    double usage = (double) ga->length / ga->capacity * 100;
    return usage;
}

void ga_discard(struct GenericArray *ga) {
    if (ga != NULL) {
        free(ga->ptrData);
        free(ga);
    }
}

void ga_print(struct GenericArray *ga, void (* print_fn)(void*)) {
    if (ga->length == 0) return;
    for (int i = 0; i < ga->length; i++) {
        void *curr = (char *) ga->ptrData + i * ga->item_size;
        print_fn(curr);
    }
}

// Bubble sort, bailing out early on the first pass that makes no swaps.
void ga_sort(struct GenericArray *ga, bool (* comparator)(void*, void*)) {
    bool is_swapped;
    for (int i = 0; i < ga->length - 1; i++) {
        is_swapped = false;
        for (int j = 0; j < ga->length - i - 1; j++) {
            void *curr = (char *) ga->ptrData + j * ga->item_size;
            void *next = (char *) ga->ptrData + (j + 1) * ga->item_size;
            if (comparator(curr, next)) {
                swap(ga, curr, next);
                is_swapped = true;
            }
        }
        if (is_swapped == false) {
            break;
        }
    }
}

void ga_reverse(struct GenericArray *ga) {
    for (int i = 0; i < ga->length / 2; i++) {
        void *front = (char *) ga->ptrData + i * ga->item_size;
        void *back = (char *) ga->ptrData + (ga->length - i - 1) * ga->item_size;
        swap(ga, front, back);
    }
}

struct GenericArray* ga_copy(struct GenericArray *ga) {
    struct GenericArray *ga_copy = NULL;
    ga_copy = malloc(sizeof(struct GenericArray));

    void *new_ga_ptrData = NULL;
    new_ga_ptrData = malloc(ga->item_size * ga->capacity);

    memcpy(ga_copy, ga, sizeof(struct GenericArray));
    memcpy(new_ga_ptrData, ga->ptrData, ga->item_size * ga->length);
    ga_copy->ptrData = new_ga_ptrData;
    return ga_copy;
}

bool ga_binary_find(struct GenericArray *ga, void *item_ptr, int (* comparator)(void*, void*)) {
    int low = 0;
    int high = ga->length - 1;

    while (low <= high) {
        int mid_idx = low + (high - low) / 2;
        void *mid = (char *) ga->ptrData + mid_idx * ga->item_size;

        int cmp = comparator(mid, item_ptr);

        // Relies on comparator returning exactly -1/0/1: any other negative
        // value would fall through to the high = mid - 1 branch.
        if (cmp == 0) {
            return true;
        } else if (cmp == -1) {
            low = mid_idx + 1;
        } else {
            high = mid_idx - 1;
        }
    }
    return false;
}


// Doubles the backing array; exits the process on allocation failure.
static void resize(struct GenericArray *ga) {
    int new_capacity = ga->capacity * 2;

    void *tmp_ptr = NULL;
    tmp_ptr = realloc(ga->ptrData, new_capacity * ga->item_size);
    if (tmp_ptr == NULL) {
        fprintf(stderr, "Memory allocation failed during resizing!\n");
        exit(EXIT_FAILURE);
    }

    ga->capacity = new_capacity;
    ga->ptrData = tmp_ptr;
}

// Shrinks an underused array: to 2.5x the live count, or 1.5x initial_capacity
// once the count drops that low. Exits the process on allocation failure.
static void shrink(struct GenericArray *ga) {
    int new_capacity;
    if (ga->length > ga->initial_capacity) {
        new_capacity = (int)(ga->length * 2.5);
    } else {
        new_capacity = (int)(ga->initial_capacity * 1.5);
    }

    void *tmp = NULL;
    tmp = realloc(ga->ptrData, new_capacity * ga->item_size);
    if (tmp == NULL) {
        fprintf(stderr, "Memory allocation failed during shrinking!\n");
        exit(EXIT_FAILURE);
    }
    ga->capacity = new_capacity;
    ga->ptrData = tmp;
}

// Walks from the tail so each slot is copied forward before it is overwritten.
static void shift_right(struct GenericArray *ga, int index) {
    for (int i = ga->length - 1; i >= index; i--) {
        void *src = (char *) ga->ptrData + i * ga->item_size;
        void *dest = (char *) ga->ptrData + (i + 1) * ga->item_size;
        memcpy(dest, src, ga->item_size);
    }
}

// Walks from index forward, closing the gap left by a removed item.
static void shift_left(struct GenericArray *ga, int index) {
    for (int i = index; i < ga->length - 1; i++) {
        void *src = (char *) ga->ptrData + (i + 1) * ga->item_size;
        void *dest = (char *) ga->ptrData + i * ga->item_size;
        memcpy(dest, src, ga->item_size);
    }
}

static void swap(struct GenericArray *ga, void *val1, void *val2) {
    void *temp = NULL;
    temp = malloc(ga->item_size);

    memcpy(temp, val1, ga->item_size);
    memcpy(val1, val2, ga->item_size);
    memcpy(val2, temp, ga->item_size);
    free(temp);
}
