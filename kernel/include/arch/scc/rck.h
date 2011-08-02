/*
 * Copyright (c) 2007, 2008, 2010, 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef RCK_H
#define RCK_H

#include <kernel_multiboot.h>
#include <target/x86/barrelfish_kpi/coredata_target.h>

void rck_init(void);
uint8_t rck_get_coreid(void);
void rck_send_notification(uint8_t dest, uintptr_t chanid);
void rck_handle_notification(void);
errval_t rck_register_notification(caddr_t cap, int chanid);
errval_t rck_delete_notification(int chanid);
int rck_start_core(uint8_t coreid, genvaddr_t entry, struct x86_core_data *core_data);
void rck_reset_lint1(void);
errval_t rck_get_route(genpaddr_t base, size_t size, uint8_t *route,
                       uint8_t *subdest, uint16_t *addrbits);

#endif
