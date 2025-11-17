
# Structures From Scratch (In C)    v2.5

A collection of fundamental data structures implemented from scratch in C for learning and practice. This project demonstrates low-level understanding of memory management, pointer arithmetic, and algorithmic thinking without relying on standard library implementations.

---

## Overview

This project began as a simple **integer array** and has evolved into a comprehensive exploration of data structures in C. The focus is on building real, working implementations with proper memory management, performance considerations, and generic design patterns.

### Currently Implemented

- **GenericArray**: A type-agnostic, dynamically resizing array that can store any data type using `void*` pointers and function pointers for custom operations.

- **LinkedList**: In progress...

### Planned Implementations

- **Stack & Queue**
- **Hash Table**
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

---

## Project Structure

```
structures-from-scratch/
├── archive/                    # Older DynamicArray implementation
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
| Operation       | Time Complexity | Notes                                                                      |
|-----------------|---------------------|----------------------------------------------------------------------- |
| `_append`       | **O(1) amortized**  | Adds to the end, occasionally needing resize                           |               
| `_add`          | **O(n)**            | Inserts at an index, requires shifting subsequent elements right.      |
| `_get`          | **O(1)**            | Directly accesses element by index.                                    |
| `_set`          | **O(1)**            | Overwrites an element at a given index.                                |
| `_find`         | **O(n)**            | Does a Linear Search; depends on user-supplied comparator.             |
| `_contains`     | **O(n)**            | Checks all elements using provided comparator.                         |
| `_remove_last`  | **O(1) amortized**  | Removes last element; may trigger shrink when underutilized.           |
| `_remove_at`    | **O(n)**            | Removes element at index and shifts remaining items left.              |
| `_clear`        | **O(1)**            | Sets `length` to 0 without freeing memory.                             |
| `_size`         | **O(1)**            | Returns current number of elements.                                    |
| `_capacity`     | **O(1)**            | Returns total allocated slots.                                         |
| `_usage`        | **O(1)**            | Computes fill ratio as percentage.                                     |
| `_discard`      | **O(1)**            | Frees allocated memory for array and struct.                           |
| `_sort`         | **O(n²)**           | Bubble sort implementation; comparator determines ordering.            |
| `_reverse`      | **O(n)**            | Swaps front/back elements in place.                                    |
| `_copy`         | **O(n)**            | Performs a deep copy of struct and all elements.                       |
| `resize`        | **O(n)**            | Allocates larger memory block and copies existing items.               |
| `shrink`        | **O(n)**            | Allocates smaller memory block and copies existing items.              |
| `shift_right`   | **O(n)**            | Moves all elements after insertion index one slot right.               |
| `shift_left`    | **O(n)**            | Moves all elements after deletion index one slot left.                 |
| `swap`          | **O(1)**            | Exchanges two items using temporary memory.                            |

### Linked List Operations
| Operation       | Time Complexity | Notes                                                       |
|-----------------|-----------------|-------------------------------------------------------------|

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

---