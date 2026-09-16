# struccs

A lightweight, generic C library, built from scratch, providing data structures, common types, and low-level memory tools. No dependencies, no standard container libraries. Just `void*`, function pointers, and manual memory management.

> Version 0.14.7

---

## Why struccs?

C gives you the building blocks but none of the infrastructure. struccs fills that gap — generic data structures, common types, and memory tools, all handwritten, all dependency-free, all designed to work together.

---

## Quick Start

```bash
git clone https://github.com/brendanddev/struccs.git
cd struccs
make
```

This builds `build/libstruccs.a`. Then in your project:

```c
#include "struccs.h"

int main(void) {
    GenericArray *arr = ga_create(sizeof(int), 4);
    int value = 42;
    ga_push(arr, &value);
    // ...
    ga_discard(arr);
    return 0;
}
```

Compile and link:

```bash
clang myprogram.c -I/path/to/struccs/include -L/path/to/struccs/build -lstruccs -o myprogram
```

For full examples per structure, see [docs/USAGE.md](docs/USAGE.md).

---

## Available Structures

| Structure          | Description                                      | Header                   |
|---------------------|---------------------------------------------------|---------------------------|
| `GenericArray`      | Type-agnostic, dynamically resizing array        | `generic_array.h`        |
| `LinkedList`        | Doubly linked list with bidirectional traversal  | `linked_list.h`           |
| `Stack`             | LIFO structure backed by linked nodes            | `stack.h`                 |
| `Queue`             | FIFO structure backed by linked nodes            | `queue.h`                 |
| `HashTable`         | Generic hash table with separate chaining        | `hash_table.h`            |
| `BinarySearchTree`  | Generic BST with recursive operations            | `binarysearch_tree.h`     |
| `BinaryTree`        | Complete binary tree backed by a flat array      | `binary_tree.h`           |
| `Heap`              | Min/max heap                                     | `heap.h`                   |
| `Set`               | Generic set backed by a hash table               | `set.h`                    |

Each structure ships with its own header and source file, and can be used independently or together via the umbrella header.

## Types

| Type      | Description                                | Header     |
|-----------|--------------------------------------------|------------|
| `Result`  | Operation result wrapping a value or error | `result.h` |
| `Option`  | Wrapper representing an optional value     | `option.h` |
| `String`  | Dynamic, resizable string type             | `str.h`    |

## Memory Management

| Component      | Description                                                 | Header           |
|----------------|-------------------------------------------------------------|------------------|
| `MemoryPool`   | Fixed-size block allocator backed by a pre-allocated buffer | `memory_pool.h`  |

---

## Usage

**Option 1 — Umbrella header** (includes everything):

```c
#include "struccs.h"
```

**Option 2 — Individual headers** (include only what you need):

```c
#include "generic_array.h"
#include "linked_list.h"
```

---

## Building & Testing

| Command          | Description                          |
|-------------------|----------------------------------------|
| `make`            | Build the static library (`build/libstruccs.a`) |
| `make test_all`   | Run all test suites                  |
| `make test_ga`    | Run a specific test (e.g. GenericArray) |
| `make clean`      | Remove build artifacts               |

Each structure has its own test target (`test_ll`, `test_bt`, `test_hash`, etc.) — check the [Makefile](Makefile) for the full list.

---

## Project Structure

struccs/
├── include/            # Public headers
├── src/                # Implementations
├── tests/              # Test suites
├── docs/               # Documentation
│   ├── USAGE.md        # Usage examples for each structure
│   ├── API.md          # Full API reference
│   └── PERFORMANCE.md  # Benchmarks & complexity notes
├── Makefile
├── LICENSE
└── README.md

---

## Documentation

- [Usage Examples](docs/USAGE.md) — code examples for every structure
- [API Reference](docs/API.md) — full function signatures and behavior
- [Performance](docs/PERFORMANCE.md) — benchmarks and complexity analysis

---

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for full guidelines on:
- Project design principles (no dependencies, generic by design, memory-conscious)
- Code style and structure conventions
- Testing requirements
- Pull request process

---

## License

MIT License — see [LICENSE](LICENSE) for details.
