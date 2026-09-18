// memory_pool.h
// Header for the generic memory pool implementation.
// Brendan Dileo - 2026

#ifndef MEMORY_POOL_H
#define MEMORY_POOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Total bytes for nblocks blocks: each block carries a header plus bsize usable bytes.
#define MEMORY_SIZE(bsize, nblocks) (((bsize) + sizeof(struct MemoryBlockHeader)) * (nblocks))

// Header prefixed to every block. While a block is free, next links it into the
// pool's free list; while it is handed out, the bytes after the header are the
// caller's to use.
struct MemoryBlockHeader {
    struct MemoryBlockHeader *next;
};

// Fixed-size block allocator over one pre-allocated buffer.
struct MemoryPool {
    char *memory;                           // the single backing allocation
    struct MemoryBlockHeader *first_free;   // head of the free list
    int num_blocks;
    int num_free_blocks;
    size_t block_size;                         // usable bytes per block, excluding the header
};

// Allocates a pool of num_blocks blocks, each with block_size usable bytes.
// Caller frees it with mp_discard. Returns NULL on allocation failure.
struct MemoryPool *mp_create(int num_blocks, size_t block_size);
// Returns a pointer to a free block's usable region, or NULL if the pool is
// exhausted. The memory belongs to the pool; return it with mp_free, never free().
void *mp_alloc(struct MemoryPool *pool);
// Returns a block obtained from mp_alloc to the free list. ptr must be a live
// pointer from this pool.
void mp_free(struct MemoryPool *pool, void *ptr);
// Prints the free-block count and the address of each free block.
void mp_print(const struct MemoryPool *pool);
// Frees the backing buffer and the pool struct.
void mp_discard(struct MemoryPool *pool);

#endif
