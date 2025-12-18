
# Structures From Scratch (In C)    v3.6

A collection of fundamental data structures implemented from scratch in C for learning and practice. This project demonstrates low-level understanding of memory management, pointer arithmetic, and algorithmic thinking without relying on standard library implementations.

---

## Overview

This project began as a simple **integer array** and has evolved into a comprehensive exploration of data structures in C. The focus is on building real, working implementations with proper memory management, performance considerations, and generic design patterns.

### Currently Implemented

- **GenericArray**: A type-agnostic, dynamically resizing array that can store any data type using `void*` pointers and function pointers for custom operations.

- **LinkedList**: A fully functional doubly linked list with *generic* type support, bidirectional traversal optimization, and comprehensive manipulation operations.

- **Stack**: A LIFO data structure backed by linked nodes with *generic* type support for storing any data type.

- **Queue**: A FIFO data structure backed by linked nodes with *generic* type support for storing any data type.

- **HashTable**: A *generic*, dynamically resizing hash table using separate chaining to handle collisions.

- **BinarySearchTree**: A *generic* binary search tree supporting any data type through `void*` pointers and `memcpy`.

- **BinaryTree**: In progress...

- **Heap**: In progress...


### Planned Implementations

- Graph

---

## Implementations

- **Generic Array**:
  - Type-agnostic array supporting any data type (int, double, char, structs, etc.)
  - Uses `void*` pointers and `memcpy` for generic data handling
  - **Automatic resizing** with configurable shrink threshold *(5% usage)*
  - Custom *comparison functions* via `function pointers` for `ga_contains` and other operations
  - Supports adding, appending, removing, accessing, updating, and swapping elements
  - Fully *memory-managed*, *efficient*, and *reusable* for any type
  - Deep copy of the entire structure and its elements via `ga_copy` function
  - Sort elements using *Bubble Sort* via `ga_sort` function
    - Accepts a comparison `function pointer` for custom sorting logic
  - In-order reversal via `ga_reverse` function
  - Binary Search implementation for sorted arrays via `_binary_find` function
    - Requires a sorted array and a comparison function pointer
  - Swap elements at two indices via `ga_swap` function
  - Discard the structure and free all associated memory via `ga_discard` function

  *(The older Dynamic Array is preserved in `archive/` for reference and comparison.)*

- **Linked List**:
  - Doubly **linked structure** with both forward and backward traversal
  - Generic type support through `void*` pointers and `memcpy`
  - **Optimized traversal:** Automatically chooses head or tail as starting point based on target index position
  - **Flexible insertion:** Add nodes at head `(ll_insert)`, tail `(ll_insert_tail)`, or any index `(ll_insert_at)`
  - **Flexible removal:** Remove nodes from head `(ll_remove)`, tail `(ll_remove_tail)`, or any index `(ll_remove_at)`
  - **Search operations:** Find elements by value with custom comparators `(ll_find, ll_contains)`
  - **Data access:** Get and set values at any index with optimized bidirectional traversal

- **Stack**: 
  - Classic LIFO (Last In, First Out) data structure
  - Generic type support using `void*` pointers and `memcpy` for storing any **data type**
  - Linked node implementation for dynamic memory allocation without fixed capacity
  - Proper memory management with automatic cleanup via (stack_discard)

- **Queue**:
  - Classic FIFO (First In, First Out) data structure
  - Generic type support using `void*` pointers and `memcpy` for storing any data type
  - Linked node implementation with head and tail pointers for O(1) enqueue and dequeue
  - Proper memory management with automatic cleanup via (queue_discard)

- **HashTable**: 
  - Generic key/value storage using `void*` pointers and `memcpy`
  - Separate chaining with **linked nodes** for **collision handling**
  - Automatic resizing when load factor exceeds *0.75*, doubling capacity and *rehashing* entries
  - Proper *memory management* ensures that all keys, values, and nodes are deep-copied and *freed* correctly
  - Supports insert/update, remove, get, contains, and utility operations like clear and print

- **BinaryTree**: In Progress...

- **BinarySearchTree**: 
  - Generic type support using `void*` pointers and `memcpy`
  - Backed by *linked nodes* with `left` and `right` child pointers
  - Proper *memory management* with deep copies of all node values
  - Custom comparison functions via `function pointers` for flexible ordering
  - *Recursive* insert, remove, and search operations
  - In-order successor deletion for nodes with two children
  - Three traversal methods: in-order, pre-order, and post-order
  - Min/max value retrieval and height calculation

- **Heap**: In Progress...

---

## Project Structure

```
structures-from-scratch/
├── archive/                    # Older implementations
│
├── generic_array/              # GenericArray library
│   ├── generic_array.h
│   └── generic_array.c
│
├── linked_list/                # LinkedList library
│   ├── linked_list.h
│   └── linked_list.c
│
├── hash_table/                # HashTable library
│   ├── hash_table.h
│   └── hash_table.c
│ 
├── binary_tree/          # BinaryTree library
│   ├── binary_tree.h
│   └── binary_tree.c
│
├── binarysearch_tree/          # BinarySearchTree library
│   ├── binarysearch_tree.h
│   └── binarysearch_tree.c
│
├── heap/                       # Heap library
│   ├── heap.h
│   └── heap.c
│
├── stack/                      # Stack library
│   ├── stack.h
│   └── stack.c
│
├── queue/                      # Queue library
│   ├── queue.h
│   └── queue.c
│
├── tests/                      # Tests
│   ├── test_ll.c
│   ├── test_bt.c
│   ├── test_bst.c
│   ├── test_ga.c
│   ├── test_ht.c
│   ├── test_stack.c
│   └── test_queue.c
└── README.md
```

---


## Performance Characteristics

### Generic Array Operations
| Operation       | Time Complexity | Notes                                                                         |
|--------------------|---------------------|----------------------------------------------------------------------- |
| `ga_append`        | **O(1) amortized**  | Adds to the end, occasionally needing resize                           |               
| `ga_add`           | **O(n)**            | Inserts at an index, requires shifting subsequent elements right.      |
| `ga_get`           | **O(1)**            | Directly accesses element by index.                                    |
| `ga_set`           | **O(1)**            | Overwrites an element at a given index.                                |
| `ga_find`          | **O(n)**            | Does a Linear Search; depends on user-supplied comparator.             |
| `ga_contains`      | **O(n)**            | Checks all elements using provided comparator.                         |
| `ga_remove_last`   | **O(1) amortized**  | Removes last element; may trigger shrink when underutilized.           |
| `ga_remove_at`     | **O(n)**            | Removes element at index and shifts remaining items left.              |
| `ga_clear`         | **O(1)**            | Sets `length` to 0 without freeing memory.                             |
| `ga_size`          | **O(1)**            | Returns current number of elements.                                    |
| `ga_capacity`      | **O(1)**            | Returns total allocated slots.                                         |
| `ga_usage`         | **O(1)**            | Computes fill ratio as percentage.                                     |
| `ga_discard`       | **O(1)**            | Frees allocated memory for array and struct.                           |
| `ga_sort`          | **O(n²)**           | Bubble sort implementation; comparator determines ordering.            |
| `ga_reverse`       | **O(n)**            | Swaps front/back elements in place.                                    |
| `ga_copy`          | **O(n)**            | Performs a deep copy of struct and all elements.                       |
| `resize`           | **O(n)**            | Allocates larger memory block and copies existing items.               |
| `shrink`           | **O(n)**            | Allocates smaller memory block and copies existing items.              |
| `shift_right`      | **O(n)**            | Moves all elements after insertion index one slot right.               |
| `shift_left`       | **O(n)**            | Moves all elements after deletion index one slot left.                 |
| `swap`             | **O(1)**            | Exchanges two items using temporary memory.                            |

### Linked List Operations
| Operation              | Time Complexity    | Notes                                                       |
|------------------------|--------------------|-------------------------------------------------------------|
| `ll_insert`            | **O(1)**           | Inserts a new node at the head of the list.                 |
| `ll_insert_tail`       | **O(1)**           | Inserts a new node at the tail of the list.                 |
| `ll_insert_at`         | **O(n)**           | Inserts a new node at a specific index.                     |
| `ll_remove`            | **O(1)**           | Removes the head node of the list.                          |
| `ll_remove_tail`       | **O(1)**           | Removes the tail node of the list.                          |
| `ll_remove_at`         | **O(n)**           | Removes a node at a specific index.                         |
| `ll_get`               | Optimized **O(n)** | Traverses to the index to retrieve the node's data.         |
| `ll_set`               | Optimized **O(n)** | Traverses to the index to update the node's data.           |
| `ll_find`              | **O(n)**           | Linear search through nodes using comparator function.      | 
| `ll_contains`          | **O(n)**           | Checks for existence of an item using comparator function.  |
| `ll_clear`             | **O(n)**           | Frees all nodes but retains list structure.                 |
| `ll_copy`              | **O(n)**           | Deep copies the entire list and its nodes.                  |
| `ll_reverse`           | **O(n)**           | Reverses the order of nodes in the list.                    |
| `ll_bsort`             | **O(n²)**          | Bubble sort implementation; comparator determines ordering. |
| `swap_nodes`           | **O(1)**           | Swaps data between two nodes.                               |
| `ll_size`              | **O(1)**           | Returns the number of nodes in the list.                    |
| `ll_is_empty`          | **O(1)**           | Checks if the list has no nodes.                            |
| `ll_discard_node`      | **O(1)**           | Frees a single node.                                        |
| `ll_discard_all_nodes` | **O(n)**           | Frees all nodes but retains list structure.                 |
| `ll_discard`           | **O(n)**           | Frees all nodes and the list structure.                     |

### Stack Operations
| Operation         | Time Complexity | Notes                                                          |
|-------------------|-----------------|----------------------------------------------------------------|
| `stack_create`    | **O(1)**        | Initializes a new empty stack.                                 |
| `stack_push`      | **O(1)**        | Adds an element to the top of the stack.                       |
| `stack_peek`      | **O(1)**        | Returns the top element without removing it.                   |
| `stack_pop`       | **O(1)**        | Removes and returns the top element of the stack.              |
| `stack_clear`     | **O(n)**        | Removes all elements from the stack.                           |
| `stack_is_empty`  | **O(1)**        | Checks if the stack is empty.                                  |
| `stack_size`      | **O(1)**        | Returns the number of elements in the stack.                   |
| `stack_discard`   | **O(n)**        | Frees all memory associated with the stack.                    |


### Queue Operations
| Operation         | Time Complexity | Notes                                                          |
|-------------------|-----------------|----------------------------------------------------------------|
| `queue_create`    | **O(1)**        | Initializes a new empty queue.                                 |
| `queue_enqueue`   | **O(1)**        | Adds an element to the end of the queue.                       |
| `queue_peek`      | **O(1)**        | Returns the front element without removing it.                 |
| `queue_dequeue`   | **O(1)**        | Removes and returns the front element of the queue.            |
| `queue_is_empty`  | **O(1)**        | Checks if the queue is empty.                                  |
| `queue_length`    | **O(1)**        | Returns the number of elements in the queue.                   |
| `queue_clear`     | **O(n)**        | Removes all elements from the queue.                           |
| `queue_discard`   | **O(n)**        | Frees all memory associated with the queue.                    |


## Hash Table Operations
| Operation         | Time Complexity       | Notes                                                     |
|-------------------|-----------------------|-----------------------------------------------------------|
| `ht_create`       | **O(1)**              | Initializes a new empty hash table.                       |
| `ht_insert `      | **O(1)** amortized    | Inserts a new key/value pair into the hash table          |
| `ht_remove`       | **O(1)** average      | Removes a key/value pair from the hash table              |
| `ht_get`          | **O(1)** average      | Retrieves a value associated with a key                   |
| `ht_contains`     | **O(1)** average      | Checks if the hash table contains a key                   |
| `ht_clear`        | **O(n)**              | Frees all nodes and resets the table                      |
| `ht_is_empty`     | **O(1)**              | Checks if the hash table is empty or not                  |
| `ht_size`         | **O(1)**              | Returns the length of the hash table                      |
| `ht_load_factor`  | **O(1)**              | Returns the current load factor of the hash table         |
| `ht_discard`      | **O(n)**              | Frees all contents of the hash table                      |


## Binary Search Tree Operations
| Operation         | Time Complexity       | Notes                                                     |
|-------------------|-----------------------|-----------------------------------------------------------|
| `bst_create`      |
| `bst_insert`      |
| `bst_remove`      |
| `bst_contains`    |
| `bst_search`      |
| `bst_min`         |
| `bst_max`         |
| `bst_height`      |
| `bst_print`       |
| `bst_inorder`     |
| `bst_postorder`   |
| `bst_preorder`    |
| `bst_size`        |
| `bst_isempty`     |
| `bst_clear`       |
| `bst_discard`     |


## Heap Operations
| Operation         | Time Complexity       | Notes                                                     |
|-------------------|-----------------------|-----------------------------------------------------------|
| `heap_create`     |
| `heap_insert`     |
| `heap_remove`     |
| `heap_peek`       |
| `heap_size`       |
| `heap_capacity`   |
| `heap_isempty`    |
| `heap_clear`      |
| `heap_discard`    |


---

## Run the Code 

### GenericArray
```bash
cd structures-from-scratch/tests
clang ../generic_array/generic_array.c ./test_ga.c -o out
./out
```

### LinkedList
```bash
cd structures-from-scratch/tests
clang ../linked_list/linked_list.c ./test_ll.c -o out
./out
```

### Stack
```bash
cd structures-from-scratch/tests
clang ../stack/stack.c ./test_stack.c -o out
./out
```

### Queue
```bash
cd structures-from-scratch/tests
clang ../queue/queue.c ./test_queue.c -o out
./out
```

### HashTable
```bash
cd structures-from-scratch/tests
clang ../hash_table/hash_table.c ./test_ht.c -o out
./out
```

### BinarySearchTree
```bash
cd structures-from-scratch/tests
clang ../binarysearch_tree/binarysearch_tree.c ./test_bst.c -o out
./out
```

### Heap
```bash
cd structures-from-scratch/tests
clang ../heap/heap.c ./test_heap.c -o out
./out
```

---

## Usage Example

### Generic Array
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
    int num1 = *(int*)a;
    int num2 = *(int*)b;
    return num1 - num2;
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

### Linked List
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

// Check if list contains a value
if (ll_contains(list, &target, compare_int)) {
    printf("List contains %d\n", target);
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

// Print the list
ll_print(list, print_int);

// Reverse the list
ll_reverse(list);

// Create a copy of the list
struct LinkedList *copy = ll_copy(list);

// Clean up
ll_discard(list);
ll_discard(copy);
```

### Stack
```c
#include "stack.h"

// Create a new stack
struct Stack *stack = stack_create();

// Check if empty
printf("Stack is empty? %d\n", stack_is_empty(stack));

// Push some integers
int value = 100;
for (int i = 0; i < 5; i++) {
    stack_push(stack, &value, sizeof(int));
}

// Print stack size
printf("Stack Size: %d\n", stack_size(stack));

// Define a print function
void print_int(void *value) {
    printf("[%d] ", *(int*)value);
}

// Print the stack
stack_print(stack, print_int);
printf("\n");

// Peek at the top element
int peek_val;
if (stack_peek(stack, &peek_val)) {
    printf("Peek Value: %d\n", peek_val);
}

// Pop an element
int pop_val;
if (stack_pop(stack, &pop_val)) {
    printf("Popped the value %d off the stack\n", pop_val);
}

printf("Stack Size after pop: %d\n", stack_size(stack));

// Clean up
stack_discard(stack);
```

## Queue
```c
#include "queue.h"

// Create a new queue
struct Queue *queue = queue_create();
printf("Initial State - Length: %d\n", queue->length);

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
    printf("Peeked the value: %d at the head of the queue\n", head);
}

// Dequeue elements
int dequeued;
if (queue_dequeue(queue, &dequeued)) {
    printf("Dequeued the value: %d\n", dequeued);
}

queue_print(queue, print_int);
printf("Queue Length: %d\n", queue_length(queue));

// Clear the queue
queue_clear(queue);
printf("Queue Size after clear: %d\n", queue_length(queue));

// Clean up
queue_discard(queue);
```

### HashTable
```c
#include "hash_table.h"

// Create a new hash table
struct HashTable *ht = ht_create();
printf("Capacity: %d, Length: %d, Load Factor: %.2f\n", 
       ht->capacity, ht->length, ht_load_factor(ht));

// Check if empty
printf("HashTable is empty: %d\n", ht_is_empty(ht));

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
    printf("Value associated with key=%d: %d\n", key, get_value);
}

// Check if key exists
int check_key = 10;
if (ht_contains(ht, &check_key, sizeof(int))) {
    printf("The hash table has key=%d\n", check_key);
} else {
    printf("Could not find key=%d in the table\n", check_key);
}

// Remove a key-value pair
int remove_key = 1;
ht_remove(ht, &remove_key, sizeof(int));

// Clear the hash table
ht_clear(ht);
printf("After clear - Capacity: %d, Length: %d\n", ht->capacity, ht->length);

// Clean up
ht_discard(ht);
```

### BinarySearchTree
```c
#include "binarysearch_tree.h"

// Create a new binary search tree
struct BinarySearchTree *bst = bst_create();
printf("Root Node: %p, Length: %d\n", bst->root, bst->length);

// Check if empty
printf("Is empty? %d\n", bst_isempty(bst));

// Define a comparison function
int compare_int(void *a, void *b) {
    int num1 = *(int*)a;
    int num2 = *(int*)b;
    
    if (num1 == num2) {
        return 0;
    } else if (num1 > num2) {
        return 1;
    } else {
        return -1;
    }
}

// Insert some integers
int nums[] = {100, 20, 300, 40};
for (int i = 0; i < 4; i++) {
    bst_insert(bst, &nums[i], sizeof(int), compare_int);
}

printf("Length: %d, Is empty? %d\n", bst_size(bst), bst_isempty(bst));

// Define a print function
void print_int(void *value) {
    printf("%d\n", *(int*)value);
}

// Print the tree with visual depth
bst_print(bst, print_int);

// Print in-order traversal
printf("In-order: ");
bst_inorder(bst, print_int);
printf("\n");

// Print post-order traversal
printf("Post-order: ");
bst_postorder(bst, print_int);
printf("\n");

// Print pre-order traversal
printf("Pre-order: ");
bst_preorder(bst, print_int);
printf("\n");

// Search for a value
int val = 100;
if (bst_contains(bst, &val, compare_int)) {
    printf("Found the value %d in the tree\n", val);
}

// Search using bst_search
if (bst_search(bst, &val, compare_int) != NULL) {
    printf("Found the value %d in the tree\n", val);
}

// Get minimum and maximum values
printf("The minimum value in the tree: %d\n", *(int*)bst_min(bst));
printf("The maximum value in the tree: %d\n", *(int*)bst_max(bst));

// Get tree height
printf("The height of the tree: %d\n", bst_height(bst));

// Remove a value
int remove_val = 100;
bst_remove(bst, &remove_val, compare_int);
bst_print(bst, print_int);

// Clear the tree
bst_clear(bst);
printf("After clear - Length: %d, Is empty? %d\n", bst_size(bst), bst_isempty(bst));

// Clean up
bst_discard(bst);
```

---