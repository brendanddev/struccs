
# Arrays from Scratch (In C)    v1.7

A dynamic, memory-efficient array implementation from scratch in C. The project initially started with a type-specific integer array but has since evolved into an improved **generic array** that supports any data type via `void*` pointers. Both versions feature automatic resizing and efficient memory management, but the main focus now is on the generic array.

---

## Implementation

- **Generic Array**:
  - Type-agnostic array supporting any data type (int, double, char, structs, etc.)
  - Uses `void*` pointers and `memcpy` for generic data handling
  - **Automatic resizing** with configurable shrink threshold (5% usage)
  - Custom comparison functions via function pointers for _contains and other operations
  - Supports adding, appending, removing, accessing, updating, and swapping elements
  - Fully memory-managed, efficient, and reusable for any type

  *(The older Dynamic Array is preserved in `archive/` for reference and comparison.)*

  - Swap elements at two indices via `_swap` function
  - Sort elements using Bubble Sort via `_sort` function
    - Accepts a comparison function pointer for custom sorting logic
  - In order reversal via `_reverse` function
  - Discard the structure and free all associated memory via `_destroy` function

---

## Project Structure

```
arrays-from-scratch/
├── archive/                    # Older DynamicArray implementation
├── generic_array/              # GenericArray library
│ ├── generic_array.h
│ └── generic_array.c
├── tests/                      # Tests and helper functions for GenericArray
│ ├── test_helpers.h
│ ├── test_helpers.c
│ └── main.c
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