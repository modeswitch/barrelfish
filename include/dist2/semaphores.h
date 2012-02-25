/**
 * \file
 * \brief Header file for the dist2 semaphores API.
 *
 * This API was written to replace the semaphore API
 * in chips in order to support posixcompat.
 */

/*
 * Copyright (c) 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef DIST2_SEMAPHORES_H_
#define DIST2_SEMAPHORES_H_

errval_t dist_sem_new(uint32_t*, size_t);
errval_t dist_sem_post(uint32_t);
errval_t dist_sem_wait(uint32_t);
errval_t dist_sem_trywait(uint32_t);

#endif /* DIST2_SEMAPHORES_H_ */
