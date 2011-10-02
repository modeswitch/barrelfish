/**
 * \file
 * \brief Buffer memory for LWIP using caps
 *
 * This file provides caps for the buffers in LWIP. Needed because the network_phase
 * stack should pass a cap to a buffer to the network device driver.
 */

/*
 * Copyright (c) 2007, 2008, 2009, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef MEM_BARRELFISH_H_
#define MEM_BARRELFISH_H_

uint8_t *mem_barrelfish_alloc_and_register(uint8_t binding_index,
                                           uint32_t size);
struct buffer_desc *mem_barrelfish_get_buffer_desc(void *p);

void mem_barrelfish_pbuf_init(void);
struct pbuf *mem_barrelfish_get_pbuf(uint64_t pbuf_id);
void mem_barrelfish_replace_pbuf(uint64_t idx);

#endif                          // MEM_BARRELFISH_H_
