#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"


/// linked_list.c
/// A generic implementation of a doubly linked list
/// Brendan Dileo - November 14 2025


// Initalizes a new node
struct Node * ll_init_node(void *val, size_t size) {

    // Allocate memory for the node itself and
    struct Node *node = malloc(sizeof(struct Node));
    
    // Handle allocation failure
    if (node == NULL) {
        return NULL;
    }

    // Set the size of the item stored in the node and initialize
    // the nodes `next` and `prev` pointers to NULL
    node->item_size = size;
    node->next = NULL;
    node->prev = NULL;

    // Allocate memory for the value that will be stored in the node
    node->value = malloc(node->item_size);

    // Handle allocation failure
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    // Copy the raw memory contents from the memory pointed to by `val` into `node->value`
    memcpy(node->value, val, node->item_size);

    return node;
}


// Creates a new linked list
struct LinkedList * ll_init() {
    // Allocate mmeory for the linked list itself
    struct LinkedList *linked_list = malloc(sizeof(struct LinkedList));

    // Handle allocation failure
    if (linked_list == NULL) { 
        return NULL;
    }

    // Set initial length of the linked list and pointers to head/tail to NULL
    linked_list->length = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

// Inserts a node at the head of the linked list
void ll_insert(struct Node *node, struct LinkedList *list) {

    // Check if the `head` of the list points to NULL since we 
    // can only update the old heads `prev` pointer if there is an old head
    if (list->head != NULL) {
        list->head->prev = node;
    }

    // Point the node being inserted `next` pointer to whatever the head of the list 
    // currently points to, and the `prev` pointer of the node being inserted to NULL
    // since its the new head of the list. Point the head of the list to the node being
    // inserted
    node->next = list->head;                                
    node->prev = NULL;                                      
    list->head = node;

    // Check if the tail of the list is NULL, meaning list is empty
    // If it is, set the tail to the node being inserted since its the only node in the list
    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
}

// Inserts a node at the tail of the linked list
void ll_insert_tail(struct Node *node, struct LinkedList *list) {

    // Check if list is empty
    if (list->head == NULL) {
        // If list is empty, point the node being inserted `next` pointer to whatever the head of
        // the list currently points to, the node being inserted `prev` to NULL since its the new
        // head of the list, and the tail to the node inserted since its the only node in the list
        node->next = list->head;
        node->prev = NULL;
        list->head = node;
        list->tail = node;
        list->length++;

    // List not empty, need to access and insert at tail
    } else {
        // If list is not empty, set the current tail `next` pointer to the node being inserted,
        // and the node being inserted `next` to NULL since its the new tail. To link the new tail
        // with the old, set the `prev` pointer of the node being inserted to point to the old tail
        list->tail->next = node;
        node->next = NULL;
        node->prev = list->tail;
        list->tail = node;
        list->length++;
    }
}

// Inserts a node at the specified location in the linked list
void ll_insert_at(struct Node *node, struct LinkedList *list, int index) {

    if (index < 0 || index > list->length) return;

    // Check if insertion point is the head of the list
    if (index == 0) {
        ll_insert(node, list);
        return;

    // Check if insertion point is the tail of the list
    } else if (index == list->length) {
        ll_insert_tail(node, list);
        return;

    // If insertion point is not head or tail, its somewhere in between
    } else {

        // Traverse the list starting from the head to find the insertion point 
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check if weve reached the insertion point
            if (idx == index) {

                // If weve reached the insertion point, store temporary pointers
                // to the node before the current node and the current node itself
                struct Node *previous = current->prev;
                struct Node *next = current;

                // Update pointers to insert the new node
                // Point the previous nodes `next` to the new node
                // Point the current nodes `prev` to the new node
                // Point the new nodes `next` to the current node
                // Point the new nodes `prev` to the previous node
                previous->next = node;
                next->prev = node;
                node->next = next;
                node->prev = previous;
                list->length++;
                break;
            }
            idx++;
        }
    }
}

// Removes the node at the head of the linked list
void ll_remove(struct LinkedList *list) {
    if (list->head == NULL) return;

    // Store pointer to the old head before removal to keep the link to rest of the list
    // and free memory allocated by the old head to remove it and set new head
    struct Node *temp = list->head->next;
    free(list->head->value);
    free(list->head);
    list->head = temp;

    // Check if the list is empty after removing the old head
    if (list->head != NULL) {
        // If list not empty, update the new head `prev` pointer to point to NULL
        list->head->prev = NULL;
    } else {
        // If the list is now empty, update the tail pointer since no nodes are left
        list->tail = NULL;
    }
    list->length--;
}

// Removes the node at the tail of the linked list
void ll_remove_tail(struct LinkedList *list) {
    if (list->head == NULL) return;

    // Check if there is only one node in the list
    if (list->head == list->tail) {
        // Free the memory allocated by the head node and update the head/tail pointers
        free(list->head->value);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length--;
        return;

    // Otherwise access the tail node to append the new node
    } else {

        // Store pointer to the node before the current tail,
        // this is the node that will become the new tail, and
        // free memory allocated by the current tail
        struct Node *new_tail = list->tail->prev;
        free(list->tail->value);
        free(list->tail);

        // Set the new tail of the list and update the new tails
        // `next` pointer to point to NULL
        list->tail = new_tail;
        list->tail->next = NULL;
        list->length--;
        return;
    }
}

// Removes a node at a specified location in the linked list
void ll_remove_at(struct LinkedList *list, int index) {
    if (index < 0 || index >= list->length) return;

    // Check if head node is being removed
    if (index == 0) {
        ll_remove(list);
        return;
    
    // Check if tail node is being removed
    } else if (index == list->length - 1) {
        ll_remove_tail(list);
        return;

    // Otherwise node being removed is in between
    } else {

        // Need to traverse from head to tail to find location of node being removed
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check if were at the removal point
            // Current node is the node to remove
            if (idx == index) {

                // Store pointers to the nodes before and after the current node
                struct Node *previous = current->prev;
                struct Node *next = current->next;

                // Free the current node to remove it
                free(current->value);
                free(current);

                // Relink the surrounding nodes by setting the previous nodes `next` to the 
                // node that followed the removed node, and the next nodes `prev` to the 
                // previous node
                previous->next = next;
                next->prev = previous;
                list->length--;
                break;
            }
            idx++;
        }
    }
}

// Retrieves the value stored in the node at the location specified
bool ll_get(struct LinkedList *list, int index, void *out) {
    if (index < 0 || index >= list->length) return false;

    // Check if location (index) is in the second half of the list
    if (index > list->length / 2) {

        // Traverse starting from the tail of the list
        int idx = list->length - 1;
        for (struct Node *current = list->tail; current != NULL; current = current->prev) {
            if (idx == index) {
                // If position is reached, copy the raw memory from where the value is stored into the 
                // memory pointed to by the `out` pointer
                memcpy(out, current->value, current->item_size);
                return true;
            }
            idx--;
        }
    // Otherwise start traversal from head
    } else {
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            
            // If weve reached the position of the node, copy its memory contents into the `out` pointer
            // and return true
            if (idx == index) {
                memcpy(out, current->value, current->item_size);
                return true;
            }
            idx++;
        }
    }
    return false;
}

// Sets the value of the node at the specified location (index) in the linked list
bool ll_set(struct LinkedList *list, int index, void *in) {
    if (index < 0 || index >= list->length) return false;

    // Check if location is closer to tail
    if (index > list->length / 2) {

        // Traverse from tail to head
        int idx = list->length - 1;
        for (struct Node *current = list->tail; current != NULL; current = current->prev) {
            // If weve reached the target node, copy the data pointed to by the `in` pointer
            // into the memory allocated for the nodes value
            if (idx == index) {
                memcpy(current->value, in, current->item_size);
                return true;
            }
            idx--;
        }
    // Location is closer to head
    } else {

        // Traverse from head to tail
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            // If reached target node, copy memory pointed to by `in` into `current->value`
            if (idx == index) {
                memcpy(current->value, in, current->item_size);
                return true;
            }
            idx++;
        }
    }
    return false;
}

// Finds the node with the specified value and returns the location (index) of the node, or -1 if not found
// Relies on a caller defined comparator function to determine how to compare items of the type stored
int ll_find(struct LinkedList *list, void *item, bool (* comparator)(void*, void*)) {
    if (list->head == NULL) return -1;

    // Traverse from head to tail
    int idx = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {

        // If the current value is equal to the value being searched for, return current index
        if (comparator(current->value, item)) {
            return idx;
        }
        idx++;
    }
    return -1;
}

// Returns a boolean value indicating whether the linked list contains the value specified or not
bool ll_contains(struct LinkedList *list, void *item, bool (* comparator)(void*, void*)) {
    if (list->head == NULL) return false;

    int idx = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        if (comparator(current->value, item)) {
            return true;
        }
        idx++;
    }
    return false;
}

// Clears each node in the linked list
void ll_clear(struct LinkedList *list) {
    if (list->head == NULL) return;

    ll_discard_all_nodes(list);
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

// Creates and returns a deep copy of a linked list
struct LinkedList* ll_copy(struct LinkedList *orig) {
    struct LinkedList *copy = ll_init();

    // Traverse from the original lists head to tail, and for each node in the original list
    // initialize a new node which is a copy of the current node to prevent breaking the links
    // between the nodes
    for (struct Node *current = orig->head; current != NULL; current = current->next) {
        struct Node *cnode = ll_init_node(current->value, current->item_size);
        ll_insert_tail(cnode, copy);
    }
    return copy;
}

// Reverses the contents of the linked list in place
void ll_reverse(struct LinkedList *list) {
    if (list->head == NULL) return;

    // Store pointers to the current node and the most recently processed node
    // Start at the head of the list, and with the most recently processed node set to NULL
    struct Node *current = list->head;
    struct Node *last = NULL;

    // Rely on the node currently being processed
    while (current != NULL) {

        // Store the current nodes `next` node to prevent losing the link to the rest of the list
        // Then we point the current nodes `next` pointer to its `prev` to flip the pointer
        struct Node *temp = current->next;
        current->next = current->prev;

        // To move to the next node, point the current nodes `prev` to the original next node
        // Store pointer to the node just reversed in `last` to track most recently reversed node
        // Point the current node to the original next node
        current->prev = temp;
        last = current;
        current = temp;
    }

    // Point the tail of the list to the head,
    // and the head to the most recently reversed node
    list->tail = list->head;
    list->head = last;
}


// Sorts a linked list using a Bubble Sort implementation and relying on a caller defined comparator to know how to order items
void ll_bsort(struct LinkedList *list, bool (* comparator)(void*, void*)) { 
    if (list->head == NULL) return;

    bool swapped = true;
    while (swapped) {

        swapped = false;
        struct Node *current  = list->head;

        while (current->next != NULL) {
            if (comparator(current->value, current->next->value)) {
                swap_nodes(current, current->next);
                swapped = true;
            }
            current = current->next;
        }
    }
}


// Swaps the value stored within two nodes
void swap_nodes(struct Node *a, struct Node *b) {
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// TODO:
// 1. Identify the two nodes: current & next
// 2. Keep track of surrounding nodes: prev (current->prev), after (next->next)
// 3. Update pointers of the two nodes themselves
// 4. Update the surrounding nodes (If prev exists, if after exists)
// 5. Update the head pointer if needed
// 6. After swapping, current now points to the second node in the pair

// Swaps the positions of two nodes in the linked list
void swap_node_positions(struct LinkedList *list, struct Node *a, struct Node *b) {

    // Nodes are the same
    if (a == b) {
        return;
    // Nodes are adjacent
    } else if (a->next == b || b->next == a) {

        // Track surronding
        struct Node *aprev = a->prev;       // could be NULL
        struct Node *bnext = b->next;

        // Update pointers of the two nodes themselves
        a->next = bnext;
        b->next = a;

        if (aprev != NULL) {
            aprev->next = b;
        }

        if (bnext != NULL) {
            bnext->prev = a;
        }



    // Nodes not adjadent
    } else {


    }



}


// Returns whether the linked list is empty or not
bool ll_is_empty(struct LinkedList *list) {
    if (list->head == NULL) return true;
    return false;
}

// Returns the size (length) of the linked list
int ll_size(struct LinkedList *list) {
    return list->length;
}

// Frees the memory allocated by a single node
void ll_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

// Frees the memory allocated by each node in a linked list
void ll_discard_all_nodes(struct LinkedList *list) {
    if (list != NULL) {
        // Start from the head of the list, traverse to the end
        struct Node *current = list->head;
        while (current != NULL) {
            // Store the nodes `next` pointer before freeing the current node
            // to avoid losing reference to the rest of the list
            struct Node *next = current->next;
            ll_discard_node(current);
            current = next;
        }
    }
}

// Frees all memory associated with a linked list
void ll_discard(struct LinkedList *list) {
    if (list != NULL) {
        ll_discard_all_nodes(list);
        free(list);
    }
}


// Prints all items stored in the linked list, requiring a caller defined print function that knows how to print each value
void ll_print(struct LinkedList *list, void (* print_fn)(void*)) {
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        print_fn(current->value);
    }
    printf("\n");
}


// Prints each node in the linked list with its address, value, and next/prev pointers for debugging
void ll_debug(struct LinkedList *list) {
    struct Node *curr = list->head;
    while (curr != NULL) {
        printf("Node %p | value=%d | prev=%p | next=%p\n", 
            (void *) curr, 
            * (int *) curr->value, 
            (void *) curr->prev, 
            (void *) curr->next);
        curr = curr->next;
    }
}