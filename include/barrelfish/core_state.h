/**
 * \file
 * \brief
 */

/*
 * Copyright (c) 2008, 2009, 2010, 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef LIBBARRELFISH_CORESTATE_H
#define LIBBARRELFISH_CORESTATE_H

#include <k_r_malloc.h>
#include <barrelfish/waitset.h>

/* DELETEME! I can't find anything that uses this -AB 20120110 */
#if 0
/*
 * XXX: This currently very small (4096 frames tracked, using 384KB
 * memory). Obviously making it much bigger results in a huge .bss
 * segment. Unfortunately, making this a dynamic data structure turns
 * out to be harder than one might expect, as this is in the critical
 * path of memory allocation, we cannot call into slab_alloc() to get
 * more memory. A cspace-based solution, where RAM caps are stored at
 * a resolvable address from their corresponding frame, also doesn't
 * work, as the interface is designed such that the frame cap slot is
 * given by the user, while the RAM cap slot is determined by
 * ram_alloc().
 */
#define MAX_TRACK_FRAMES        4096

struct captrack {
    struct capref       framecap;
    struct capref       ramcap;
};
#endif // 0 DELETEME

struct morecore_state {
    struct thread_mutex mutex;
    Header header_base;
    Header *header_freep;
    struct vspace_mmu_aware mmu_state;
#if 0 // DELETEME
    struct captrack track_frames[MAX_TRACK_FRAMES];
#endif // 0 DELETEME
};

struct ram_alloc_state {
    bool mem_connect_done;
    errval_t mem_connect_err;
    struct thread_mutex ram_alloc_lock;
    ram_alloc_func_t ram_alloc_func;
    uint64_t default_minbase;
    uint64_t default_maxlimit;
    int base_capnum;
};

struct skb_state {
    bool request_done;
    struct skb_rpc_client *skb;
};

struct slot_alloc_state {
    struct multi_slot_allocator defca;

    struct single_slot_allocator top;
    struct slot_allocator_list head;
    struct slot_allocator_list reserve;

    struct cnode_meta top_buf[SLOT_ALLOC_CNODE_SLOTS / 2];
    struct cnode_meta head_buf[SLOT_ALLOC_CNODE_SLOTS / 2];
    struct cnode_meta reserve_buf[SLOT_ALLOC_CNODE_SLOTS / 2];

    struct single_slot_allocator rootca;
    struct cnode_meta root_buf[DEFAULT_CNODE_SLOTS / 2];
};

struct terminal_state;
struct octopus_rpc_client;
struct domain_state;
struct spawn_state;
struct monitor_binding;
struct mem_rpc_client;
struct spawn_rpc_client;

struct core_state_generic {
    struct waitset default_waitset;
    struct monitor_binding *monitor_binding;
    struct monitor_blocking_rpc_client *monitor_blocking_rpc_client;
    struct mem_rpc_client *mem_st;
    struct morecore_state morecore_state;
    struct ram_alloc_state ram_alloc_state;
    struct octopus_rpc_client *nameservice_rpc_client;
    struct spawn_rpc_client *spawn_rpc_clients[MAX_CPUS];
    struct terminal_state *terminal_state;
    struct domain_state *domain_state;
    struct spawn_state *spawn_state;
    struct slot_alloc_state slot_alloc_state;
    struct skb_state skb_state;
};

#endif
