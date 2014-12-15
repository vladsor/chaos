
#ifndef __INTERFACE_PCI_DEVICE_CONTROL_H__
#define __INTERFACE_PCI_DEVICE_CONTROL_H__

#define INTERFACE_PCI_DEVICE_CONTROL_ID 0x0009

enum
{
    METHOD_PCI_DEVICE_CONTROL_GET_INFO_ID,
    METHOD_PCI_DEVICE_CONTROL_ENABLE_ID,
    METHOD_PCI_DEVICE_CONTROL_DISABLE_ID,
    METHOD_PCI_DEVICE_CONTROL_SET_MASTER_ID,
    
    METHOD_PCI_DEVICE_CONTROL_NUMBER
};

#ifndef PCI_RESOURCE_DEFINED
#define PCI_RESOURCE_DEFINED

#define PCI_NUMBER_OF_RESOURCES         (12)
typedef struct 
{
    const char *name;
    unsigned long start, end;
    unsigned long flags;
} pci_resource_t;


#define PCI_RESOURCE_IO                 BIT_BALUE (8)
#define PCI_RESOURCE_MEMORY             BIT_VALUE (9)
#define PCI_RESOURCE_IRQ                BIT_VALUE (10)
#define PCI_RESOURCE_DMA                BIT_VALUE (11)

#endif /* !PCI_RESOURCE_DEFINED */

typedef struct
{
    uint16_t vendor_id;
    char vendor_name[80];

    uint16_t device_id;
    char device_name[80];

    unsigned int irq;
  
    pci_resource_t resource[PCI_NUMBER_OF_RESOURCES];

} pci_device_info_t;

typedef void (pci_device_control_get_info_t) (context_t context, 
    pci_device_info_t *info);
typedef pci_device_control_get_info_t * p_pci_device_control_get_info_t;
    
typedef void (pci_device_control_enable_t) (context_t context);
typedef pci_device_control_enable_t * p_pci_device_control_enable_t;

typedef void (pci_device_control_disable_t) (context_t context);
typedef pci_device_control_disable_t * p_pci_device_control_disable_t;

typedef void (pci_device_control_set_master_t) (context_t context);
typedef pci_device_control_set_master_t * p_pci_device_control_set_master_t;

typedef struct
{
    p_pci_device_control_get_info_t get_info;
    p_pci_device_control_enable_t enable;
    p_pci_device_control_disable_t disable;
    p_pci_device_control_set_master_t set_master;
    
} pci_device_control_interface_table_t;

typedef pci_device_control_interface_table_t * 
    p_pci_device_control_interface_table_t;

static inline handle_reference_t pci_device_control$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_PCI_DEVICE_CONTROL_ID, seq_empty, 0);
}    

static inline void pci_device_control$get_info (handle_reference_t handle,
    pci_device_info_t *info)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    uint32_t pars_out[1] = {(uint32_t) info};
    sequence_t pars_out_seq = {data: pars_out, count: 1};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_CONTROL_GET_INFO_ID, 
        REFERENCE_NULL, empty_seq, empty_seq, pars_out_seq, 0);
}

static inline void pci_device_control$enable (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_CONTROL_ENABLE_ID, 
        REFERENCE_NULL, empty_seq, empty_seq, empty_seq, 0);
}

static inline void pci_device_control$set_master (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_CONTROL_SET_MASTER_ID, 
        REFERENCE_NULL, empty_seq, empty_seq, empty_seq, 0);
}

#endif /* !__INTERFACE_PCI_DEVICE_CONTROL_H__ */

