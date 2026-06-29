/**
 * memory_pool.h
 * Header for the generic memory pool implementation.
 * Brendan Dileo - 2026
 */

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_SIZE(bsize, nblocks) ((bsize) + sizeof(struct MemoryBlockHeader)) * (nblocks)

/**
 * Represents the header metadata stored at the start of each memory block.
 * Blocks are linked together via the next pointer to track free blocks.
 */
struct MemoryBlockHeader {
    struct MemoryBlockHeader *next;
};

/**
 * Represents a fixed-size memory pool.
 * Manages a pre-allocated buffer split into equal-sized blocks.
 */
struct MemoryPool {
    char *memory;
    struct MemoryBlockHeader *first_free;
    int num_blocks;
    int num_free_blocks;
    int block_size;
};

struct MemoryPool *mp_create(int num_blocks, int block_size);
void *mp_alloc(struct MemoryPool *pool);
void mp_free(struct MemoryPool *pool, void *ptr);
void mp_print(struct MemoryPool *pool);
void mp_discard(struct MemoryPool *pool);

#endif