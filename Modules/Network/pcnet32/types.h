
#include "ethernet.h"

extern int pcnet32_debug;
extern const char *version;

#define PORT_AUI      0x00
#define PORT_10BT     0x01
#define PORT_GPSI     0x02
#define PORT_MII      0x03

#define PORT_PORTSEL  0x03
#define PORT_ASEL     0x04
#define PORT_100      0x40
#define PORT_FD	      0x80

/* PCnet32 access functions */
typedef struct  
{
    uint16_t (*read_csr)(unsigned long, int);
    void (*write_csr)(unsigned long, int, uint16_t);
    uint16_t (*read_bcr)(unsigned long, int);
    void (*write_bcr)(unsigned long, int, uint16_t);
    uint16_t (*read_rap)(unsigned long);
    void (*write_rap)(unsigned long, uint16_t);
    void (*reset)(unsigned long);
} pcnet32_access_t;

/* The PCNET32 Rx and Tx ring descriptors. */
typedef struct 
{
    uint32_t base;
    int16_t buf_length;
    int16_t status;	   
    uint32_t msg_length;
    uint32_t reserved;
} pcnet32_rx_head_t;
	
typedef struct
{
    uint32_t base;
    int16_t length;
    int16_t status;
    uint32_t misc;
    uint32_t reserved;
} pcnet32_tx_head_t;

/* The PCNET32 32-Bit initialization block, described in databook. */
typedef struct 
{
    uint16_t mode;
    uint16_t tlen_rlen;
    uint8_t phys_addr[6];
    uint16_t reserved;
    uint32_t filter[2];
    /* Receive and transmit ring base, along with extra bits. */    
    uint32_t rx_ring;
    uint32_t tx_ring;
} pcnet32_init_block_t;

/*
 * Set the number of Tx and Rx buffers, using Log_2(# buffers).
 * Reasonable default values are 4 Tx buffers, and 16 Rx buffers.
 * That translates to 2 (4 == 2^^2) and 4 (16 == 2^^4).
 */
#ifndef PCNET32_LOG_TX_BUFFERS
#define PCNET32_LOG_TX_BUFFERS 4
#define PCNET32_LOG_RX_BUFFERS 5
#endif

#define TX_RING_SIZE			(1 << (PCNET32_LOG_TX_BUFFERS))
#define TX_RING_MOD_MASK		(TX_RING_SIZE - 1)
#define TX_RING_LEN_BITS		((PCNET32_LOG_TX_BUFFERS) << 12)

#define RX_RING_SIZE			(1 << (PCNET32_LOG_RX_BUFFERS))
#define RX_RING_MOD_MASK		(RX_RING_SIZE - 1)
#define RX_RING_LEN_BITS		((PCNET32_LOG_RX_BUFFERS) << 4)

typedef uint32_t dma_addr_t;

typedef struct
{
    uint8_t ethernet_address[NETWORK_ETHERNET_ADDRESS_LENGTH];
    char name[256];
    unsigned long base_addr;
    int irq;
    struct pcnet32_private_t *priv;

    int watchdog_timeo;
} ethernet_device_t;

/*
 * The first three fields of pcnet32_private are read by the ethernet device 
 * so we allocate the structure should be allocated by pci_alloc_consistent().
 */
typedef struct 
{
    /* The Tx and Rx ring entries must be aligned on 16-byte boundaries in 32bit mode. */
    pcnet32_rx_head_t rx_ring[RX_RING_SIZE];
    pcnet32_tx_head_t tx_ring[TX_RING_SIZE];
    pcnet32_init_block_t init_block;
    dma_addr_t dma_addr;		/* DMA address of beginning of this object, returned by pci_alloc_consistent */

    handle_t pci_device;		/* Pointer to the associated pci device structure */

    const char *name;
    /* The saved address of a sent-in-place packet/buffer, for skfree(). */
    void *tx_skbuff[TX_RING_SIZE];
    void *rx_skbuff[RX_RING_SIZE];
    dma_addr_t tx_dma_addr[TX_RING_SIZE];
    dma_addr_t rx_dma_addr[RX_RING_SIZE];
    pcnet32_access_t a;
    spinlock_t lock;					/* Guard lock */
    unsigned int cur_rx, cur_tx;		/* The next free ring entry */
    unsigned int dirty_rx, dirty_tx;	/* The ring entries to be free()ed. */
    net_device_stats_t stats;
    char tx_full;
    int	 options;
    int	 shared_irq:1,			/* shared irq possible */
	ltint:1,
#ifdef DO_DXSUFLO
	      dxsuflo:1,						    /* disable transmit stop on uflo */
#endif
	full_duplex:1,				/* full duplex possible */
	mii:1;					/* mii port available */
    
    ethernet_device_t *next;
} pcnet32_private_t;


