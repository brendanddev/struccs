#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binarysearch_tree.h"


/// binarysearch_tree.c
/// A generic implementation of a binary search tree
/// Brendan Dileo - December 8 2025


// Defines the Node struct type
typedef struct Node {
    void *value;                // Pointer to the memory where the value is stored
    size_t value_size;          // Number of bytes the value will occupy in memory pointed to for the value
    struct Node *left;          // Pointer to the current nodes left child in the tree
    struct Node *right;         // Pointer to the current nodes right child in the tree
} Node;


// Prototypes
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*));
static struct Node* bst_remove_rec(struct Node *root, void *value, int (*compare)(void*, void*), bool *found);
static bool bst_contains_rec(struct Node *root, void *value, int (*compare)(void*, void*));
static struct Node* bst_search_rec(struct Node *root, void *value, int (*compare)(void*, void*));
static int bst_height_rec(struct Node *root);
static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int depth);  
static void bst_inorder_rec(struct Node *root, void (* print_fn)(void*));
static void bst_postorder_rec(struct Node *root, void (* print_fn)(void*));
static struct Node* bst_get_successor(struct Node *root); 
static struct Node* bst_create_node(void *value, size_t value_size);
static void bst_discard_node(struct Node *node);
static void bst_discard_all_nodes(struct BinarySearchTree *tree);
static void bst_discard_all_nodes_rec(struct Node *root);


// Creates a new binary search tree
struct BinarySearchTree* bst_create() {

    // Allocate memory for the tree itself and handle allocation failure
    struct BinarySearchTree *tree = malloc(sizeof(struct BinarySearchTree));
    if (tree == NULL) return NULL;

    // Set the initial root pointer and length of the tree
    tree->root = NULL;
    tree->length = 0;
    
    return tree;
}

// Public interface for inserting a new value into the binary search tree
void bst_insert(struct BinarySearchTree *tree, void *value, size_t value_size, int (*compare)(void*, void*)) {
    tree->root = bst_insert_rec(tree->root, value, value_size, compare);
    tree->length++;
}

// Recursive helper function for inserting a value into the binary search tree
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*)) {
    
    // Base case - if the root node is empty, return it to insert
    if (root == NULL) {
        return bst_create_node(value, value_size);

    // Compare memory blocks pointed to by the value being inserted and the current node value
    // to see if we need to recurse left in the tree
    } else if (compare(value, root->value) < 0) {

        // Recurse to the left of the tree to insert the value, then assign the returned
        // subtree back to the root nodes left child to maintain the connection, and return
        // root so the caller can update their pointer to this subtree
        root->left = bst_insert_rec(root->left, value, value_size, compare);
        return root;
    // Otherwise recurse right in the tree
    } else {
        root->right = bst_insert_rec(root->right, value, value_size, compare);
        return root;
    }
}

// Public interface for removing a value from the binary search tree
void bst_remove(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) { 
    bool found = false;
    tree->root = bst_remove_rec(tree->root, value, compare, &found);
    if (found) tree->length--;
}

// Recursive helper for removing a value from the binary search tree
static Node* bst_remove_rec(struct Node *root, void *value, int (*compare)(void*, void*), bool *found) { 

    // Base case - we found an empty node
    if (root == NULL) {
        *found = false;
        return root;

    // Check if we found the value to remove
    } else if (compare(value, root->value) == 0) {
        *found = true;

        // Check if the node being removed has no children
        if (root->left == NULL && root->right == NULL) {

            // Remove the node and return the new subtree root back up to the call stack so the 
            // parent can update its child pointer
            bst_discard_node(root);
            root = NULL;
            return root;

        // Check if the node being removed has one child
        } else if (root->left == NULL || root->right == NULL) {

            // Check if left child is not empty
            if (root->left != NULL) {

                // Save pointer to the left child, free the current node, and return the left child
                // back up to the call stack so the parent can update its child pointer
                struct Node *left = root->left;
                bst_discard_node(root);
                root = NULL;
                return left;

            // Otherwise right child is not empty
            } else {
                struct Node *right = root->right;
                bst_discard_node(root);
                root = NULL;
                return right;
            }

        // Otherwise node has two children
        } else {

            // Find the successor node
            struct Node *successor = bst_get_successor(root->right);

            // Copy the value from the successor into the root and 
            // remove the successor itself by recursing down the right side of the tree
            memcpy(root->value, successor->value, root->value_size);
            root->right = bst_remove_rec(root->right, successor->value, compare, found);
            return root;
        }

    // Didnt find the value to remove, need to recurse the tree further
    } else {

        // Check if we need to recurse to the left in the tree
        if (compare(value, root->value) < 0) {

            root->left = bst_remove_rec(root->left, value, compare, found);
            return root;

        // Otherwise recurse to the right
        } else {

            root->right = bst_remove_rec(root->right, value, compare, found);
            return root;
        }
    }
}

// Public interface for checking if the binary search tree contains a value
bool bst_contains(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) {
    if (bst_isempty(tree)) return false;
    return bst_contains_rec(tree->root, value, compare);
}

// Recursive helper for checking if the tree contains a given value
static bool bst_contains_rec(struct Node *root, void *value, int (*compare)(void*, void*)) { 

    // Base case - if we have reached an empty node without finding value its not in the tree
    if (root == NULL) return false;

    // Check if we have found the value
    if (compare(value, root->value) == 0) {
        return true;

    // Check if we need to traverse in the left branch
    } else if (compare(value, root->value) < 0) {
        return bst_contains_rec(root->left, value, compare);

    // Otherwise we need to traverse in the right branch
    } else {
        return bst_contains_rec(root->right, value, compare);
    }
}

// Public interface for searching the binary search tree for a value
struct Node* bst_search(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) {
    if (bst_isempty(tree)) return NULL;
    return bst_search_rec(tree->root, value, compare);
}

// Recursive helper for searching for a value in the tree
static struct Node* bst_search_rec(struct Node *root, void *value, int (*compare)(void*, void*)) {

    // Base case - if we have reached an empty node without finding value, its not in the tree
    if (root == NULL) return NULL;

    // Check if we found the value
    if (compare(value, root->value) == 0) {
        return root;

    // Check if value is less than the value stored in the current node,
    // if it is, traverse left down the tree
    } else if (compare(value, root->value) < 0) {
        return bst_search_rec(root->left, value, compare);

    // Otherwise value is equal to or larger, so traverse right down the tree
    } else {
        return bst_search_rec(root->right, value, compare);
    }
}

// Public interface for finding the height of the binary search tree
int bst_height(struct BinarySearchTree *tree) {
    if (bst_isempty(tree)) return 0;
    return bst_height_rec(tree->root);
}

// Recursive helper for finding the height of the binary search tree, which is the length of the longest path from the root down
// to the deepest leaf node
static int bst_height_rec(struct Node *root) {

    // Base case - we reached an empty node
    if (root == NULL) return 0;

    // Recurse down the left and right side of the tree to get height of both paths
    int left_height = bst_height_rec(root->left);
    int right_height = bst_height_rec(root->right);

    // Each non-NULL node adds 1 to the height as recursion unwinds
    // Return the taller path plus 1 for the current node
    if (left_height > right_height) return left_height + 1;
    return right_height + 1;
}

// Public interface for printing the contents of the binary search tree
void bst_print(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    bst_print_rec(tree->root, print_fn, 0);
}

// Recursive helper function for printing the contents of the binary search tree in order traversal
static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int depth) {

    // Base case - if we hit a empty node, weve hit the end of the branch
    if (root == NULL) return;

    // Print right subtree
    bst_print_rec(root->left, print_fn, depth + 1);

    // Print current node with indentation
    for (int i = 0; i < depth; i++) printf("    ");
    print_fn(root->value);
    printf("\n");

    // Print left subtree
    bst_print_rec(root->right, print_fn, depth + 1);
}

// Public interface for traversing and printing the contents of the tree in-order
void bst_inorder(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    if (bst_isempty(tree)) return;
    bst_inorder_rec(tree->root, print_fn);
}

// Recursive helper for traversing and printing the contents of the tree in-order
static void bst_inorder_rec(struct Node *root, void (* print_fn)(void*)) {

    // Base case - hit an empty node
    if (root == NULL) return;

    // Traverse the tree, first traversing the left side of the tree,
    // the root node, then the right
    bst_inorder_rec(root->left, print_fn);
    print_fn(root->value);
    bst_inorder_rec(root->right, print_fn);
}

// Public interface for traversing and printing the contents of the tree post-order
void bst_postorder(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    if (bst_isempty(tree)) return;
    bst_postorder_rec(tree->root, print_fn);
}

// Recursive helper for traversing and printing the contents of the tree post-order
static void bst_postorder_rec(struct Node *root, void (* print_fn)(void*)) {
}



// Returns the number of nodes in the binary search tree
int bst_size(struct BinarySearchTree *tree) {
    return tree->length;
}

// Checks whether the binary search tree is empty
bool bst_isempty(struct BinarySearchTree *tree) {
    return tree->length == 0;
}

// Clears the contents of the binary search tree
void bst_clear(struct BinarySearchTree *tree) { 
    bst_discard_all_nodes(tree);
    tree->root = NULL;
    tree->length = 0;
}

// Frees the memory previously allocated by all nodes in the tree and the tree itself
void bst_discard(struct BinarySearchTree *tree) {
    if (tree != NULL) {
        bst_discard_all_nodes(tree);
        free(tree);
    }
}



// Private helper functions, linkage limited to this file


// Finds the minumum node in the tree, which when passed a node on the right subtree, returns the successor
static struct Node* bst_get_successor(struct Node *root) {
    if (root->left == NULL) return root;
    return bst_get_successor(root->left);
}

// Creates a new node to be stored in the tree
static struct Node* bst_create_node(void *value, size_t value_size) {
    
    // Allocate memory for the node itself and handle allocation failure
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    // Set size of value to be stored in the node and
    // initial left/right child pointers
    node->value_size = value_size;
    node->left = NULL;
    node->right = NULL;

    // Allocate memory for the value itself stored in the node, store pointer to the address, and
    // handle allocation failure
    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy the raw memory pointed to by the parameter into the memory pointed to by the nodes member
    memcpy(node->value, value, node->value_size);

    return node;
}

// Frees the memory previously allocated by a node
static void bst_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Interface for freeing the memory previously allocated by all nodes in the tree
static void bst_discard_all_nodes(struct BinarySearchTree *tree) { 
    bst_discard_all_nodes_rec(tree->root);
}

// Recursive helper function for freeing the memory allocated by each node in the tree
static void bst_discard_all_nodes_rec(struct Node *root) {

    // Base case - hit an empty node
    if (root == NULL) return;

    // Free left and right child branches of the root node and
    // then free the root node to avoid accessing freed memory
    bst_discard_all_nodes_rec(root->left);
    bst_discard_all_nodes_rec(root->right);
    bst_discard_node(root);
}
