/**
 * \file
 * \brief Header file for ethersrv.h
 */

/*
 * Copyright (c) 2007-11 ETH Zurich.
 * All rights reserved.
 *
 * This file is distributed under the terms in the attached LICENSE file.
 * If you do not find this file, copies can be found by writing to:
 * ETH Zurich D-INFK, Haldeneggsteig 4, CH-8092 Zurich. Attn: Systems Group.
 */

#ifndef ETHERSRV_H
#define ETHERSRV_H

#include <barrelfish/barrelfish.h>
#include <barrelfish/bulk_transfer.h>
#include <contmng/contmng.h>
#include <contmng/netbench.h>
#include <procon/procon.h>
#include <if/ether_defs.h>
#include <barrelfish/net_constants.h>

/*****************************************************************
 * Constants:
 *****************************************************************/

#define MAX_NR_TRANSMIT_PBUFS 80

#define RECEIVE_CONNECTION 0
#define TRANSMIT_CONNECTION 1



/*****************************************************************
 * common data-structures
 *****************************************************************/

#define MAX_PAUSE_BUFFER        10

struct bufdesc {
    char pkt_data[1600];
    size_t pkt_len;
};

struct filter {
    uint64_t filter_id;
    uint64_t filter_type;
    uint8_t *data;
    int32_t len;
    bool paused;
    struct bufdesc pause_buffer[MAX_PAUSE_BUFFER];
    int pause_bufpos;
    struct buffer_descriptor *buffer;
    struct filter *next;
};

struct buffer_descriptor {
    uint64_t buffer_id;
    struct ether_binding *con;
    struct capref cap;
    struct shared_pool_private *spp_prv;
    uint8_t role;
    lpaddr_t pa;
    uint64_t bits;
    void *va;

    uint64_t type;
    void *pbuf_metadata_ds; // FIXME: why is it void *
    void *pbuf_metadata_ds_tx; // FIXME: is it used?. Nope, not used. Remove it
    uint32_t pbuf_head_rx;
    uint32_t pbuf_tail_rx;
    uint32_t pbuf_head_tx;
    uint32_t pbuf_tail_tx;
    struct buffer_descriptor *next;
    struct filter* tx_filters;
};

struct pbuf {
    uint64_t buffer_id;
    uint64_t len;
    uint64_t offset;
    uint64_t client_data;
//    uint64_t spp_index;
//    uint64_t ts;
};


enum pbuf_lifecycle {
    PBUF_REGISTERED,
    PKT_RECEIVED,
    RECV_NOTIFICATION_GENERATED,
    RECV_NOTIFICATION_SENT,
    PKT_ARRIVED_APP, // From here bellow, everything will be in APP
    PKT_REACHED_APP,
    PBUF_REGISTER_STARTED,
    PBUF_REGISTER_GENERATED,
    PBUF_REGISTER_SENT
};
#define MAX_STAT_EVENTS   5   // This is the count of pbuf_lifecycle events

struct pbuf_desc {
    uint64_t buffer_id; // k: we are gonna reference this from now on
    uint64_t pbuf_id;
    uint64_t vaddr; // k: we need virtual memory from now on :)
    uint64_t paddr; // k: we also need to provide this for card for DMA
    uint64_t client_data;
    uint64_t len;
    uint64_t packet_size;
    struct ether_binding *sr;
    bool event_sent; //the interrupt handler has to know wheter the client was
    //already notified about new data in this buffer.
    bool last;
    uint64_t spp_index;
    uint64_t ts;
    // FIXME: Remove this from here! as we create large arrays of pbuf_desc!!
    // For Statistics
    uint64_t event_ts[MAX_STAT_EVENTS];
    uint64_t event_n[MAX_STAT_EVENTS];
    uint64_t event_sum[MAX_STAT_EVENTS];
    uint64_t event_sum2[MAX_STAT_EVENTS];
    uint64_t event_max[MAX_STAT_EVENTS];
    uint64_t event_min[MAX_STAT_EVENTS];
    uint64_t event_sum_i[MAX_STAT_EVENTS];
    uint64_t event_sum2_i[MAX_STAT_EVENTS];
    uint64_t event_max_i[MAX_STAT_EVENTS];
    uint64_t event_min_i[MAX_STAT_EVENTS];
};

struct client_closure;

struct tx_pbuf {
    struct buffer_descriptor *buffer;
    struct ether_binding *sr;
    struct client_closure *cc;
    bool is_priv;
    bool can_send;
    bool last;
    uint64_t len;
    uint64_t offset;
    uint64_t client_data;
    uint64_t buffer_id;
    uint64_t spp_index;
    uint64_t ts;

};

/* This is client_closure for network service */
struct client_closure {
    int cl_no;
    struct buffer_descriptor *buffer_ptr;
    struct shared_pool_private *spp_ptr;

    /* Following two are used by packet transmit logic */
    uintptr_t nr_transmit_pbufs; /*< how many pbufs belong to the packet to
                                        transmit now? */
    /* FIXME: following should be a number */
//    uintptr_t rtpbuf; ///< how many pbufs have we received so far?
    uint16_t rtpbuf; ///< how many pbufs have we received so far?
    struct tx_pbuf pbuf[MAX_NR_TRANSMIT_PBUFS];
    uint64_t tx_private_mem_v;  // FIXME: un-used, remove it
    uint64_t tx_private_mem_p;  // FIXME: un-used, remove  it
    uint64_t head;
    uint64_t tail;
    uint64_t len;

    struct ether_binding *app_connection; /* FIXME: Do I need this? */
    struct cont_queue *q;
    uint8_t debug_state;
    uint8_t debug_state_tx;
    uint64_t start_ts;
    uint64_t start_ts_tx;
    uint64_t pkt_count;
    uint64_t tx_done_count;
    uint64_t tx_explicit_msg_needed;
    uint64_t tx_notification_sent;
    uint64_t rx_notification_sent;
    uint64_t dropped_pkt_count;
    uint64_t hw_queue;
    uint64_t pbuf_count;
    uint64_t in_dropped_q_full;
    uint64_t in_dropped_invalid_pkt;
    uint64_t in_dropped_no_app;
    uint64_t in_dropped_app_buf_full;
    uint64_t in_dropped_app_invalid_buf;
    uint64_t in_dropped_notification_prob;
    uint64_t in_dropped_notification_prob2;
    uint64_t in_other_pkts;
    uint64_t in_arp_pkts;
    uint64_t in_netd_pkts;
    uint64_t in_paused_pkts;
    uint64_t in_filter_matched;
    uint64_t in_filter_matched_f;
    uint64_t in_filter_matched_p;
    uint64_t in_queue_len_n;
    uint64_t in_queue_len_sum;

    uint64_t in_app_time_n;
    uint64_t in_app_time_sum;
    uint64_t in_app_time_min;
    uint64_t in_app_time_max;
    uint64_t in_success;
    uint64_t in_trigger_counter;
    uint64_t out_trigger_counter;
    uint8_t  filter_matched;
}; /* holds info about how much data is transferred to NIC. */


/*****************************************************************
 * Driver states
 * ***************************************************************/


/*******************************************************************
 *  Following functions must be implemented by the driver which is
 *  using the library.
 ******************************************************************/
typedef void (*ether_get_mac_address_t)(uint8_t *mac);

typedef errval_t (*ether_transmit_pbuf_list_t)
                        (struct client_closure *closure);
typedef uint64_t (*ether_get_tx_free_slots)(void);
typedef bool (*ether_handle_free_TX_slot)(void);


/*****************************************************************/
void ethersrv_init(char *service_name,
		ether_get_mac_address_t get_mac_ptr,
		ether_transmit_pbuf_list_t transmit_ptr,
                ether_get_tx_free_slots tx_free_slots_ptr,
                ether_handle_free_TX_slot handle_free_tx_slots_ptr);

bool waiting_for_netd(void);

bool notify_client_free_tx(struct ether_binding * b,
                           uint64_t client_data,
                           uint64_t spp_index,
                           uint64_t rts,
                           uint64_t slots_left,
                           uint64_t dropped);
/*
bool notify_client_free_tx1(struct ether_binding * b,
                           uint64_t client_data,
                           uint64_t spp_index,
                           uint64_t rts,
                           uint64_t slots_left,
                           uint64_t dropped);
*/


void process_received_packet(void *pkt_data, size_t pkt_len);

/* for frag.c */
bool handle_fragmented_packet(void* packet, size_t len);


struct filter *execute_filters(void *data, size_t len);

/* FIXME: put this into the local include file.  */
bool copy_packet_to_user(struct buffer_descriptor* buffer,
				void *data, uint64_t len);

void do_pending_work_for_all(void);

//debug
void print_statistics(void);


// For recording statistics

enum Recorded_Events {
    RE_ALL = 0,
    RE_FILTER,
    RE_COPY,
    RE_DROPPED,
    RE_USEFUL, // used
    RE_PBUF_REG, // used
    RE_PROCESSING_ALL, // used
    RE_RX_ALL, // used
    RE_PENDING_WORK,
    RE_PENDING_1,
    RE_PENDING_2,
    RE_PENDING_3,
    RE_PENDING_4,

    RE_TX_NOTI_CS,
    RE_TX_T,
    RE_TX_SP_S,
    RE_TX_SP_F,
    RE_TX_DONE,
    RE_TX_W_ALL,
    RE_TX_DONE_NN,
    RE_TX_DONE_N,
    RE_TX_SP_MSG,
    RE_TX_SP_MSG_Q,
    EVENT_LIST_SIZE
};

extern struct netbench_details *bm;

// **************************************
// Use of optimised memcpy for SCC

void *memcpy_fast(void *dst0, const void *src0, size_t length);

#endif // ETHERSRV_H
