/**
 * test_mp.c
 * Test suite for the fixed-size MemoryPool allocator.
 * Brendan Dileo - 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "test_utils.h"
#include "memory_pool.h"

#define NUM_OF_BLOCKS 8
#define BLOCK_SIZE 16

void test_mp_create(void);
void test_mp_alloc(void);
void test_mp_free(void);

int main(void) {
    TEST(test_mp_create);
    TEST(test_mp_alloc);
    TEST(test_mp_free);
    return 0;
}

void test_mp_create(void) {
    struct MemoryPool *pool = mp_create(NUM_OF_BLOCKS, BLOCK_SIZE);
    ASSERT_NOT_NULL(pool);
    ASSERT_NOT_NULL(pool->memory);

    ASSERT_EQ(pool->num_blocks, NUM_OF_BLOCKS);
    ASSERT_EQ(pool->num_free_blocks, NUM_OF_BLOCKS);
    ASSERT_EQ(pool->block_size, BLOCK_SIZE);

    mp_discard(pool);
    pool = NULL;
}

void test_mp_alloc(void) {
    struct MemoryPool *pool = mp_create(NUM_OF_BLOCKS, BLOCK_SIZE);
    ASSERT_NOT_NULL(pool);

    void *block_one = mp_alloc(pool);

    ASSERT_NOT_NULL(block_one);
    ASSERT_EQ(pool->num_free_blocks, NUM_OF_BLOCKS - 1);

    mp_discard(pool);
    pool = NULL;
}

void test_mp_free(void) {
    struct MemoryPool *pool = mp_create(NUM_OF_BLOCKS, BLOCK_SIZE);
    ASSERT_NOT_NULL(pool);

    void *block_one = mp_alloc(pool);
    ASSERT_NOT_NULL(block_one);
    ASSERT_EQ(pool->num_free_blocks, NUM_OF_BLOCKS - 1);

    mp_free(pool, block_one);
    ASSERT_EQ(pool->num_free_blocks, NUM_OF_BLOCKS);

    mp_discard(pool);
    pool = NULL;
}
