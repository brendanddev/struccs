#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binary_tree.h"


/// binary_tree.c
/// A generic implementation of a complete binary tree
/// Brendan Dileo - December 17 2025


// Prototypes
static void print_recursive(struct BinaryTree *tree, int index, int depth, void (*print_fn)(void*));
static bool resize(struct BinaryTree *tree);
static void swap(void *a, void *b, size_t element_size);
static int parent_index(int index);
static int left_child_index(int index);
static int right_child_index(int index);


// Creates a new binary tree storing elements of the provided size
struct BinaryTree* bt_create(size_t element_size) {

    // Allocate memory for the binary tree struct itself and handle allocation failure
    struct BinaryTree *tree = malloc(sizeof(struct BinaryTree));
    if (tree == NULL) return NULL;

    // Set initial capacity, length and size of elements stored in the tree
    tree->capacity = 12;
    tree->length = 0;
    tree->element_size = element_size;

    // Allocate memory for the underlying array that will hold the tree elements
    // and handle allocation failure
    tree->elements = malloc(tree->capacity * tree->element_size);
    if (tree->elements == NULL) {
        free(tree);
        return NULL;
    }
    return tree;
}

// Inserts the provided value at the next available position in the tree
void bt_insert(struct BinaryTree *tree, void *value) {

    // Check if a resize is needed
    if (tree->length >= tree->capacity) {
        resize(tree);
    }
    // Get the pointer to the next available position in the tree
    // then copy the value into the trees array
    void *curr = (char*) tree->elements + tree->length * tree->element_size;
    memcpy(curr, value, tree->element_size);
    tree->length++;
}

// Removes the element at the provided index in the binary tree
void bt_remove(struct BinaryTree *tree, int index) {
    if (index < 0 || index >= tree->length) return;

    // Get pointer to the element being removed and
    // the last element in the tree
    void *curr = (char*) tree->elements + index * tree->element_size;
    void *last = (char*) tree->elements + (tree->length - 1) * tree->element_size;
     
    // Swap the two values and decrement length to remove the value
    swap(curr, last, tree->element_size);
    tree->length--;
}

// Returns a pointer to the element at the provided index in the tree
bool bt_get(struct BinaryTree *tree, int index, void *out) {
    if (index < 0 || index >= tree->length) return false;

    // Get pointer to the element at the provided index, and
    // copy raw bytes between memory locations to return the value to user
    void *current = (char*) tree->elements + index * tree->element_size;
    memcpy(out, current, tree->element_size);
    return true;
}

// Sets the value of the element at the provided index to the provided value
bool bt_set(struct BinaryTree *tree, int index, void *value) {
    if (index < 0 || index >= tree->length) return false;

    void *current = (char*) tree->elements + index * tree->element_size;
    memcpy(current, value, tree->element_size);
    return true;
}


// Checks if the binary tree contains the provided value
bool bt_contains(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*)) {
    for (int i = 0; i < tree->length; i++) {
        void *current = (char*) tree->elements + i * tree->element_size;
        if (comparator(current, value) == 0) {
            return true;
        }
    }
    return false;
}

// Finds and returns the index of the provided value in the tree
int bt_find(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*)) {
    for (int i = 0; i < tree->length; i++) {
        void *current = (char*) tree->elements + i * tree->element_size;
        if (comparator(current, value) == 0) {
            return i;
        }
    }
    return -1;
}

// Returns the height of the binary tree, which is the largest number of edges in a path from the root to a leaf node
int bt_height(struct BinaryTree *tree) {
    if (tree->length == 0) {
        return -1;
    }

    // 
    int height = 0;
    int last = tree->length - 1;

    // Continue while were not at root or reach root
    while (last >= 0) {

        int parent = parent_index(last);    // calc parent to go up from the `last` nod

        height++;   // increment height, reached new level
        last = parent;  // reassign last (currently current) to the parent to keep moving up
    }
    return height;
}

// Returns the number of nodes with no children (leaf) in the binary tree
int bt_leaves(struct BinaryTree *tree) {


}

// Returns the level of a node at the provided index in the binary tree
int bt_levelof(struct BinaryTree *tree, int index) {

}


// Public interface for printing the contents of the binary tree
void bt_print(struct BinaryTree *tree, void (*print_fn)(void*)) {
    if (bt_isempty(tree)) return;
    print_recursive(tree, 0, 0, print_fn);
}

// Recursive helper for printing the contents of the binary tree in a tree-like structure
static void print_recursive(struct BinaryTree *tree, int index, int depth, void (*print_fn)(void*)) {

    // Base case - we reached an index outside of the arrays bounds
    if (index >= tree->length) return;
    
    // Get pointer to the element at the provided index
    void *curr = (char*) tree->elements + index * tree->element_size;

    // Recurse down the right side of the tree first
    // then print the current element with indentation
    // then recurse down the left side of the tree
    print_recursive(tree, right_child_index(index), depth + 1, print_fn);
    for (int i = 0; i < depth; i++) printf("        ");
    print_fn(curr);
    print_recursive(tree, left_child_index(index), depth + 1, print_fn);
}

// Clears the contents of the binary tree
void bt_clear(struct BinaryTree *tree) {
    tree->length = 0;
}

// Returns the current size (length) of the binary tree
int bt_size(struct BinaryTree *tree) {
    return tree->length;
}

// Returns the current capacity of the tree's underlying array
int bt_capacity(struct BinaryTree *tree) {
    return tree->capacity;
}

// Checks if the binary tree is empty
bool bt_isempty(struct BinaryTree *tree) {
    return tree->length == 0;
}

// Frees the memory previously allocated for the binary tree
void bt_discard(struct BinaryTree *tree) {
    if (tree != NULL) {
        free(tree->elements);
        free(tree);
    }
}


// Private helper functions, linkage limited to this file


// Resizes the binary trees internal array to twice the current capacity
static bool resize(struct BinaryTree *tree) {

    // Calculate new capacity
    int new_capacity = tree->capacity * 2;

    // Reallocate more memory for the new larger array and handle allocation failure
    void *temp = realloc(tree->elements, new_capacity * tree->element_size);
    if (temp == NULL) return false;

    // If reallocation succeeds, update the pointer to point to the new larger memory block
    // and set the new capacity of the binary tree
    tree->elements = temp;
    tree->capacity = new_capacity;
    return true;
}

// Swaps the raw bytes at the two memory locations pointed to by the provided pointers
static void swap(void *a, void *b, size_t element_size) {

    // Create a variable length array to hold element_size bytes
    // on the stack
    char temp[element_size];

    // Copy the raw bytes between the memory locations to swap values
    memcpy(temp, a, element_size);
    memcpy(a, b, element_size);
    memcpy(b, temp, element_size);
}

// Returns the array index of the parent of the element at index `index` in the tree
static int parent_index(int index) {
    return (index - 1) / 2;
}

// Returns the array index of the left child of the element at the provided index in the tree
static int left_child_index(int index) {
    return 2 * index + 1;
}

// Returns the array index of the right child of the element at the provided index in the tree
static int right_child_index(int index) {
    return 2 * index + 2;
}