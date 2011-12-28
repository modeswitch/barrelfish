/**
 * \file
 * \brief Buffer cache daemon.
 */

/*
 * Copyright (c) 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#include <stdio.h>
#include <barrelfish/barrelfish.h>
#ifdef __scc__
#       define ENABLE_FEIGN_FRAME_CAP
#       include <barrelfish/sys_debug.h>
#endif
#include <barrelfish/waitset.h>
#define WITH_BUFFER_CACHE
#include <vfs/vfs.h>
#ifdef __scc__
#       include <barrelfish_kpi/shared_mem_arch.h>
#endif

#include "bcached.h"
#include <hashtable/hashtable.h>

//#ifndef CONFIG_QEMU_NETWORK
#if 1
#       define CACHE_SIZE      (1U << 28)      // 256MB
#else
#       define CACHE_SIZE      (1U << 22)      // 4MB
#endif
#define NUM_BLOCKS      (CACHE_SIZE / BUFFER_CACHE_BLOCK_SIZE)

struct lru_queue {
    struct lru_queue *prev, *next;
    uintptr_t index, block_length;
    bool inuse;
    char *key;
    size_t key_len;
};

struct capref cache_memory;
size_t cache_size, block_size = BUFFER_CACHE_BLOCK_SIZE;
void *cache_pool;
static struct hashtable *cache_hash = NULL;
static struct lru_queue *lru_start, *lru_end, *lru;
static size_t hits = 0, misses = 0, allocations = 0, evictions = 0;

void print_stats(void)
{
    printf("cache statistics\n"
           "----------------\n"
           "cache size               = %u blocks * %u KB = %u MB\n"
           "hits                     = %lu\n"
           "misses                   = %lu\n"
           "allocations              = %lu / %u blocks (%lu%% utilization)\n"
           "evictions (replacements) = %lu blocks\n",
           NUM_BLOCKS, BUFFER_CACHE_BLOCK_SIZE / 1024, CACHE_SIZE / 1024 / 1024,
           hits, misses, allocations, NUM_BLOCKS,
           (allocations * 100) / NUM_BLOCKS, evictions);
}

static struct lru_queue *lru_use(uintptr_t index)
{
    assert(index < NUM_BLOCKS);
    struct lru_queue *e = &lru[index];

    // Make it new head of the queue
    if(e->prev != NULL) {
        struct lru_queue *oldnext = e->next;
        e->prev->next = e->next;
        if(oldnext != NULL) {
            oldnext->prev = e->prev;
        } else {
            // This was the tail of the queue, we need to designate a new tail
            assert(e == lru_end);
            lru_end = e->prev;
        }
        e->prev = NULL;
        e->next = lru_start;
        lru_start->prev = e;
        lru_start = e;
    } else {
        assert(e == lru_start);
    }

    return lru_start;
}

static struct lru_queue *lru_get(void)
{
    assert(lru_end != NULL);
    return lru_use(lru_end->index);
}

static void lru_init(void)
{
    // Initialize LRU queue
    lru_start = lru = calloc(NUM_BLOCKS, sizeof(struct lru_queue));
    assert(lru_start != NULL);
    lru_end = lru_start + NUM_BLOCKS - 1;
    for(struct lru_queue *p = lru_start; p <= lru_end; p++) {
        p->prev = p - 1;
        p->next = p + 1;
        p->index = p - lru_start;
    }
    lru_start->prev = lru_end->next = NULL;
}

bool cache_lookup(char *key, size_t key_len, uintptr_t *index,
                  uintptr_t *length)
{
    ENTRY_TYPE et;
    void *val;

    et = cache_hash->d.get(&cache_hash->d, key, key_len, &val);
    assert(et == TYPE_WORD || et == 0);

    if(et == TYPE_WORD) {
        *index = (uintptr_t)val;
        struct lru_queue *l = lru_use(*index);
        *length = l->block_length;

        hits++;
    } else {
        misses++;
    }

    // Convert to byte offset from start of cache
    *index *= BUFFER_CACHE_BLOCK_SIZE;

    /* printf("cache_lookup(\"%s\", %" PRIuPTR ") = %s\n", key, *index, */
    /*        et == TYPE_WORD ? "true" : "false"); */

    return et == TYPE_WORD ? true : false;
}

uintptr_t cache_allocate(char *key, size_t key_len)
{
    struct lru_queue *e = lru_get();

    if(e->inuse) {
        // Cache is write-through, so we just have to delete the old entry
        int r = cache_hash->d.remove(&cache_hash->d, e->key, e->key_len);
        assert(r == 0);
        free(e->key);

#ifdef WITH_WRITE_BACK_CACHE
        assert(!"NYI");
#endif

        evictions++;
    } else {
        allocations++;
    }

    e->inuse = true;
    e->key = key;
    e->key_len = key_len;
    e->block_length = 0;

    int r = cache_hash->d.put_word(&cache_hash->d, key, key_len, e->index);
    assert(r == 0);

    // Convert to byte offset from start of cache
    return e->index * BUFFER_CACHE_BLOCK_SIZE;
}

void cache_update(uintptr_t index, uintptr_t length)
{
    assert(index % BUFFER_CACHE_BLOCK_SIZE == 0);
    index /= BUFFER_CACHE_BLOCK_SIZE;
    struct lru_queue *l = lru_use(index);
    l->block_length = length;
}

static errval_t create_cache_mem(size_t size)
{
    // Create a Frame Capability
#ifndef __scc__
    errval_t r = frame_alloc(&cache_memory, size, &cache_size);
#else
    errval_t r = slot_alloc(&cache_memory);
    assert(err_is_ok(r));
    r = sys_debug_feign_frame_cap(cache_memory, EXTRA_SHARED_MEM_MIN, 28);
    cache_size = size;
#endif
    if (err_is_fail(r)) {
        return err_push(r, LIB_ERR_FRAME_ALLOC);
    }
    assert(cache_size >= size);

    // Map the frame in local memory
#ifdef __scc__
    r = vspace_map_one_frame_attr(&cache_pool, cache_size, cache_memory,
                                  VREGION_FLAGS_READ_WRITE_MPB, NULL, NULL);
#else
    r = vspace_map_one_frame(&cache_pool, cache_size, cache_memory, NULL, NULL);
#endif
    if (err_is_fail(r)) {
        cap_destroy(cache_memory);
        return err_push(r, LIB_ERR_VSPACE_MAP);
    }
    assert(cache_pool != NULL);

    return SYS_ERR_OK;
}

#include <dmalloc/dmalloc.h>

typedef void *(*alt_malloc_t)(size_t bytes);
extern alt_malloc_t alt_malloc;

typedef void (*alt_free_t)(void *p);
extern alt_free_t alt_free;

typedef void *(*alt_realloc_t)(void *p, size_t bytes);
extern alt_realloc_t alt_realloc;

static void init_dmalloc(void)
{
    alt_malloc = &dlmalloc;
    alt_free = &dlfree;
    alt_realloc = &dlrealloc;
}

int main(int argc, char *argv[])
{
    errval_t err;

    init_dmalloc();

    err = create_cache_mem(CACHE_SIZE);
    if(err_is_fail(err)) {
        USER_PANIC_ERR(err, "create_cache_mem");
    }

    cache_hash = create_hashtable2(2 * NUM_BLOCKS, 75);
    assert(cache_hash != NULL);

    lru_init();

    err = start_service();
    assert(err_is_ok(err));

    for(;;) {
        err = event_dispatch(get_default_waitset());
        if(err_is_fail(err)) {
            USER_PANIC_ERR(err, "event_dispatch");
        }
    }

    return 0;
}
