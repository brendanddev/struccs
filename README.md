
# Arrays from Scratch (In C)

A dynamic array implementation in C that demonstrates manual memory management, automatic resizing, and fundamental data structure operations.

---

## Implementations

1. **Dynamic Array**: A simple dynamic array that stores integers with automatic resizing capabilities.

2. **Generic Array**: In progress...

---
## Project Structure

```
arrays-from-scratch/
├── dynamic_array/
│   ├── dynamic_array.h
│   ├── dynamic_array.c
│   └── main.c
├── generic_array/
│   ├── generic_array.h
│   ├── generic_array.c
│   └── main.c
└── README.md
```

---

## Performance Characteristics

### Dynamic Array Operations
|Operation|Time Complexity|Notes|
|---------|---------------|-----|
| add     | O(1) amortized | O(n) when resize needed |
| add_at  | O(n)           | Requires shifting elements |
| get     | O(1)           | Direct array access |
| remove  | O(n)           | Must search for element |
| remove_at | O(n)         | Requires shifting elements |
| remove_back | O(1)       | No shifting needed |

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