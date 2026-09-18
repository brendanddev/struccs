// binary_tree.c
// A generic implementation of a complete binary tree.
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"

// Prototypes
static void print_recursive(const struct BinaryTree *tree, int index, int depth, void (*print_fn)(const void*));
static bool resize(struct BinaryTree *tree);
static void swap(void *a, void *b, size_t element_size);
static int parent_index(int index);
static int left_child_index(int index);
static int right_child_index(int index);

struct BinaryTree* bt_create(size_t element_size) {
    struct BinaryTree *tree = malloc(sizeof(struct BinaryTree));
    if (tree == NULL) return NULL;

    tree->capacity = 12;
    tree->length = 0;
    tree->element_size = element_size;

    tree->elements = malloc(tree->capacity * tree->element_size);
    if (tree->elements == NULL) {
        free(tree);
        return NULL;
    }
    return tree;
}

void bt_insert(struct BinaryTree *tree, const void *value) {
    if (tree->length >= tree->capacity) {
        resize(tree);
    }

    void *curr = (char*) tree->elements + tree->length * tree->element_size;
    memcpy(curr, value, tree->element_size);
    tree->length++;
}

void bt_remove(struct BinaryTree *tree, int index) {
    if (index < 0 || index >= tree->length) return;

    void *curr = (char*) tree->elements + index * tree->element_size;
    void *last = (char*) tree->elements + (tree->length - 1) * tree->element_size;

    // Overwrite the hole with the last element and drop the last slot.
    swap(curr, last, tree->element_size);
    tree->length--;
}

bool bt_get(const struct BinaryTree *tree, int index, void *out) {
    if (index < 0 || index >= tree->length) return false;

    void *current = (char*) tree->elements + index * tree->element_size;
    memcpy(out, current, tree->element_size);
    return true;
}

bool bt_set(struct BinaryTree *tree, int index, const void *value) {
    if (index < 0 || index >= tree->length) return false;

    void *current = (char*) tree->elements + index * tree->element_size;
    memcpy(current, value, tree->element_size);
    return true;
}

bool bt_contains(const struct BinaryTree *tree, const void *value, int (*comparator)(const void*, const void*)) {
    for (int i = 0; i < tree->length; i++) {
        void *current = (char*) tree->elements + i * tree->element_size;
        if (comparator(current, value) == 0) {
            return true;
        }
    }
    return false;
}

int bt_find(const struct BinaryTree *tree, const void *value, int (*comparator)(const void*, const void*)) {
    for (int i = 0; i < tree->length; i++) {
        void *current = (char*) tree->elements + i * tree->element_size;
        if (comparator(current, value) == 0) {
            return i;
        }
    }
    return -1;
}

int bt_height(const struct BinaryTree *tree) {
    if (bt_isempty(tree)) return -1;

    // The tree is complete, so the last array element sits at maximum depth.
    // Counting parent hops from it back to the root gives the height.
    int height = 0;
    int last = tree->length - 1;

    while (last > 0) {
        int parent = parent_index(last);
        height++;
        last = parent;
    }
    return height;
}

int bt_leaves(const struct BinaryTree *tree) {
    if (bt_isempty(tree)) return 0;

    int current = 0;
    int leaves = 0;

    while (current < tree->length) {
        // In a complete tree a node is a leaf exactly when it has no left child.
        if (left_child_index(current) >= tree->length) {
            leaves++;
        }
        current++;
    }
    return leaves;
}

void bt_print(const struct BinaryTree *tree, void (*print_fn)(const void*)) {
    if (bt_isempty(tree)) return;
    print_recursive(tree, 0, 0, print_fn);
}

static void print_recursive(const struct BinaryTree *tree, int index, int depth, void (*print_fn)(const void*)) {
    if (index >= tree->length) return;

    void *curr = (char*) tree->elements + index * tree->element_size;

    // Reverse in-order (right, node, left) so the output reads as the tree
    // rotated onto its side, with the root flush left and depth shown by indent.
    print_recursive(tree, right_child_index(index), depth + 1, print_fn);
    for (int i = 0; i < depth; i++) printf("        ");
    print_fn(curr);
    print_recursive(tree, left_child_index(index), depth + 1, print_fn);
}

void bt_clear(struct BinaryTree *tree) {
    tree->length = 0;
}

int bt_size(const struct BinaryTree *tree) {
    return tree->length;
}

int bt_capacity(const struct BinaryTree *tree) {
    return tree->capacity;
}

bool bt_isempty(const struct BinaryTree *tree) {
    return tree->length == 0;
}

void bt_discard(struct BinaryTree *tree) {
    if (tree != NULL) {
        free(tree->elements);
        free(tree);
    }
}


// Doubles the backing array. Returns false if reallocation fails (tree unchanged).
static bool resize(struct BinaryTree *tree) {
    int new_capacity = tree->capacity * 2;
    void *temp = realloc(tree->elements, new_capacity * tree->element_size);
    if (temp == NULL) return false;

    tree->elements = temp;
    tree->capacity = new_capacity;
    return true;
}

// Byte-wise swap of two element_size-byte regions.
static void swap(void *a, void *b, size_t element_size) {
    char temp[element_size];

    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);
}

static int parent_index(int index) {
    return (index - 1) / 2;
}

static int left_child_index(int index) {
    return 2 * index + 1;
}

static int right_child_index(int index) {
    return 2 * index + 2;
}
