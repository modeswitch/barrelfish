/*
 * Copyright (c) 2011, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int remove(const char *filename)
{
    int ret;

    // Try unlink first
    ret = unlink(filename);

    // If it was a directory, try rmdir() next
    if(ret == -1 && errno == EPERM) {
        return rmdir(filename);
    }

    return ret;
}
