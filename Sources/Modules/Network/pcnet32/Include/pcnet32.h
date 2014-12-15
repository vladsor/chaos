
#include <Interfaces/pci_device.h>

extern int pcnet32_open (ethernet_device_t *dev);
extern void pcnet32_restart (ethernet_device_t *dev, unsigned int csr0_bits);
extern int pcnet32_close (ethernet_device_t *dev);
extern net_device_stats_t * pcnet32_get_stats (ethernet_device_t *dev);

extern ethernet_device_t * pcnet32_probe_pci (handle_reference_t device, 
    pci_device_info_t *device_info);
extern void pcnet32_interrupt (unsigned int irq_number, p_void_t parameter, 
    irq_cpu_registers_t registers);

extern void pcnet32_purge_tx_ring (ethernet_device_t *dev);
extern int pcnet32_init_ring (ethernet_device_t *dev);
extern void pcnet32_tx_timeout (ethernet_device_t *dev);
extern int pcnet32_start_xmit (ethernet_device_t *dev, void *data, 
    size_t length);
extern int pcnet32_rx (ethernet_device_t *dev);
