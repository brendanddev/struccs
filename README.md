
# Arrays from Scratch (In C)    v1.4

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
├── archive/                # Older DynamicArray implementation
├── generic_array/          # GenericArray implementation
│   ├── generic_array.h
│   ├── generic_array.c
│   ├── utils.h
│   ├── utils.c
│   └── main.c
└── README.md
```

---


## Performance Characteristics

### Dynamic Array Operations
| Operation       | Time Complexity | Notes                                                                  |
|-----------------|-----------------|----------------------------------------------------------------------- |
| _add            | O(n) amortized  | Requires shifting subsequent elements right and occasionally resizing  |
| _append         | O(1) amortized  | Adds to the end, occasionally needing resize                           |               
| _get            | O(1)            | Accesses an element by index                                           |
| _set            | O(1)            | Overwrites an element in memory                                        |
| _remove_last    | O(1) amortized  | Accesses and removes last element, ocasionally shrinking               |
| _remove_at      | O(n)            | Requires shifting subsequent elements left, best case O(1)             |
| _remove         | O(n)            | Searches for item to remove, shifting subsequent elements left only when the item is found |
| _contains       | O(n)            | Searches for the item                                                  |
| resize          | O(n)            | Copies all existing elements to the new larger memory block            |
| shrink          | O(n)            | Copies all existing elements to the new smaller memory block           |
| shift_right     | O(n)            | Shifts all subsequent elements to the right                            |
| shift_left      | O(n)            | Shifts all subsequent elements to the left                             |


### Generic Array Operations
| Operation       | Time Complexity | Notes                                                                  |
|-----------------|-----------------|----------------------------------------------------------------------- |


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

## Future Enhancements

- **Copy Function** - Deep/shallow copy of arrays
  - Copy array structure and all elements
  - Consider deep copy with custom copy function for complex types
- **Binary Search** - Efficient search for sorted arrays
- **Fix Shrinking Thrashing** - Prevent resize-shrink-resize cycles