
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

So for _add, its O(n) since the operation requires shifting subsequent elements right which is O(n), and is amortized since sometimes a resize is triggered and is O(n)?


## Performance Characteristics

### Dynamic Array Operations
| Operation       | Time Complexity | Notes                                                                  |
|-----------------|-----------------|----------------------------------------------------------------------- |
| _add            | O(n) amortized  | Requires shifting subsequent elements right and occasionally resizing. |
| _append         |                 |                                                                        |                                     
| _get            |                 |                 |
| _set            |                 |                 |
| _remove_last    |                 |                 |
| _remove_at      |                 |                 |
| _remove         |                 |                 |
| _contains       |                 |                 |
| resize          |                 |                 |
| shrink          |                 |                 |
| shift_right     |                 |                 |
| shift_left      |                 |                 |


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