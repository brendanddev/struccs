// binarysearch_tree.c
// A generic implementation of a binary search tree
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "binarysearch_tree.h"

// Each node owns a heap copy of its value (value_size bytes).
typedef struct Node {
    void *value;
    size_t value_size;
    struct Node *left;
    struct Node *right;
} Node;


// Prototypes
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*));
static struct Node* bst_remove_rec(struct Node *root, void *value, int (*compare)(void*, void*), bool *found);
static bool bst_contains_rec(struct Node *root, void *value, int (*compare)(void*, void*));
static struct Node* bst_search_rec(struct Node *root, void *value, int (*compare)(void*, void*));
static void* bst_min_rec(struct Node *root);
static void* bst_max_rec(struct Node *root);
static int bst_height_rec(struct Node *root);
static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int depth);
static void bst_inorder_rec(struct Node *root, void (* print_fn)(void*));
static void bst_postorder_rec(struct Node *root, void (* print_fn)(void*));
static void bst_preorder_rec(struct Node *root, void (* print_fn)(void*));
static struct Node* bst_get_successor(struct Node *root);
static struct Node* bst_create_node(void *value, size_t value_size);
static void bst_discard_node(struct Node *node);
static void bst_discard_all_nodes(struct BinarySearchTree *tree);
static void bst_discard_all_nodes_rec(struct Node *root);


struct BinarySearchTree* bst_create() {
    struct BinarySearchTree *tree = malloc(sizeof(struct BinarySearchTree));
    if (tree == NULL) return NULL;

    tree->root = NULL;
    tree->length = 0;
    return tree;
}

void bst_insert(struct BinarySearchTree *tree, void *value, size_t value_size, int (*compare)(void*, void*)) {
    tree->root = bst_insert_rec(tree->root, value, value_size, compare);
    tree->length++;
}

// Each call returns the (possibly new) root of the subtree it was handed, which
// the caller rebinds into root->left / root->right as it unwinds.
static struct Node* bst_insert_rec(struct Node *root, void *value, size_t value_size, int (*compare)(void*, void*)) {
    if (root == NULL) {
        return bst_create_node(value, value_size);
    } else if (compare(value, root->value) < 0) {
        root->left = bst_insert_rec(root->left, value, value_size, compare);
        return root;
    } else {
        root->right = bst_insert_rec(root->right, value, value_size, compare);
        return root;
    }
}

void bst_remove(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) {
    bool found = false;
    tree->root = bst_remove_rec(tree->root, value, compare, &found);
    if (found) tree->length--;
}

// Returns the replacement root for this subtree; every branch hands back the node
// the parent should point its child pointer at (NULL, the lone child, or root
// itself carrying the successor's value). *found reports whether value was present.
static Node* bst_remove_rec(struct Node *root, void *value, int (*compare)(void*, void*), bool *found) {
    if (root == NULL) {
        *found = false;
        return root;

    } else if (compare(value, root->value) == 0) {
        *found = true;

        if (root->left == NULL && root->right == NULL) {
            bst_discard_node(root);
            root = NULL;
            return root;

        } else if (root->left == NULL || root->right == NULL) {

            if (root->left != NULL) {
                struct Node *left = root->left;
                bst_discard_node(root);
                root = NULL;
                return left;

            } else {
                struct Node *right = root->right;
                bst_discard_node(root);
                root = NULL;
                return right;
            }

        } else {
            // Two children: overwrite this node's value with its in-order
            // successor (smallest value in the right subtree), then delete the
            // successor from that subtree.
            struct Node *successor = bst_get_successor(root->right);
            memcpy(root->value, successor->value, root->value_size);
            root->right = bst_remove_rec(root->right, successor->value, compare, found);
            return root;
        }

    } else {
        if (compare(value, root->value) < 0) {
            root->left = bst_remove_rec(root->left, value, compare, found);
            return root;

        } else {
            root->right = bst_remove_rec(root->right, value, compare, found);
            return root;
        }
    }
}

bool bst_contains(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) {
    if (bst_isempty(tree)) return false;
    return bst_contains_rec(tree->root, value, compare);
}

static bool bst_contains_rec(struct Node *root, void *value, int (*compare)(void*, void*)) {
    if (root == NULL) return false;

    if (compare(value, root->value) == 0) {
        return true;
    } else if (compare(value, root->value) < 0) {
        return bst_contains_rec(root->left, value, compare);
    } else {
        return bst_contains_rec(root->right, value, compare);
    }
}

struct Node* bst_search(struct BinarySearchTree *tree, void *value, int (*compare)(void*, void*)) {
    if (bst_isempty(tree)) return NULL;
    return bst_search_rec(tree->root, value, compare);
}

static struct Node* bst_search_rec(struct Node *root, void *value, int (*compare)(void*, void*)) {
    if (root == NULL) return NULL;

    if (compare(value, root->value) == 0) {
        return root;
    } else if (compare(value, root->value) < 0) {
        return bst_search_rec(root->left, value, compare);
    } else {
        return bst_search_rec(root->right, value, compare);
    }
}

void* bst_min(struct BinarySearchTree *tree) {
    if (bst_isempty(tree)) return NULL;
    return bst_min_rec(tree->root);
}

// Precondition: root != NULL (callers guard with bst_isempty). Walks left to the
// smallest value; bst_max_rec is the mirror image.
static void* bst_min_rec(struct Node *root) {
    if (root->left == NULL) return root->value;
    return bst_min_rec(root->left);
}

void* bst_max(struct BinarySearchTree *tree) {
    if (bst_isempty(tree)) return NULL;
    return bst_max_rec(tree->root);
}

static void* bst_max_rec(struct Node *root) {
    if (root->right == NULL) return root->value;
    return bst_max_rec(root->right);
}

int bst_height(struct BinarySearchTree *tree) {
    if (bst_isempty(tree)) return 0;
    return bst_height_rec(tree->root);
}

static int bst_height_rec(struct Node *root) {
    if (root == NULL) return 0;

    int left_height = bst_height_rec(root->left);
    int right_height = bst_height_rec(root->right);

    // Height in nodes: taller child subtree plus one for the current node.
    if (left_height > right_height) return left_height + 1;
    return right_height + 1;
}

void bst_print(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    bst_print_rec(tree->root, print_fn, 0);
}

static void bst_print_rec(struct Node *root, void (* print_fn)(void*), int depth) {
    if (root == NULL) return;

    // In-order (left, node, right): values print in ascending order, one per
    // line, indented by depth.
    bst_print_rec(root->left, print_fn, depth + 1);

    for (int i = 0; i < depth; i++) printf("    ");
    print_fn(root->value);
    printf("\n");

    bst_print_rec(root->right, print_fn, depth + 1);
}

void bst_inorder(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    if (bst_isempty(tree)) return;
    bst_inorder_rec(tree->root, print_fn);
}

static void bst_inorder_rec(struct Node *root, void (* print_fn)(void*)) {
    if (root == NULL) return;

    bst_inorder_rec(root->left, print_fn);
    print_fn(root->value);
    bst_inorder_rec(root->right, print_fn);
}

void bst_postorder(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    if (bst_isempty(tree)) return;
    bst_postorder_rec(tree->root, print_fn);
}

static void bst_postorder_rec(struct Node *root, void (* print_fn)(void*)) {
    if (root == NULL) return;

    bst_postorder_rec(root->left, print_fn);
    bst_postorder_rec(root->right, print_fn);
    print_fn(root->value);
}

void bst_preorder(struct BinarySearchTree *tree, void (* print_fn)(void*)) {
    if (bst_isempty(tree)) return;
    bst_preorder_rec(tree->root, print_fn);
}

static void bst_preorder_rec(struct Node *root, void (* print_fn)(void*)) {
    if (root == NULL) return;

    print_fn(root->value);
    bst_preorder_rec(root->left, print_fn);
    bst_preorder_rec(root->right, print_fn);
}

int bst_size(const struct BinarySearchTree *tree) {
    return tree->length;
}

bool bst_isempty(const struct BinarySearchTree *tree) {
    return tree->length == 0;
}

void bst_clear(struct BinarySearchTree *tree) {
    bst_discard_all_nodes(tree);
    tree->root = NULL;
    tree->length = 0;
}

void bst_discard(struct BinarySearchTree *tree) {
    if (tree != NULL) {
        bst_discard_all_nodes(tree);
        free(tree);
    }
}


// Leftmost node of the given subtree. Pass root->right to get the in-order
// successor of root.
static struct Node* bst_get_successor(struct Node *root) {
    if (root->left == NULL) return root;
    return bst_get_successor(root->left);
}

// Deep-copies value_size bytes from value; the node owns the copy.
static struct Node* bst_create_node(void *value, size_t value_size) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) return NULL;

    node->value_size = value_size;
    node->left = NULL;
    node->right = NULL;

    node->value = malloc(node->value_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->value, value, node->value_size);
    return node;
}

static void bst_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

static void bst_discard_all_nodes(struct BinarySearchTree *tree) {
    bst_discard_all_nodes_rec(tree->root);
}

static void bst_discard_all_nodes_rec(struct Node *root) {
    if (root == NULL) return;

    // Post-order: free both children before the parent so we never follow a
    // pointer into an already-freed node.
    bst_discard_all_nodes_rec(root->left);
    bst_discard_all_nodes_rec(root->right);
    bst_discard_node(root);
}
