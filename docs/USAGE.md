# Usage Examples

Code examples for each structure in the struccs library.

---

## Generic Array

```c
#include "generic_array.h"

// Create an array for integers
struct GenericArray *ga = ga_create(sizeof(int));

// Add some elements
int values[] = {42, 17, 89, 3};
for (int i = 0; i < 4; i++) {
    ga_append(ga, &values[i]);
}

// Define a comparison function
int compare_int(void *a, void *b) {
    return *(int*)a - *(int*)b;
}

// Search for a value
int target = 17;
if (ga_contains(ga, &target, compare_int)) {
    printf("Found %d in the array!\n", target);
}

// Define a print function
void print_int(void *value) {
    printf("[%d] ", *(int*)value);
}

// Print the array
ga_print(ga, print_int);

// Clean up
ga_discard(ga);
```

---

## Linked List

```c
#include "linked_list.h"

// Create a new linked list
struct LinkedList *list = ll_create();

// Add some integers
int values[] = {10, 20, 30, 40};
for (int i = 0; i < 4; i++) {
    ll_insert_tail(list, &values[i], sizeof(int));
}

// Define a comparison function
bool compare_int(void *a, void *b) {
    return *(int*)a == *(int*)b;
}

// Search for a value
int target = 30;
int index = ll_find(list, &target, compare_int);
if (index != -1) {
    printf("Found %d at index %d\n", target, index);
}

// Access an element
int value;
if (ll_get(list, 2, &value)) {
    printf("Element at index 2: %d\n", value);
}

// Update an element
int new_value = 3454;
if (ll_set(list, 1, &new_value)) {
    printf("Set the item at index 1 to: %d\n", new_value);
}

// Define a print function
void print_int(void *value) {
    printf("[%d] ", *(int*)value);
}

// Print and reverse the list
ll_print(list, print_int);
ll_reverse(list);

// Create a copy
struct LinkedList *copy = ll_copy(list);

// Clean up
ll_discard(list);
ll_discard(copy);
```

---

## Stack

```c
#include "stack.h"

// Create a new stack
struct Stack *stack = stack_create();

// Push some integers
int value = 100;
for (int i = 0; i < 5; i++) {
    stack_push(stack, &value, sizeof(int));
}

// Define a print function
void print_int(void *value) {
    printf("[%d] ", *(int*)value);
}

// Print the stack
stack_print(stack, print_int);

// Peek at the top element
int peek_val;
if (stack_peek(stack, &peek_val)) {
    printf("Peek Value: %d\n", peek_val);
}

// Pop an element
int pop_val;
if (stack_pop(stack, &pop_val)) {
    printf("Popped: %d\n", pop_val);
}

// Clean up
stack_discard(stack);
```

---

## Queue

```c
#include "queue.h"

// Create a new queue
struct Queue *queue = queue_create();

// Enqueue some integers
int values[] = {5000, 999, 159, 9};
for (int i = 0; i < 4; i++) {
    queue_enqueue(queue, &values[i], sizeof(int));
}

// Define a print function
void print_int(void *value) {
    printf("[%d] ", *(int*)value);
}

// Print the queue
queue_print(queue, print_int);

// Peek at the front element
int head;
if (queue_peek(queue, &head)) {
    printf("Front: %d\n", head);
}

// Dequeue an element
int dequeued;
if (queue_dequeue(queue, &dequeued)) {
    printf("Dequeued: %d\n", dequeued);
}

// Clean up
queue_discard(queue);
```

---

## Hash Table

```c
#include "hash_table.h"

// Create a new hash table
struct HashTable *ht = ht_create();

// Insert key-value pairs
for (int i = 0; i < 8; i++) {
    int key = i;
    int value = i * 15;
    ht_insert(ht, &key, sizeof(int), &value, sizeof(int));
}

// Define a print function
void print_int_key_value(void *key, void *value) {
    printf("[Key: %d: Value: %d]", *(int*)key, *(int*)value);
}

// Print the hash table
ht_print(ht, print_int_key_value);

// Get a value by key
int key = 6;
int get_value;
if (ht_get(ht, &key, sizeof(int), &get_value)) {
    printf("Value for key=%d: %d\n", key, get_value);
}

// Remove a key-value pair
int remove_key = 1;
ht_remove(ht, &remove_key, sizeof(int));

// Clean up
ht_discard(ht);
```

---

## Binary Search Tree

```c
#include "binarysearch_tree.h"

// Create a new BST
struct BinarySearchTree *bst = bst_create();

// Define a comparison function
int compare_int(void *a, void *b) {
    int num1 = *(int*)a;
    int num2 = *(int*)b;
    if (num1 == num2) return 0;
    return (num1 > num2) ? 1 : -1;
}

// Insert some integers
int nums[] = {100, 20, 300, 40};
for (int i = 0; i < 4; i++) {
    bst_insert(bst, &nums[i], sizeof(int), compare_int);
}

// Define a print function
void print_int(void *value) {
    printf("%d\n", *(int*)value);
}

// Print traversals
printf("In-order: ");
bst_inorder(bst, print_int);

printf("Pre-order: ");
bst_preorder(bst, print_int);

printf("Post-order: ");
bst_postorder(bst, print_int);

// Search for a value
int val = 100;
if (bst_contains(bst, &val, compare_int)) {
    printf("Found %d in the tree\n", val);
}

// Min, max, height
printf("Min: %d\n", *(int*)bst_min(bst));
printf("Max: %d\n", *(int*)bst_max(bst));
printf("Height: %d\n", bst_height(bst));

// Remove a value
int remove_val = 100;
bst_remove(bst, &remove_val, compare_int);

// Clean up
bst_discard(bst);
```

---

## Heap

> TODO!
