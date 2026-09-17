// memory_pool.c
// Implementation of a fixed-size memory pool allocator backed by a free list.
// Brendan Dileo - 2026

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "memory_pool.h"

struct MemoryPool *mp_create(int num_blocks, size_t block_size) {
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

    // Thread every block onto the free list. From one header, (current_block + 1)
    // steps past the header and + block_size steps past the usable region, landing
    // on the next block's header.
    struct MemoryBlockHeader *current_block = pool->first_free;
    for (int i = 0; i < pool->num_blocks - 1; i++) {
        current_block->next = (struct MemoryBlockHeader *)((char *)(current_block + 1) + pool->block_size);
        current_block = current_block->next;
    }

    current_block->next = NULL;
    return pool;
}

void *mp_alloc(struct MemoryPool *pool) {
    void *data = NULL;

    if (pool->num_free_blocks > 0) {
        // Hand back the region just past the block's header.
        data = (void *)((char *) pool->first_free + sizeof(struct MemoryBlockHeader));
        pool->first_free = pool->first_free->next;
        pool->num_free_blocks--;
    }
    return data;
}

void mp_free(struct MemoryPool *pool, void *ptr) {
    if (pool->num_free_blocks < pool->num_blocks) {
        // Step back from the user pointer to its header, then push onto the free list.
        struct MemoryBlockHeader *block = (struct MemoryBlockHeader *)((char *) ptr - sizeof(struct MemoryBlockHeader));
        block->next = pool->first_free;
        pool->first_free = block;
        pool->num_free_blocks++;
    }
}

void mp_print(struct MemoryPool *pool) {
    printf("Number of free blocks: %d\n", pool->num_free_blocks);

    struct MemoryBlockHeader *block = pool->first_free;
    while (block != NULL) {
        printf("%p\n", block);
        block = block->next;
    }
}

void mp_discard(struct MemoryPool *pool) {
    if (pool != NULL) {
        free(pool->memory);
        free(pool);
    }
}
