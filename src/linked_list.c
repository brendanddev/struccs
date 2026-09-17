// linked_list.c
// A generic implementation of a double linked list.
// Brendan Dileo - 2025

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linked_list.h"

// Each node owns a heap copy of its value (item_size bytes).
typedef struct Node {
    void *value;
    size_t item_size;
    struct Node *next;
    struct Node *prev;
} Node;

// Prototypes
static struct Node* ll_create_node(void *val, size_t size);
static void ll_discard_node(struct Node *node);
static void ll_discard_all_nodes(struct LinkedList *list);
static void swap_node_positions(struct LinkedList *list, struct Node *a, struct Node *b);
static void swap_nodes(struct Node *a, struct Node *b);

struct LinkedList * ll_create() {
    struct LinkedList *linked_list = malloc(sizeof(struct LinkedList));
    if (linked_list == NULL) {
        return NULL;
    }

    linked_list->length = 0;
    linked_list->head = NULL;
    linked_list->tail = NULL;

    return linked_list;
}

void ll_insert(struct LinkedList *list, void *value, size_t item_size) {
    struct Node *node = ll_create_node(value, item_size);

    // Only the old head has a prev pointer to fix up; an empty list has none.
    if (list->head != NULL) {
        list->head->prev = node;
    }

    node->next = list->head;
    node->prev = NULL;
    list->head = node;

    // First node: it is the tail as well as the head.
    if (list->tail == NULL) {
        list->tail = node;
    }

    list->length++;
}

void ll_insert_tail(struct LinkedList *list, void *value, size_t item_size) {
    struct Node *node = ll_create_node(value, item_size);

    if (list->head == NULL) {
        // Empty list: the new node is both head and tail.
        node->next = list->head;
        node->prev = NULL;
        list->head = node;
        list->tail = node;
        list->length++;

    } else {
        list->tail->next = node;
        node->next = NULL;
        node->prev = list->tail;
        list->tail = node;
        list->length++;
    }
}

void ll_insert_at(struct LinkedList *list, void *value, size_t item_size, int index) {
    if (index < 0 || index > list->length) return;

    if (index == 0) {
        ll_insert(list, value, item_size);
        return;

    } else if (index == list->length) {
        ll_insert_tail(list, value, item_size);
        return;

    } else {
        struct Node *node = ll_create_node(value, item_size);
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            if (idx == index) {
                struct Node *previous = current->prev;
                struct Node *next = current;

                // Splice node in between previous and current.
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

void ll_remove(struct LinkedList *list) {
    if (list->head == NULL) return;

    struct Node *temp = list->head->next;
    free(list->head->value);
    free(list->head);
    list->head = temp;

    if (list->head != NULL) {
        list->head->prev = NULL;
    } else {
        // That was the only node, so the tail pointer is now stale too.
        list->tail = NULL;
    }
    list->length--;
}

void ll_remove_tail(struct LinkedList *list) {
    if (list->head == NULL) return;

    if (list->head == list->tail) {
        free(list->head->value);
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        list->length--;
        return;

    } else {
        struct Node *new_tail = list->tail->prev;
        free(list->tail->value);
        free(list->tail);

        list->tail = new_tail;
        list->tail->next = NULL;
        list->length--;
        return;
    }
}

void ll_remove_at(struct LinkedList *list, int index) {
    if (index < 0 || index >= list->length) return;

    if (index == 0) {
        ll_remove(list);
        return;

    } else if (index == list->length - 1) {
        ll_remove_tail(list);
        return;

    } else {
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            if (idx == index) {
                struct Node *previous = current->prev;
                struct Node *next = current->next;

                free(current->value);
                free(current);

                previous->next = next;
                next->prev = previous;
                list->length--;
                break;
            }
            idx++;
        }
    }
}

bool ll_get(struct LinkedList *list, int index, void *out) {
    if (index < 0 || index >= list->length) return false;

    // Walk in from whichever end is closer to index.
    if (index > list->length / 2) {
        int idx = list->length - 1;
        for (struct Node *current = list->tail; current != NULL; current = current->prev) {
            if (idx == index) {
                memcpy(out, current->value, current->item_size);
                return true;
            }
            idx--;
        }
    } else {
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            if (idx == index) {
                memcpy(out, current->value, current->item_size);
                return true;
            }
            idx++;
        }
    }
    return false;
}

bool ll_set(struct LinkedList *list, int index, void *in) {
    if (index < 0 || index >= list->length) return false;

    // Walk in from whichever end is closer to index.
    if (index > list->length / 2) {
        int idx = list->length - 1;
        for (struct Node *current = list->tail; current != NULL; current = current->prev) {
            if (idx == index) {
                memcpy(current->value, in, current->item_size);
                return true;
            }
            idx--;
        }
    } else {
        int idx = 0;
        for (struct Node *current = list->head; current != NULL; current = current->next) {
            if (idx == index) {
                memcpy(current->value, in, current->item_size);
                return true;
            }
            idx++;
        }
    }
    return false;
}

int ll_find(struct LinkedList *list, void *item, bool (* comparator)(void*, void*)) {
    if (list->head == NULL) return -1;

    int idx = 0;
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        if (comparator(current->value, item)) {
            return idx;
        }
        idx++;
    }
    return -1;
}

bool ll_contains(struct LinkedList *list, void *item, bool (* comparator)(void*, void*)) {
    if (list->head == NULL) return false;

    for (struct Node *current = list->head; current != NULL; current = current->next) {
        if (comparator(current->value, item)) {
            return true;
        }
    }
    return false;
}

void ll_clear(struct LinkedList *list) {
    if (list->head == NULL) return;

    ll_discard_all_nodes(list);
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}

struct LinkedList* ll_copy(struct LinkedList *orig) {
    struct LinkedList *copy = ll_create();
    if (copy == NULL) {
        return NULL;
    }

    for (struct Node *current = orig->head; current != NULL; current = current->next) {
        ll_insert_tail(copy, current->value, current->item_size);
    }
    return copy;
}

void ll_reverse(struct LinkedList *list) {
    if (list->head == NULL) return;

    struct Node *current = list->head;
    struct Node *last = NULL;

    while (current != NULL) {
        // Save next before we overwrite this node's link fields.
        struct Node *temp = current->next;
        current->next = current->prev;
        current->prev = temp;
        last = current;
        current = temp;
    }

    // Old head is now the tail; the last node visited is the new head.
    list->tail = list->head;
    list->head = last;
}

bool ll_is_empty(const struct LinkedList *list) {
    if (list->head == NULL) return true;
    return false;
}

int ll_size(const struct LinkedList *list) {
    return list->length;
}

void ll_discard(struct LinkedList *list) {
    if (list != NULL) {
        ll_discard_all_nodes(list);
        free(list);
    }
}

void ll_print(struct LinkedList *list, void (* print_fn)(void*)) {
    for (struct Node *current = list->head; current != NULL; current = current->next) {
        print_fn(current->value);
    }
    printf("\n");
}

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


// Private helper functions - linkage limited to this file


// Deep-copies size bytes from val; the returned node owns the copy.
struct Node * ll_create_node(void *val, size_t size) {
    struct Node *node = malloc(sizeof(struct Node));
    if (node == NULL) {
        return NULL;
    }

    node->item_size = size;
    node->next = NULL;
    node->prev = NULL;

    node->value = malloc(node->item_size);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }

    memcpy(node->value, val, node->item_size);

    return node;
}

static void ll_discard_node(struct Node *node) {
    if (node != NULL) {
        free(node->value);
        free(node);
    }
}

static void ll_discard_all_nodes(struct LinkedList *list) {
    if (list != NULL) {
        struct Node *current = list->head;
        while (current != NULL) {
            // Grab next before freeing current.
            struct Node *next = current->next;
            ll_discard_node(current);
            current = next;
        }
    }
}

// Swaps the values held by two nodes, leaving the nodes themselves in place.
// This is what ll_bsort uses; swap_node_positions (below) relinks instead.
static void swap_nodes(struct Node *a, struct Node *b) {
    void *temp = a->value;
    a->value = b->value;
    b->value = temp;
}

// Relinks two nodes so they trade places in the list. Currently unused.
static void swap_node_positions(struct LinkedList *list, struct Node *a, struct Node *b) {
    if (a == b) {
        return;
    } else if (a->next == b || b->next == a) {
        // Adjacent nodes: handled on their own since there are fewer links to fix.

        if (b->next == a) {
            // Normalize so a is always the left (earlier) node.
            struct Node *tmp = a;
            a = b;
            b = tmp;
        }

        struct Node *aprev = a->prev;       // may be NULL (a is the head)
        struct Node *bnext = b->next;       // may be NULL (b is the tail)

        b->prev = aprev;
        b->next = a;

        a->next = bnext;
        a->prev = b;

        // The outer nodes only need fixing up when they actually exist.
        if (aprev != NULL) {
            aprev->next = b;
        }

        if (bnext != NULL) {
            bnext->prev = a;
        }

        // Move head/tail if either endpoint was one of the swapped nodes.
        if (list->head == a) {
            list->head = b;
        } else if (list->head == b) {
            list->head = a;
        }

        if (list->tail == a) {
            list->tail = b;
        } else if (list->tail == b) {
            list->tail = a;
        }

    } else {
        // Non-adjacent nodes: point each one at the other's old neighbours.
        struct Node *aprev = a->prev;
        struct Node *anext = a->next;
        struct Node *bprev = b->prev;
        struct Node *bnext = b->next;

        b->prev = aprev;
        b->next = anext;

        a->next = bnext;
        a->prev = bprev;

        // Reconnect the surrounding nodes that exist.
        if (aprev != NULL) {
            aprev->next = b;
        }

        if (anext != NULL) {
            anext->prev = b;
        }

        if (bprev != NULL) {
            bprev->next = a;
        }

        if (bnext != NULL) {
            bnext->prev = a;
        }

        // Move head/tail if either endpoint was one of the swapped nodes.
        if (list->head == a) {
            list->head = b;
        } else if (list->head == b) {
            list->head = a;
        }

        if (list->tail == a) {
            list->tail = b;
        } else if (list->tail == b) {
            list->tail = a;
        }
    }
}
