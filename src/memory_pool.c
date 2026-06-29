/**
 * memory_pool.c
 * Implementation of a fixed-size memory pool allocator backed by a free list.
 * Brendan Dileo - 2026
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "memory_pool.h"

/**
 * Creates a MemoryPool backed by a single contiguous memory region.
 * Initializes metadata for fixed-size block allocation.
 */
struct MemoryPool *mp_create(int num_blocks, int block_size) {
    struct MemoryPool *pool = malloc(sizeof(struct MemoryPool));
    if (pool == NULL) return NULL;

    pool->memory = malloc(MEMORY_SIZE(block_size, num_blocks));
    if (pool->memory == NULL) {
        free(pool);
        return NULL;
    }

    pool->num_blocks = num_blocks;
    pool->block_size = block_size;
    pool->num_free_blocks = num_blocks;

    memset(pool->memory, 0, MEMORY_SIZE(pool->block_size, pool->num_blocks));
    pool->first_free = (struct MemoryBlockHeader*) pool->memory;

    struct MemoryBlockHeader *current_block = pool->first_free;
    for (int i = 0; i < pool->num_blocks - 1; i++) {
        current_block->next = (struct MemoryBlockHeader *)((char *)(current_block + 1) + pool->block_size);
        current_block = current_block->next;
    }

    current_block->next = NULL;
    return pool;
}

/**
 * Allocates a block from the memory pool and returns a pointer
 * to its usable data region.
 */
void *mp_alloc(struct MemoryPool *pool) {
    void *data = NULL;

    if (pool->num_free_blocks > 0) {
        data = (void *)((char *) pool->first_free + sizeof(struct MemoryBlockHeader));
        pool->first_free = pool->first_free->next;
        pool->num_free_blocks--;
    }
    return data;
}

/**
 * Frees a block of memory and reinserts it into the pool's free list.
 */
void mp_free(struct MemoryPool *pool, void *ptr) {
    if (pool->num_free_blocks < pool->num_blocks) {

        // Convert user pointer back to block header
        struct MemoryBlockHeader *block = (struct MemoryBlockHeader *)((char *) ptr - sizeof(struct MemoryBlockHeader));
        block->next = pool->first_free;
        pool->first_free = block;
        pool->num_free_blocks++;
    }
}

/**
 * Prints the addresses of all free memory blocks in the pool.
 */
void mp_print(struct MemoryPool *pool) {
    printf("Number of free blocks: %d\n", pool->num_free_blocks);

    struct MemoryBlockHeader *block = pool->first_free;
    while (block != NULL) {
        printf("%p\n", block);
        block = block->next;
    }
}

/**
 * Frees the memory pool and all memory it allocated.
 */
void mp_discard(struct MemoryPool *pool) {
    if (pool != NULL) {
        free(pool->memory);
        free(pool);
    }
}
