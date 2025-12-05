
# Structures From Scratch (In C)    v3.4

A collection of fundamental data structures implemented from scratch in C for learning and practice. This project demonstrates low-level understanding of memory management, pointer arithmetic, and algorithmic thinking without relying on standard library implementations.

---

## Overview

This project began as a simple **integer array** and has evolved into a comprehensive exploration of data structures in C. The focus is on building real, working implementations with proper memory management, performance considerations, and generic design patterns.

### Currently Implemented

- **GenericArray**: A type-agnostic, dynamically resizing array that can store any data type using `void*` pointers and function pointers for custom operations.

- **LinkedList**: A fully functional doubly linked list with generic type support, bidirectional traversal optimization, and comprehensive manipulation operations.

- **Stack**: A LIFO data structure backed by linked nodes with generic type support for storing any data type.

- **Queue**: A FIFO data structure backed by linked nodes with generic type support for storing any data type.

- **HashTable**: In Progres...


### Planned Implementations

- **Binary Search Tree**
- **Heap / Priority Queue**
- More advanced structures as the project evolves

---

## Implementations

- **Generic Array**:
  - Type-agnostic array supporting any data type (int, double, char, structs, etc.)
  - Uses `void*` pointers and `memcpy` for generic data handling
  - **Automatic resizing** with configurable shrink threshold (5% usage)
  - Custom comparison functions via function pointers for _contains and other operations
  - Supports adding, appending, removing, accessing, updating, and swapping elements
  - Fully memory-managed, efficient, and reusable for any type
  - Deep copy of the entire structure and its elements via `_copy` function
  - Sort elements using Bubble Sort via `_sort` function
    - Accepts a comparison function pointer for custom sorting logic
  - In-order reversal via `_reverse` function
  - Binary Search implementation for sorted arrays via `_binary_find` function
    - Requires a sorted array and a comparison function pointer
  - Swap elements at two indices via `_swap` function
  - Discard the structure and free all associated memory via `_discard` function

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

- **HashTable**: *(Planned)*

---

## Project Structure

```
structures-from-scratch/
├── archive/                    # Older implementations
├── generic_array/              # GenericArray library
│ ├── generic_array.h
│ └── generic_array.c
├── linked_list/                # LinkedList library
│ ├── linked_list.h
│ └── linked_list.c
├── tests/                      # Tests and helper functions for GenericArray
│ ├── test_helpers.h
│ ├── test_helpers.c
│ ├── test_ll.c
│ └── test_ga.c
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
| Operation       | Time Complexity    | Notes                                                       |
|-----------------|--------------------|-------------------------------------------------------------|
| ll_insert       | **O(1)**           | Inserts a new node at the head of the list.                 |
| ll_insert_tail  | **O(1)**           | Inserts a new node at the tail of the list.                 |
| ll_insert_at    | **O(n)**           | Inserts a new node at a specific index.                     |
| ll_remove       | **O(1)**           | Removes the head node of the list.                          |
| ll_remove_tail  | **O(1)**           | Removes the tail node of the list.                          |
| ll_remove_at    | **O(n)**           | Removes a node at a specific index.                         |
| ll_get          | Optimized **O(n)** | Traverses to the index to retrieve the node's data.         |
| ll_set          | Optimized **O(n)** | Traverses to the index to update the node's data.           |
| ll_find         | **O(n)**           | Linear search through nodes using comparator function.      | 
| ll_contains     | **O(n)**           | Checks for existence of an item using comparator function.  |
| ll_clear        | **O(n)**           | Frees all nodes but retains list structure.                 |
| ll_copy         | **O(n)**           | Deep copies the entire list and its nodes.                  |
| ll_reverse      | **O(n)**           | Reverses the order of nodes in the list.                    |
| ll_bsort        | **O(n²)**          | Bubble sort implementation; comparator determines ordering. |
| swap_nodes      | **O(1)**           | Swaps data between two nodes.                               |
| ll_size         | **O(1)**           | Returns the number of nodes in the list.                    |
| ll_is_empty     | **O(1)**           | Checks if the list has no nodes.                            |
| ll_discard_node | **O(1)**           | Frees a single node.                                        |
| ll_discard_all_nodes | **O(n)**      | Frees all nodes but retains list structure.                 |
| ll_discard      | **O(n)**           | Frees all nodes and the list structure.                     |

---

## Run the Code

### Generic Array
1. Navigate to the generic_array directory:
```bash
cd arrays-from-scratch/generic_array
```

2. Compile with all source files:
```bash
clang generic_array.c utils.c main.c -o out
```

3. Run the executable:
```bash
./out
```

---

## Usage Example

### Generic Array
```c
#include "generic_array.h"

// Create an array for integers
struct GenericArray *ga = _init(sizeof(int));

// Add some elements
int values[] = {42, 17, 89, 3};
for (int i = 0; i < 4; i++) {
    _append(ga, &values[i]);
}

// Define a custom comparison function
bool compare_int(void *a, void *b) {
    return (*(int*)a == *(int*)b);
}

// Search for a value
int target = 17;
if (_contains(ga, compare_int, &target)) {
    printf("Found %d in the array!\n", target);
}

// Clean up
_discard(ga);
```

### Linked List
```c
#include "linked_list.h"

// Create a new linked list
struct LinkedList *list = ll_init();

// Add some integers
int values[] = {10, 20, 30, 40};
for (int i = 0; i < 4; i++) {
    struct Node *node = ll_init_node(&values[i], sizeof(int));
    ll_insert_tail(node, list);
}

// Define a comparison function
bool compare_int(void *a, void *b) {
    return (*(int*)a == *(int*)b);
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

// Reverse the list
ll_reverse(list);

// Clean up
ll_discard(list);
```

---