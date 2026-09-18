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

## Type Conventions

- **Byte sizes and byte counts** — anything passed to `malloc`/`realloc`/ `memcpy`, or documented as "N bytes" — use `size_t`.
- **Element counts** — how many items/nodes/entries a structure holds — use `int`.
- **`String` is a deliberate exception**: its `length`/`capacity` fields are `size_t`, not `int`, because for a string, 1 character is 1 byte, so its element count and byte count are the same value. This mirrors how `strlen` works in the C standard library.
- When adding a new structure, if a field or parameter represents a byte quantity, it must be `size_t`. If in doubt, ask: "does this ever get multiplied against or compared to something `sizeof` or `malloc` would produce?" If yes, it's `size_t`.

---

## Error Handling

struccs follows one consistent convention for reporting failure:

- **Constructors** (`_create`) return `NULL` on allocation failure. Never call `exit()` or `abort()` from library code — a library must never unilaterally kill the caller's process.
- **Operations** that can fail (insert, remove, set, get) return `bool` — `true` on success, `false` on failure. They do not report *why* an operation failed beyond that.
- **`Result`** is available for cases where a caller genuinely needs to know *why* something failed, not just that it did. It is not the default return type — most functions don't need it. Use it deliberately, not reflexively.
- **`Option`** is available for representing "a value may or may not be present" as a return type, as an alternative to sentinel values (`-1`, `NULL`) or out-parameters plus a `bool`.

When a function performs a secondary operation that isn't essential to its own contract (e.g. `shrink()` after a successful removal, purely to reclaim memory), a failure in that secondary step should not cause the primary operation to report failure. Document this explicitly in the function's comment if it isn't obvious.

Every caller of a function that can return `NULL` or `false` is responsible for checking it before using the result.

---

## Const-Correctness

- Any pointer parameter that a function only reads from — never writes through, directly or via a helper it calls — should be `const`.
- This includes: struct pointers passed to query/inspection functions (`_size`, `_isempty`, `_get`, `_contains`, `_print`), `void*` data parameters that are only copied out of (not written to), and comparator/callback function pointer parameters.
- A function that *mutates* a structure should not be marked `const`, even if it would technically compile, C's `const` is shallow, so a `const` struct pointer doesn't prevent writes through a member pointer inside it. Marking a mutating function `const` would compile but lie about what the function does. Correctness of intent matters more than what the compiler will silently allow.
- A function that returns a pointer *into* a structure it was given as `const` (e.g. searching a tree and returning a pointer to a found node) may keep a non-`const` return type. Forcing the return type `const` too is a legitimate stricter option, but is not required — document the choice either way rather than leaving it accidental.
- When changing a callback's parameter types to `const`, every function that accepts that callback type, and every test file with a matching callback, must be updated in the same change. A callback signature mismatch is a compile error, not a warning.

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

Every public function should have at least one test exercising its documented behavior, including its failure/edge-case paths, not just its happy path — a test suite that only calls a function once, successfully, does not protect against regressions in how that function handles invalid input, empty structures, or allocation failure.

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
