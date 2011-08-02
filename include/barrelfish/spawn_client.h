/*
 * Copyright (c) 2010, 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef BARRELFISH_SPAWN_CLIENT_H
#define BARRELFISH_SPAWN_CLIENT_H

#include <barrelfish_kpi/types.h>

/// Flags for spawning a program
typedef enum spawn_flags {
    SPAWN_NEW_DOMAIN    = 1 << 0, ///< allocate a new domain ID
} spawn_flags_t;

#define SPAWN_FLAGS_DEFAULT (0)

/* XXX: utility function that doesn't really belong here */
const char *cpu_type_to_archstr(enum cpu_type cpu_type);

errval_t spawn_program_with_fdcap(coreid_t coreid, const char *path,
                       char *const argv[], char *const envp[],
                       struct capref fdcap,
                       spawn_flags_t flags, domainid_t *ret_domainid);
errval_t spawn_program(coreid_t coreid, const char *path,
                       char *const argv[], char *const envp[],
                       spawn_flags_t flags, domainid_t *ret_domainid);
errval_t spawn_program_on_all_cores(bool same_core, const char *path,
                                    char *const argv[], char *const envp[],
                                    spawn_flags_t flags, domainid_t *ret_domainid);
errval_t spawn_kill(domainid_t domainid);
errval_t spawn_exit(uint8_t exitcode);
errval_t spawn_wait(domainid_t domainid, uint8_t *exitcode, bool nohang);
errval_t spawn_rpc_client(coreid_t coreid, struct spawn_rpc_client **ret_client);

#endif // BARRELFISH_SPAWN_CLIENT_H
