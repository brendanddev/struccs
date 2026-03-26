# Project
PROJECT = struccs

# Compiler and flags
CC = clang
CFLAGS = -Wall -Wextra -I include

# Directories
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Static library
LIB = $(BUILD_DIR)/lib$(PROJECT).a

# Default target
all: $(BUILD_DIR) $(LIB)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build static library
$(LIB): $(SRCS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $(SRCS)
	mv *.o $(BUILD_DIR)/
	ar rcs $(LIB) $(BUILD_DIR)/*.o

# Test targets
test_bt: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/binary_tree.c $(TEST_DIR)/test_bt.c -o $(BUILD_DIR)/test_bt
	./$(BUILD_DIR)/test_bt

test_bst: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/binarysearch_tree.c $(TEST_DIR)/test_bst.c -o $(BUILD_DIR)/test_bst
	./$(BUILD_DIR)/test_bst

test_ga: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/generic_array.c $(TEST_DIR)/test_ga.c -o $(BUILD_DIR)/test_ga
	./$(BUILD_DIR)/test_ga

test_ll: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/linked_list.c $(TEST_DIR)/test_ll.c -o $(BUILD_DIR)/test_ll
	./$(BUILD_DIR)/test_ll

test_ht: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/hash_table.c $(TEST_DIR)/test_ht.c -o $(BUILD_DIR)/test_ht
	./$(BUILD_DIR)/test_ht

test_stack: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/stack.c $(TEST_DIR)/test_stack.c -o $(BUILD_DIR)/test_stack
	./$(BUILD_DIR)/test_stack

test_queue: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/queue.c $(TEST_DIR)/test_queue.c -o $(BUILD_DIR)/test_queue
	./$(BUILD_DIR)/test_queue

test_heap: $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SRC_DIR)/heap.c $(TEST_DIR)/test_heap.c -o $(BUILD_DIR)/test_heap
	./$(BUILD_DIR)/test_heap

# Run all tests
test_all: test_bt test_bst test_ga test_ll test_ht test_stack test_queue test_heap

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR)