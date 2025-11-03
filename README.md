
# Arrays from Scratch (In C)    v0.1

I’m currently implementing a **dynamically resizing, memory-efficient array** from scratch in **C**.  
This involves optimizing how capacity expands and contracts to balance **performance** and **memory usage**.

Once this is complete, I plan to build on it by creating a **generic dynamically resizing array** that supports **`void*` types**, allowing storage of any data type while maintaining efficiency.

---

## Implementations

1. **Dynamic Array**: In progress...
2. **Generic Array**: In progress...

---
## Project Structure

```
arrays-from-scratch/
├── dynamic_array/
│   ├── dynamic_array.h
│   ├── dynamic_array.c
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


---

## Run the Code

1. Clone the repository:
```bash
git clone https://github.com/brendanddev/arrays-from-scratch.git
cd array-from-scratch
```

2. Compile the code using `clang`:
```bash
clang main.c -o out
```

3. Run the executable:
```bash
./out
```

---