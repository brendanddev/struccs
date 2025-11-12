#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linked_list.h"


/// linked_list.c
/// Brendan Dileo - November 11 2025



// Creates a new struct Node
struct Node * _node_init(int value) {
    // Allocate memory for the Node struct itself
    struct Node *node = NULL;
    node = malloc(sizeof(struct Node));

    // Store the value inside the Node
    node->value = value;

    // Set the `next` pointer to NULL since it is not linked yet
    node->next = NULL;

    return node;
}

// Creates a new struct LinkedList
struct LinkedList * _init() {
    // Allocate memory for the LinkedList itself
    struct LinkedList *linked_list = NULL;
    linked_list = malloc(sizeof(struct LinkedList));

    // Point the `head` pointer to NULL since no Nodes are linked
    linked_list->head = NULL;
    linked_list->length = 0;

    return linked_list;
}

// Inserts a new Node into the LinkedList at the head
void _insert(struct Node *node, struct LinkedList *list) {

    // Point the new Nodes `next` to the `head` of the LinkedList
    node->next = list->head;

    // Point the lists `head` to the new node
    list->head = node;

    // Increment length
    list->length++;
}

// Inserts a new Node into the LinkedList at the tail of the list
void _insert_tail(struct Node *node, struct LinkedList *list) {

    // Check if the head of the list is NULL, meaning the list is empty
    if (list->head == NULL) {
        // If the list is empty, set the new node as the first node in the list
        // The node added now becomes the head node in the list (first node) 
        list->head = node;
        list->length++;

    // List is not empty, need to traverse from the head node to the tail node
    } else {

        // Start from head node, traverse the list until we reach a node where next == NULL, this is the tail node
        for (struct Node *current = list->head; current != NULL; current = current->next) {

            // Check if the current node does not point to another node with its `next` ptr
            // This is the tail node
            if (current->next == NULL) {
                // Insert the node at the end by setting the current tails `next` ptr to the node inserted
                current->next = node;
                list->length++;
                return;
            }
        }
    }
}


// Inserts a new Node into the LinkedList at a specified index
void _insert_at(struct Node *node, struct LinkedList *list, int index) {

    if (index < 0 || index > list->length) return;

    // List is empty, node being inserted becomes new head of the linked list
    if (index == 0) {
        node->next = list->head;
        list->head = node;
        list->length++;
        return;
    }

    // Traverse the list starting from the head
    int i = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {

        // Found the position before where the node will be inserted
        if (i == (index - 1)) {

            // Store the 'prev' node which is the current node, one element behind the insertion point
            // Store the 'curr' node which is the node at the insertion point
            struct Node *prev = current;                    
            struct Node *curr = current->next;
            
            // Set the next pointer of the `prev` node to point to the node being inserted
            // Set the next pointer of the node being added to point to the node at the insertion point
            // This inserts the new node between the `prev` and `curr` pointers and relinks
            prev->next = node;
            node->next = curr;
            list->length++;
            return;
        }
        i++;
    }
}

// Removes the head Node of the LinkedList (first item)
void _remove(struct LinkedList *list) {

    // Check if the list is empty (head ptr points to NULL)
    if (list->head == NULL) {
        return;
    }

    // Temporary pointer to hold the node that will be the new head
    // Store it here to avoid losing the pointer when freeing the head node of the list
    struct Node *temp = list->head->next;

    // Free the memory previously allocated for the head node
    free(list->head);

    // Reassign the head pointer of the list to the temp
    list->head = temp;
    list->length--;
}

// Removes the tail node of the Linked List (last item)
void _remove_tail(struct LinkedList *list) {
    
    // List is empty (head pointer points to NULL)
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    // Traverse the nodes of the linked list starting from the head to find the tail node
    for (struct Node *current = list->head; current != NULL; current = current->next) {

        // Check if the current nodes `next` pointer points to NULL,
        // meaning we have found the tail node
        if (current->next->next == NULL) {

            // Free the memory allocated by the tail node
            free(current->next);
            current->next = NULL;
            list->length--;
        }
    }
}

// Removes a node at a specified index in the Linked List
void _remove_at(struct LinkedList *list, int index) {
    if (index < 0 || index > list->length) return;

    // Check if head is being removed
    if (index == 0) {
        _remove(list);

    // Check if tail is being removed
    } else if (index == list->length - 1) {
        _remove_tail(list);

    // Otherwise node to remove is somewhere else inside the list
    } else {

        // Traverse the list starting from the head node
        int i = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            
            // Found the position before the node to remove
            // Which is the position of the node before the node at position=index
            if (i == (index - 1)) {

                struct Node *prev = current;                // the node before the node being removed
                struct Node *curr = current->next;          // the node being removed
                struct Node *temp = curr->next;             // a temporary pointer to the node after the node being removed

                // Free the memory allocated by the node being removed
                free(current->next);
                current->next = NULL;

                // Point the current nodes `next` ptr to the node after the one removed
                // stored in the temp pointer
                current->next = temp;
                list->length--;
            }
            i++;
        }
    }
}




// Checks if the Linked List is empty
bool _is_empty(struct LinkedList *list) {
    if (list->head == NULL) return true;
    return false;
}

// Returns the size (length) of the Linked List
int _size(struct LinkedList *list) {
    return list->length;
}

// Prints the contents of the LinkedList by traversing Node through Node
void _print(struct LinkedList *list) {
    printf("Size of LinkedList: %d, Contents: \n", list->length);
    int index = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        printf("Value: %d, Index: %d\n", current->value, index);
        index++;
    }
}

// Frees any memory allocated by the Node
void _node_discard(struct Node *node) {
    if (node != NULL) {
        free(node->next);
        free(node);
    }
}

// Frees any memory allocated by the LinkedList
void _discard(struct LinkedList *linked_list) {
    if (linked_list != NULL) {
        free(linked_list->head);
        free(linked_list);
    }
}





