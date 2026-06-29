#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "memory_pool.h"

void mp_create(struct MemoryPool *pool) {
    memset(pool->memory, 0, MEMORY_SIZE(pool->block_size, pool->num_blocks));
    pool->first_free = (struct MemoryBlockHeader*) pool->memory;

    struct MemoryBlockHeader* current_block = pool->first_free;
    for (int i = 0; i < pool->num_blocks - 1; i++) {
        current_block->next = (struct MemoryBlockHeader *)((char *)(current_block + 1) + pool->block_size);
        current_block = current_block->next;
        pool->num_free_blocks++;
    }

    current_block->next = NULL;
    pool->num_free_blocks++;
}

void *mp_alloc(struct MemoryPool *pool) { 
    void *data = NULL;

    if (pool->num_free_blocks > 0) {
        data = (void *)((char *) pool->first_free + sizeof(struct MemoryBlockHeader));
        pool->first_free = pool->first_free->next;
        pool->num_free_blocks--;
    }
    return data;
}

void mp_free(struct MemoryPool *pool, void *ptr) { 
    if (pool->num_free_blocks < pool->num_blocks) {
        struct MemoryBlockHeader *block = (struct MemoryBlockHeader *)((char *) ptr - sizeof(struct MemoryBlockHeader));
        block->next = pool->first_free;
        pool->first_free = block;
        pool->num_free_blocks++;
    }
}

void mp_stats(struct MemoryPool *pool) {
    printf("Number of free blocks: %d\n", pool->num_free_blocks);

    struct MemoryBlockHeader *block = pool->first_free;
    while (block != NULL) {
        printf("%p\n", block);
        block = block->next;
    }
}
