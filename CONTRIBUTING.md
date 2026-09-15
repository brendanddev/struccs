# Contributing to struccs

Thanks for your interest in contributing. struccs is a handwritten, dependency-free 
C library built from scratch with a focus on learning, memory management, and 
type-agnostic design. Contributions are welcome as long as they align with that philosophy.

---

## Use of AI Tools

AI tools (Claude, Codex, Cursor) have been used in a limited capacity during development:

- Discussing ideas, design decisions, and tradeoffs
- Code review and feedback on existing implementations
- Mechanical refactoring tasks (e.g. find-and-replace style changes)
- Documentation suggestions

All core implementations - data structures, algorithms, memory management, and API 
design — were written by hand without AI generation. This is intentional; the primary 
goal of struccs is deep learning and genuine understanding of systems-level C programming.

Contributors are expected to follow the same standard. AI-generated core logic or 
implementations will not be accepted.

---

## Project Philosophy

struccs is built on a few core principles:

- No dependencies — no standard container libraries, no third party code
- Generic by design — structures work with any data type via `void*` and function pointers
- Memory conscious — every allocation has a corresponding free, ownership is always clear
- Readable — code should be understandable to someone learning C, not just experts

Keep these in mind when contributing.

---

## Getting Started

```bash
git clone https://github.com/brendanddev/struccs.git
cd struccs
make
make test_all
```

See [README.md](README.md) for full build and usage instructions.

---

## Adding a New Structure

Follow this checklist when adding a new data structure:

1. Create `include/structure_name.h` — public API and struct definition
2. Create `src/structure_name.c` — implementation
3. Create `tests/test_structure_name.c` — test suite
4. Add a test target to the `Makefile`
5. Add the structure to `test_all` in the `Makefile`
6. Update the structures table in `README.md`
7. Add the header to `struccs.h` if an umbrella header exists

---

## Code Style

**Naming**
- Functions follow the `structure_operation` pattern — `ga_append`, `bst_insert`, `ht_remove`
- Structs use PascalCase — `GenericArray`, `BinarySearchTree`
- Internal/static helpers are lowercase with underscores — `shift_left`, `resize`

**Comments**
- Comment *why*, not *what* — avoid restating what the code already says
- Public headers get a brief docstring per function
- Implementation files get a file header comment, nothing more unless the logic is non-obvious

**Memory**
- Every allocation must have a corresponding free
- Ownership must be clear — document who is responsible for freeing data passed via `void*`
- Always handle allocation failure — never assume `malloc` succeeds

---

## Testing

Every new structure needs a test file in `tests/` covering:

- Initialization
- Basic operations
- Edge cases (empty structure, single element, duplicates where relevant)
- Cleanup — no memory leaks

Tests use the macros defined in `tests/test_utils.h`:

```c
ASSERT_EQ(actual, expected);
ASSERT_TRUE(expr);
ASSERT_FALSE(expr);
ASSERT_NULL(ptr);
ASSERT_NOT_NULL(ptr);
TEST(function_name);
```

---

## Submitting Changes

- Fork the repo and create a branch for your change
- Keep PRs focused — one structure or fix per PR
- Make sure `make test_all` passes before submitting
- Update documentation if your change affects the public API

---

## License

By contributing, you agree that your contributions will be licensed under the 
same MIT License that covers this project.
