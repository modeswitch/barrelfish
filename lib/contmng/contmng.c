/**
 * \file
 * \brief e1000 continuation management
 *
 * This file provides a generic way of managing continuation for messages
 * of different types
 */

/*
 * Copyright (c) 2007, 2008, 2009, 2010, ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef CONTMNG_C_
#define CONTMNG_C_

#include <string.h>
#include <barrelfish/barrelfish.h>
//#include <if/ether_defs.h>

#include <contmng/contmng.h>

/* QUEUE_DEBUG enables the debug statements */
//#define QUEUE_DEBUG 1

//****************************************************************************
/************** Generic continuation queue implementation *******************/
/* WARN: use only when your responses contains only integers */

static void cont_queue_send_next_message(struct cont_queue *q);

static void qprintf (struct cont_queue *q, char *msg)
{

#ifdef QUEUE_DEBUG
    if (q->name[0]) { /* show debug msg, only if queue name is present */
        printf("CQ: [%s] %s [%d] [%d] qqqqqq\n",
                    q->name, msg, q->head, q->tail);
    }
#endif /* QUEUE_DEBUG */

}

/* allocates the memory for continuation queue 
    It includes the memory for MAX_QUEUE_SIZE of elements also */
struct cont_queue *create_cont_q(char *name)
{
    struct cont_queue *ptr = NULL;
    ptr = (struct cont_queue *) malloc(sizeof(struct cont_queue));
    if (ptr == NULL) {
        printf("ERROR: malloc failed in create_cont_q\n");
        abort();
        /* FIXME: introduce new error and return the error */
    }
    strncpy(ptr->name, name, 63);
    return ptr;
}/* end function: create_cont_q */


/* Adds element to the queue */
void enqueue_cont_q(struct cont_queue *q, struct q_entry *entry)
{

    if (((q->head + 1) % MAX_QUEUE_SIZE) == q->tail)
    {
        printf("ERROR: Queue [%s] is full\n", q->name);
        abort();
    }

    /* Copying the structure */
    q->qelist[q->head].binding_ptr = entry->binding_ptr;
    q->qelist[q->head].cap = entry->cap;
    q->qelist[q->head].handler = entry->handler;
    q->qelist[q->head].history = 0;   // reset the history
    for(int i = 0; i < MAX_PARAMS; ++i) {
    	q->qelist[q->head].plist[i] = entry->plist[i];
    }

    q->head = (q->head + 1) % MAX_QUEUE_SIZE;
    qprintf(q, "enqueued");

    // If no continuations are running, then execute this one directly
    if(q->running == 0){
        q->running = 1;
        q->qelist[q->head].history += 500; // For debugging: mark to trace the history
        q->qelist[q->tail].history += 30; // For debugging: mark to trace the history
        qprintf(q, "directly-sending");
        cont_queue_send_next_message(q);
    }
    //otherwise continuation function will trigger sending next queue element
} /* end function: enqueue_cont_q */


/* called from continuation registered with flounder 
    WARN: should not be called directly */
void cont_queue_callback(void *arg)
{
    struct cont_queue *q = (struct cont_queue *)arg;

    q->tail = (q->tail + 1) % MAX_QUEUE_SIZE;
    qprintf(q, "from-continuation");
    q->qelist[q->tail].history += 100; // For debugging: mark to trace the history
    cont_queue_send_next_message(q);
} /* end function: cont_queue_callback */


/* Sends the top of queue msg 
    NOTE: this function does not increment the tail.  It calls handler,
        which registers "cont_queue_callback" as callback with flounder,
        and that callback function increments the tail!!!
            complicated? huh.. :-P */
void cont_queue_send_next_message(struct cont_queue *q)
{
    qprintf(q, "sending-msg");

    if(q->head == q->tail){
        qprintf(q, "Queue-empty-Recursion-End!!");
        q->qelist[q->tail].history += 1;
        q->running = 0;
        return;
    }

    errval_t err = q->qelist[q->tail].handler(q->qelist[q->tail]);
    q->qelist[q->tail].history += 4;
    if (err_is_fail(err)) {
        if (err == FLOUNDER_ERR_TX_BUSY ) {
            qprintf(q, "sending:FLO-BUSY");
            q->qelist[q->tail].history += 2;
        } else {
            qprintf(q, "sending:FLO FAIL");
            q->qelist[q->tail].history += 3;
            USER_PANIC_ERR(err, "cont_queue_send_next_message ");
        }
    }
} /* end function: cont_queue_send_next_message */

// Function to show the content of the queue.
// Note: It is to be used only for debug purposes.
void cont_queue_show_queue(struct cont_queue *q)
{
    int i = 0;
    int idx = 0;
    int len = 0;
    len = q->head - q->tail;
    printf("Showing the cont queue status for queue[%s]\n", q->name);
    printf("queue len [%d]==> head [%d] - tail [%d]\n", len, q->head, q->tail);
    idx = q->tail;
    while (idx != q->head){
        printf("elem %d: [%s], state %u\n", idx, q->qelist[idx].fname,
                q->qelist[idx].history);
        idx = (idx + 1) % MAX_QUEUE_SIZE;
    }

    printf("Showing elements which are already sent!!\n");
    idx = q->tail;
    for (i = 0; i < 10; ++i){
        idx = (idx - 1);
        if (idx < 0) {
            idx = MAX_QUEUE_SIZE - 1;
        }
        printf("elem %d: [%s], state %d\n", idx, q->qelist[idx].fname,
                q->qelist[idx].history);
    }
} // end function: cont_queue_show_queue


/* Following function has nothing to do with cont_queue_management,
 * and is to be used for debugging.  Ideally this function should not exist. */
void show_binary_blob (void *data, int len)
{
	printf("\nBlob_%d[", len);
	uint8_t *ptr = data;
	for (int i = 0 ; i < len; ++i){
		printf("0x%x,", ptr[i]);
	}
	printf("]\n");
}

#endif // CONTMNG_C_
