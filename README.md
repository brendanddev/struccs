# struccs
A lightweight, generic C library of fundamental data structures built from scratch with a focus on memory management, performance, and type-agnostic design.

---

## Overview
A collection of generic, reusable data structures implemented in C using `void*` pointers, 
function pointers, and manual memory management — no dependencies, no standard container 
libraries.

---

## Structures
| Structure | Description |
|---|---|---|
| GenericArray | Type-agnostic dynamically resizing array |
| LinkedList | Doubly linked list with bidirectional traversal |
| Stack | LIFO structure backed by linked nodes |
| Queue | FIFO structure backed by linked nodes |
| HashTable | Generic hash table with separate chaining |
| BinarySearchTree | Generic BST with recursive operations |
| BinaryTree | Complete binary tree backed by flat array |
| Heap | Min/max heap |

---

## Project Structure

```
struccs/
├── include/                    # Public headers
│   ├── generic_array.h
│   ├── linked_list.h
│   ├── stack.h
│   ├── queue.h
│   ├── hash_table.h
│   ├── binary_tree.h
│   ├── binarysearch_tree.h
│   └── heap.h
├── src/                        # Implementations
│   ├── generic_array.c
│   ├── linked_list.c
│   ├── stack.c
│   ├── queue.c
│   ├── hash_table.c
│   ├── binary_tree.c
│   ├── binarysearch_tree.c
│   └── heap.c
├── tests/                      # Test suites
├── docs/                       # Documentation
│   ├── USAGE.md
│   ├── API.md
│   └── PERFORMANCE.md
├── Makefile
├── LICENSE
└── README.md
```
 
---

## Building

Clone the repo and build the static library:
 
```bash
git clone https://github.com/brendanddev/struccs.git
cd struccs
make
```
 
This produces `build/libstruccs.a`.
 
To run a specific test:
 
```bash
make test_ga
make test_ll
make test_bt
# etc...
```
 
To run all tests:
 
```bash
make test_all
```
 
To clean build artifacts:
 
```bash
make clean
```

---

## Usage
 
Include the umbrella header to get everything:
 
```c
#include "strucc.h"
```
 
Or include individual headers:
 
```c
#include "generic_array.h"
#include "linked_list.h"
```
 
Link against the static library when compiling:
 
```bash
clang myprogram.c -I/path/to/struccs/include -L/path/to/struccs/build -lstruccs -o myprogram
```
 
See [docs/usage.md](docs/usage.md) for full code examples for each structure.
 
---

## Docs
 
- [Usage Examples](docs/usage.md)
- [API Reference](docs/api.md)
- [Performance](docs/performance.md)

---

## License
 
MIT License — see [LICENSE](LICENSE) for details.