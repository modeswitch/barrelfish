/*
 * Copyright (c) 2007, 2008, 2009, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef NETD_DEBUG_H_
#define NETD_DEBUG_H_


/*****************************************************************
 * Debug printer:
 *****************************************************************/
//#define NETD_DEBUG(x...) printf("netd: " x)
//#define NETD_SERVICE_DEBUG 1
#if defined(NETD_SERVICE_DEBUG) || defined(GLOBAL_DEBUG)
#define NETD_DEBUG(x...) printf("netd: " x)
#else
#define NETD_DEBUG(x...) ((void)0)
#endif                          // defined(NETD_SERVICE_DEBUG) || defined(GLOBAL_DEBUG)


#endif                          // E1000_DEBUG_H_
