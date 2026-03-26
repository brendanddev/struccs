# Performance Characteristics

Time complexity reference for all operations across each structure.

---

## Generic Array

| Operation | Time Complexity | Notes |
|---|---|---|
| `ga_append` | **O(1)** amortized | Adds to end, occasionally triggers resize |
| `ga_add` | **O(n)** | Inserts at index, shifts subsequent elements right |
| `ga_get` | **O(1)** | Direct access by index |
| `ga_set` | **O(1)** | Overwrites element at index |
| `ga_find` | **O(n)** | Linear search using supplied comparator |
| `ga_contains` | **O(n)** | Checks all elements using comparator |
| `ga_remove_last` | **O(1)** amortized | May trigger shrink when underutilized |
| `ga_remove_at` | **O(n)** | Removes at index, shifts remaining elements left |
| `ga_clear` | **O(1)** | Sets length to 0 without freeing memory |
| `ga_size` | **O(1)** | Returns current number of elements |
| `ga_capacity` | **O(1)** | Returns total allocated slots |
| `ga_usage` | **O(1)** | Computes fill ratio as percentage |
| `ga_discard` | **O(1)** | Frees allocated memory for array and struct |
| `ga_sort` | **O(n²)** | Bubble sort; comparator determines ordering |
| `ga_reverse` | **O(n)** | Swaps front/back elements in place |
| `ga_copy` | **O(n)** | Deep copy of struct and all elements |
| `resize` | **O(n)** | Allocates larger block and copies items |
| `shrink` | **O(n)** | Allocates smaller block and copies items |
| `shift_right` | **O(n)** | Moves elements after insertion index one slot right |
| `shift_left` | **O(n)** | Moves elements after deletion index one slot left |
| `swap` | **O(1)** | Exchanges two items using temporary memory |

---

## Linked List

| Operation | Time Complexity | Notes |
|---|---|---|
| `ll_insert` | **O(1)** | Inserts at head |
| `ll_insert_tail` | **O(1)** | Inserts at tail |
| `ll_insert_at` | **O(n)** | Inserts at specific index |
| `ll_remove` | **O(1)** | Removes head node |
| `ll_remove_tail` | **O(1)** | Removes tail node |
| `ll_remove_at` | **O(n)** | Removes node at index |
| `ll_get` | Optimized **O(n)** | Bidirectional traversal to index |
| `ll_set` | Optimized **O(n)** | Bidirectional traversal to update index |
| `ll_find` | **O(n)** | Linear search using comparator |
| `ll_contains` | **O(n)** | Checks existence using comparator |
| `ll_clear` | **O(n)** | Frees all nodes, retains list structure |
| `ll_copy` | **O(n)** | Deep copies entire list and nodes |
| `ll_reverse` | **O(n)** | Reverses order of nodes in place |
| `ll_bsort` | **O(n²)** | Bubble sort; comparator determines ordering |
| `swap_nodes` | **O(1)** | Swaps data between two nodes |
| `ll_size` | **O(1)** | Returns number of nodes |
| `ll_is_empty` | **O(1)** | Checks if list has no nodes |
| `ll_discard_node` | **O(1)** | Frees a single node |
| `ll_discard_all_nodes` | **O(n)** | Frees all nodes, retains list structure |
| `ll_discard` | **O(n)** | Frees all nodes and list structure |

---

## Stack

| Operation | Time Complexity | Notes |
|---|---|---|
| `stack_create` | **O(1)** | Initializes a new empty stack |
| `stack_push` | **O(1)** | Adds element to top |
| `stack_peek` | **O(1)** | Returns top element without removing it |
| `stack_pop` | **O(1)** | Removes and returns top element |
| `stack_clear` | **O(n)** | Removes all elements |
| `stack_is_empty` | **O(1)** | Checks if stack is empty |
| `stack_size` | **O(1)** | Returns number of elements |
| `stack_discard` | **O(n)** | Frees all memory associated with the stack |

---

## Queue

| Operation | Time Complexity | Notes |
|---|---|---|
| `queue_create` | **O(1)** | Initializes a new empty queue |
| `queue_enqueue` | **O(1)** | Adds element to end |
| `queue_peek` | **O(1)** | Returns front element without removing it |
| `queue_dequeue` | **O(1)** | Removes and returns front element |
| `queue_is_empty` | **O(1)** | Checks if queue is empty |
| `queue_length` | **O(1)** | Returns number of elements |
| `queue_clear` | **O(n)** | Removes all elements |
| `queue_discard` | **O(n)** | Frees all memory associated with the queue |

---

## Hash Table

| Operation | Time Complexity | Notes |
|---|---|---|
| `ht_create` | **O(1)** | Initializes a new empty hash table |
| `ht_insert` | **O(1)** amortized | Inserts key/value pair, resizes at load factor 0.75 |
| `ht_remove` | **O(1)** average | Removes key/value pair |
| `ht_get` | **O(1)** average | Retrieves value by key |
| `ht_contains` | **O(1)** average | Checks if key exists |
| `ht_clear` | **O(n)** | Frees all nodes and resets table |
| `ht_is_empty` | **O(1)** | Checks if table is empty |
| `ht_size` | **O(1)** | Returns number of entries |
| `ht_load_factor` | **O(1)** | Returns current load factor |
| `ht_discard` | **O(n)** | Frees all contents of the hash table |

---

## Binary Search Tree

| Operation | Time Complexity | Notes |
|---|---|---|
| `bst_create` | **O(1)** | Initializes a new empty BST |
| `bst_insert` | **O(log n)** average | Recursive insert; O(n) worst case (unbalanced) |
| `bst_remove` | **O(log n)** average | Recursive remove with in-order successor |
| `bst_contains` | **O(log n)** average | Recursive search |
| `bst_search` | **O(log n)** average | Returns pointer to node |
| `bst_min` | **O(log n)** | Traverses to leftmost node |
| `bst_max` | **O(log n)** | Traverses to rightmost node |
| `bst_height` | **O(n)** | Traverses entire tree |
| `bst_inorder` | **O(n)** | Left → Root → Right traversal |
| `bst_preorder` | **O(n)** | Root → Left → Right traversal |
| `bst_postorder` | **O(n)** | Left → Right → Root traversal |
| `bst_size` | **O(1)** | Returns number of nodes |
| `bst_isempty` | **O(1)** | Checks if tree is empty |
| `bst_clear` | **O(n)** | Frees all nodes |
| `bst_discard` | **O(n)** | Frees all nodes and tree structure |