
# Dynamic Array From Scratch (In C)

A dynamic array implementation in C that demonstrates manual memory management, automatic resizing, and fundamental data structure operations.

---

## Project Structure

```
├── dynamic_array.h       # Header file with struct definition and function declarations
├── dynamic_array.c       # Implementation of all dynamic array operations
├── main.c                # Demo program showing usage
└── README.md
```

---

## Performance Characteristics

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
git clone https://github.com/brendanddev/array-from-scratch.git
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