/* $Id: ethernet.h,v 1.1.1.1 2000/09/26 19:08:08 plundis Exp $ */
/* Abstract: Ethernet library type defintions and function
   prototypes. */
/* Author: Per Lundberg <plundis@chaosdev.org> */

/* Copyright 1999-2000 chaos development. */

#ifndef __LIBRARY_NETWORK_ETHERNET_H__
#define __LIBRARY_NETWORK_ETHERNET_H__

/* IEEE 802.3 ethernet magic constants. The frame sizes omit the
   preamble and FCS/CRC (frame check sequence). */

#define NETWORK_ETHERNET_ADDRESS_LENGTH         6
#define NETWORK_ETHERNET_HEADER_LENGTH          14

/* Min. octets in frame minus FCS. */

#define NETWORK_ETHERNET_MINIMUM_LENGTH         60  

/* Max. octets in payload. */
            
#define NETWORK_ETHERNET_DATA_LENGTH            1500

/* Max. octets in frame minus FCS. */

#define NETWORK_ETHERNET_FRAME_LENGTH           1514

/* These are the protocol ID's we support. */

#define NETWORK_ETHERNET_PROTOCOL_IPV4          0x0800
#define NETWORK_ETHERNET_PROTOCOL_ARP           0x0806
#define NETWORK_ETHERNET_PROTOCOL_IPV6          0x86DD

/* This is an ethernet frame header. */
 
typedef struct
{
    uint8_t destination_address[NETWORK_ETHERNET_ADDRESS_LENGTH];
    uint8_t source_address[NETWORK_ETHERNET_ADDRESS_LENGTH];
    uint16_t protocol_type;
    uint8_t data[0];
} network_ethernet_header_t PACKED;

/**
 * is_valid_ether_addr - Determine if the given Ethernet address is valid
 * @addr: Pointer to a six-byte array containing the Ethernet address
 *
 * Check that the Ethernet address (MAC) is not 00:00:00:00:00:00, is not
 * a multicast address, and is not FF:FF:FF:FF:FF:FF.  The multicast
 * and FF:FF:... tests are combined into the single test "!(addr[0]&1)".
 *
 * Return true if the address is valid.
 */
static inline int is_valid_ethernet_address (uint8_t *addr)
{
	const char zaddr[6] = {0,};

	return !(addr[0]&1) && memory_compare (addr, (void *) zaddr, 6);
}

/*
 *	Network device statistics. Akin to the 2.0 ether stats but
 *	with byte counters.
 */
 
typedef struct 
{
	unsigned long	rx_packets;		/* total packets received	*/
	unsigned long	tx_packets;		/* total packets transmitted	*/
	unsigned long	rx_bytes;		/* total bytes received 	*/
	unsigned long	tx_bytes;		/* total bytes transmitted	*/
	unsigned long	rx_errors;		/* bad packets received		*/
	unsigned long	tx_errors;		/* packet transmit problems	*/
	unsigned long	rx_dropped;		/* no space in linux buffers	*/
	unsigned long	tx_dropped;		/* no space available in linux	*/
	unsigned long	multicast;		/* multicast packets received	*/
	unsigned long	collisions;

	/* detailed rx_errors: */
	unsigned long	rx_length_errors;
	unsigned long	rx_over_errors;		/* receiver ring buff overflow	*/
	unsigned long	rx_crc_errors;		/* recved pkt with crc error	*/
	unsigned long	rx_frame_errors;	/* recv'd frame alignment error */
	unsigned long	rx_fifo_errors;		/* recv'r fifo overrun		*/
	unsigned long	rx_missed_errors;	/* receiver missed packet	*/

	/* detailed tx_errors */
	unsigned long	tx_aborted_errors;
	unsigned long	tx_carrier_errors;
	unsigned long	tx_fifo_errors;
	unsigned long	tx_heartbeat_errors;
	unsigned long	tx_window_errors;
	
	/* for cslip etc */
	unsigned long	rx_compressed;
	unsigned long	tx_compressed;
} net_device_stats_t;


#endif /* !__LIBRARY_NETWORK_ETHERNET_H__ */
