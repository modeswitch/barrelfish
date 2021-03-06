/**
 * \file
 * \brief Architecture specific kernel page table definitions
 */

/*
 * Copyright (c) 2010, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef KERNEL_ARCH_X86_32_PAGING_H
#define KERNEL_ARCH_X86_32_PAGING_H

#include <target/x86_32/paging_kernel_target.h>
#include <paging_kernel_helper.h>

#if defined(CONFIG_PAE) || defined(CONFIG_PSE)
/** Physical memory page size is 2 MBytes */
#       define X86_32_MEM_PAGE_SIZE           X86_32_LARGE_PAGE_SIZE
#else
/** Physical memory page size is 4 KBytes */
#       define X86_32_MEM_PAGE_SIZE           X86_32_BASE_PAGE_SIZE

#       define MEM_PTABLE_SIZE                X86_32_PTABLE_ENTRIES(X86_32_PADDR_SPACE_LIMIT)
#endif

/** Mask for physical memory page */
#define X86_32_MEM_PAGE_MASK           (X86_32_MEM_PAGE_SIZE - 1)

#ifdef CONFIG_PAE

/**
 * Resolves to required number of entries in page directory to map 'limit'
 * number of bytes.
 */
#       define X86_32_PDIR_ENTRIES(limit)    (X86_32_PDPTE_BASE((limit) - 1) + 1)

/**
 * Resolves to required number of entries in page table to map 'limit' number
 * of bytes.
 */
#       define X86_32_PTABLE_ENTRIES(limit)  (X86_32_PDIR_BASE((limit) - 1) + 1)

#else

/**
 * Resolves to required number of entries in page directory to map 'limit'
 * number of bytes.
 */
#       define X86_32_PDIR_ENTRIES(limit)      1

/**
 * Resolves to required number of entries in page table to map 'limit' number
 * of bytes.
 */
#       define X86_32_PTABLE_ENTRIES(limit)  (X86_32_PDIR_BASE((limit) - 1) + 1)

#endif

/**
 * \brief Switch context.
 *
 * Assigns given physical base address to the CR3 register,
 * effectively switching context to new address space. Be
 * cautious that you only switch to "good" page tables.
 *
 * \param addr  Physical base address of page table.
 */
static void inline paging_context_switch(lpaddr_t addr)
{
    paging_x86_32_context_switch(addr);
}

static lvaddr_t inline paging_map_device(lpaddr_t base, size_t size)
{
    return paging_x86_32_map_device(base, size);
}

#endif // KERNEL_ARCH_X86_32_PAGING_H
