# API Reference

Function signatures and descriptions for all structures in the struccs library.

---

## Generic Array

```c
struct GenericArray* ga_create(size_t element_size);
```
Creates and returns a new empty generic array for elements of the given size. Returns `NULL` on failure.

```c
bool ga_append(struct GenericArray *ga, void *value);
```
Appends a value to the end of the array. Resizes automatically if needed.

```c
bool ga_add(struct GenericArray *ga, void *value, int index);
```
Inserts a value at the given index, shifting subsequent elements right.

```c
bool ga_get(struct GenericArray *ga, int index, void *out);
```
Copies the element at the given index into `out`. Returns `false` if out of bounds.

```c
bool ga_set(struct GenericArray *ga, int index, void *value);
```
Overwrites the element at the given index. Returns `false` if out of bounds.

```c
bool ga_find(struct GenericArray *ga, void *value, int (*comparator)(void*, void*));
```
Returns the index of the first matching element using the comparator, or `-1` if not found.

```c
bool ga_contains(struct GenericArray *ga, void *value, int (*comparator)(void*, void*));
```
Returns `true` if the array contains the given value using the comparator.

```c
bool ga_remove_last(struct GenericArray *ga);
```
Removes the last element. May trigger a shrink if utilization drops below 5%.

```c
bool ga_remove_at(struct GenericArray *ga, int index);
```
Removes the element at the given index, shifting remaining elements left.

```c
void ga_clear(struct GenericArray *ga);
```
Sets length to 0 without freeing memory.

```c
int ga_size(struct GenericArray *ga);
```
Returns the current number of elements.

```c
int ga_capacity(struct GenericArray *ga);
```
Returns the total number of allocated slots.

```c
float ga_usage(struct GenericArray *ga);
```
Returns the fill ratio as a percentage.

```c
void ga_sort(struct GenericArray *ga, int (*comparator)(void*, void*));
```
Sorts the array using bubble sort with the provided comparator.

```c
void ga_reverse(struct GenericArray *ga);
```
Reverses the array in place.

```c
struct GenericArray* ga_copy(struct GenericArray *ga);
```
Returns a deep copy of the array and all its elements.

```c
bool ga_swap(struct GenericArray *ga, int i, int j);
```
Swaps the elements at indices `i` and `j`.

```c
void ga_discard(struct GenericArray *ga);
```
Frees all memory associated with the array.

---

## Linked List

```c
struct LinkedList* ll_create();
```
Creates and returns a new empty doubly linked list. Returns `NULL` on failure.

```c
bool ll_insert(struct LinkedList *list, void *value, size_t size);
```
Inserts a new node at the head of the list.

```c
bool ll_insert_tail(struct LinkedList *list, void *value, size_t size);
```
Inserts a new node at the tail of the list.

```c
bool ll_insert_at(struct LinkedList *list, void *value, size_t size, int index);
```
Inserts a new node at the given index.

```c
bool ll_remove(struct LinkedList *list);
```
Removes the head node.

```c
bool ll_remove_tail(struct LinkedList *list);
```
Removes the tail node.

```c
bool ll_remove_at(struct LinkedList *list, int index);
```
Removes the node at the given index.

```c
bool ll_get(struct LinkedList *list, int index, void *out);
```
Copies the value at the given index into `out` using optimized bidirectional traversal.

```c
bool ll_set(struct LinkedList *list, int index, void *value);
```
Updates the value at the given index using optimized bidirectional traversal.

```c
int ll_find(struct LinkedList *list, void *value, bool (*comparator)(void*, void*));
```
Returns the index of the first matching element, or `-1` if not found.

```c
bool ll_contains(struct LinkedList *list, void *value, bool (*comparator)(void*, void*));
```
Returns `true` if the list contains the given value.

```c
void ll_reverse(struct LinkedList *list);
```
Reverses the order of nodes in place.

```c
struct LinkedList* ll_copy(struct LinkedList *list);
```
Returns a deep copy of the list and all its nodes.

```c
void ll_bsort(struct LinkedList *list, int (*comparator)(void*, void*));
```
Sorts the list using bubble sort with the provided comparator.

```c
int ll_size(struct LinkedList *list);
```
Returns the number of nodes.

```c
bool ll_is_empty(struct LinkedList *list);
```
Returns `true` if the list has no nodes.

```c
void ll_clear(struct LinkedList *list);
```
Frees all nodes but retains the list structure.

```c
void ll_discard(struct LinkedList *list);
```
Frees all nodes and the list structure.

---

## Stack

```c
struct Stack* stack_create();
```
Creates and returns a new empty stack. Returns `NULL` on failure.

```c
bool stack_push(struct Stack *stack, void *value, size_t size);
```
Pushes a value onto the top of the stack.

```c
bool stack_peek(struct Stack *stack, void *out);
```
Copies the top element into `out` without removing it.

```c
bool stack_pop(struct Stack *stack, void *out);
```
Removes the top element and copies it into `out`.

```c
bool stack_is_empty(struct Stack *stack);
```
Returns `true` if the stack has no elements.

```c
int stack_size(struct Stack *stack);
```
Returns the number of elements.

```c
void stack_clear(struct Stack *stack);
```
Removes all elements from the stack.

```c
void stack_print(struct Stack *stack, void (*print_fn)(void*));
```
Prints the stack using the provided print function.

```c
void stack_discard(struct Stack *stack);
```
Frees all memory associated with the stack.

---

## Queue

```c
struct Queue* queue_create();
```
Creates and returns a new empty queue. Returns `NULL` on failure.

```c
bool queue_enqueue(struct Queue *queue, void *value, size_t size);
```
Adds a value to the end of the queue.

```c
bool queue_peek(struct Queue *queue, void *out);
```
Copies the front element into `out` without removing it.

```c
bool queue_dequeue(struct Queue *queue, void *out);
```
Removes the front element and copies it into `out`.

```c
bool queue_is_empty(struct Queue *queue);
```
Returns `true` if the queue has no elements.

```c
int queue_length(struct Queue *queue);
```
Returns the number of elements.

```c
void queue_clear(struct Queue *queue);
```
Removes all elements from the queue.

```c
void queue_print(struct Queue *queue, void (*print_fn)(void*));
```
Prints the queue using the provided print function.

```c
void queue_discard(struct Queue *queue);
```
Frees all memory associated with the queue.

---

## Hash Table

```c
struct HashTable* ht_create();
```
Creates and returns a new empty hash table. Returns `NULL` on failure.

```c
bool ht_insert(struct HashTable *ht, void *key, size_t key_size, void *value, size_t value_size);
```
Inserts a key/value pair. Updates the value if the key already exists. Resizes when load factor exceeds 0.75.

```c
bool ht_remove(struct HashTable *ht, void *key, size_t key_size);
```
Removes the key/value pair associated with the given key.

```c
bool ht_get(struct HashTable *ht, void *key, size_t key_size, void *out);
```
Copies the value associated with the key into `out`. Returns `false` if not found.

```c
bool ht_contains(struct HashTable *ht, void *key, size_t key_size);
```
Returns `true` if the hash table contains the given key.

```c
bool ht_is_empty(struct HashTable *ht);
```
Returns `true` if the table has no entries.

```c
int ht_size(struct HashTable *ht);
```
Returns the number of entries.

```c
float ht_load_factor(struct HashTable *ht);
```
Returns the current load factor.

```c
void ht_clear(struct HashTable *ht);
```
Frees all entries and resets the table.

```c
void ht_print(struct HashTable *ht, void (*print_fn)(void*, void*));
```
Prints all key/value pairs using the provided print function.

```c
void ht_discard(struct HashTable *ht);
```
Frees all memory associated with the hash table.

---

## Binary Search Tree

```c
struct BinarySearchTree* bst_create();
```
Creates and returns a new empty BST. Returns `NULL` on failure.

```c
bool bst_insert(struct BinarySearchTree *bst, void *value, size_t size, int (*comparator)(void*, void*));
```
Recursively inserts a value using the comparator for ordering.

```c
bool bst_remove(struct BinarySearchTree *bst, void *value, int (*comparator)(void*, void*));
```
Recursively removes a value. Uses in-order successor deletion for nodes with two children.

```c
bool bst_contains(struct BinarySearchTree *bst, void *value, int (*comparator)(void*, void*));
```
Returns `true` if the BST contains the given value.

```c
struct Node* bst_search(struct BinarySearchTree *bst, void *value, int (*comparator)(void*, void*));
```
Returns a pointer to the node containing the value, or `NULL` if not found.

```c
void* bst_min(struct BinarySearchTree *bst);
```
Returns a pointer to the minimum value in the tree.

```c
void* bst_max(struct BinarySearchTree *bst);
```
Returns a pointer to the maximum value in the tree.

```c
int bst_height(struct BinarySearchTree *bst);
```
Returns the height of the tree.

```c
void bst_inorder(struct BinarySearchTree *bst, void (*print_fn)(void*));
```
Traverses and prints the tree in-order (Left → Root → Right).

```c
void bst_preorder(struct BinarySearchTree *bst, void (*print_fn)(void*));
```
Traverses and prints the tree pre-order (Root → Left → Right).

```c
void bst_postorder(struct BinarySearchTree *bst, void (*print_fn)(void*));
```
Traverses and prints the tree post-order (Left → Right → Root).

```c
int bst_size(struct BinarySearchTree *bst);
```
Returns the number of nodes.

```c
bool bst_isempty(struct BinarySearchTree *bst);
```
Returns `true` if the tree has no nodes.

```c
void bst_clear(struct BinarySearchTree *bst);
```
Frees all nodes but retains the tree structure.

```c
void bst_discard(struct BinarySearchTree *bst);
```
Frees all nodes and the tree structure.

---

## Binary Tree

```c
struct BinaryTree* bt_create(size_t element_size);
```
Creates and returns a new empty binary tree for elements of the given size. Returns `NULL` on failure.

```c
void bt_insert(struct BinaryTree *tree, void *value);
```
Inserts a value at the next available position. Resizes automatically if needed.

```c
void bt_remove(struct BinaryTree *tree, int index);
```
Removes the element at the given index by swapping it with the last element and decrementing length.

```c
bool bt_get(struct BinaryTree *tree, int index, void *out);
```
Copies the element at the given index into `out`. Returns `false` if out of bounds.

```c
bool bt_set(struct BinaryTree *tree, int index, void *value);
```
Overwrites the element at the given index. Returns `false` if out of bounds.

```c
bool bt_contains(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
```
Returns `true` if the tree contains the given value using the comparator.

```c
int bt_find(struct BinaryTree *tree, void *value, int (*comparator)(void*, void*));
```
Returns the index of the first matching element, or `-1` if not found.

```c
int bt_height(struct BinaryTree *tree);
```
Returns the height of the tree — the number of edges from the root to the deepest leaf.

```c
int bt_leaves(struct BinaryTree *tree);
```
Returns the number of leaf nodes (nodes with no children).

```c
int bt_size(struct BinaryTree *tree);
```
Returns the current number of elements.

```c
int bt_capacity(struct BinaryTree *tree);
```
Returns the total number of allocated slots.

```c
bool bt_isempty(struct BinaryTree *tree);
```
Returns `true` if the tree has no elements.

```c
void bt_clear(struct BinaryTree *tree);
```
Sets length to 0 without freeing memory.

```c
void bt_print(struct BinaryTree *tree, void (*print_fn)(void*));
```
Prints the tree in a tree-like structure using the provided print function.

```c
void bt_discard(struct BinaryTree *tree);
```
Frees all memory associated with the binary tree.

---

## Heap

```c
struct Heap* heap_create(size_t element_size);
```
Creates and returns a new empty max-heap for elements of the given size. Returns `NULL` on failure.

```c
bool heap_insert(struct Heap *heap, void *value, size_t vsize, int (*compare)(void*, void*));
```
Inserts a value into the heap and heapifies up to restore the max-heap property.

```c
bool heap_remove(struct Heap *heap, void *out, int (*compare)(void*, void*));
```
Removes the root (maximum) element, copies it into `out`, and heapifies down to restore the max-heap property.

```c
void* heap_peek(struct Heap *heap);
```
Returns a pointer to the root element without removing it.

```c
int heap_size(struct Heap *heap);
```
Returns the current number of elements.

```c
int heap_capacity(struct Heap *heap);
```
Returns the total number of allocated slots.

```c
bool heap_isempty(struct Heap *heap);
```
Returns `true` if the heap has no elements.

```c
void heap_clear(struct Heap *heap);
```
Sets length to 0 without freeing memory.

```c
void heap_print(struct Heap *heap, void (*print_fn)(void*));
```
Prints the heap in a tree-like structure using the provided print function.

```c
void heap_debug(struct Heap *heap, void (*print_fn)(void*));
```
Prints all elements in raw array order with no tree visualization.

```c
void heap_discard(struct Heap *heap);
```
Frees all memory associated with the heap.