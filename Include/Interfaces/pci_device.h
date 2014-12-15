#ifndef __INTERFACE_PCI_DEVICE_H__
#define __INTERFACE_PCI_DEVICE_H__

#define INTERFACE_PCI_DEVICE_ID 0x0009

enum
{
    METHOD_PCI_DEVICE_GET_INFO_ID,
    METHOD_PCI_DEVICE_ENABLE_ID,
    METHOD_PCI_DEVICE_DISABLE_ID,
    METHOD_PCI_DEVICE_SET_MASTER_ID,
    
    METHOD_PCI_DEVICE_NUMBER
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

typedef void (pci_device_get_info_t) (context_t context, 
    pci_device_info_t *info);
typedef pci_device_get_info_t * p_pci_device_get_info_t;
    
typedef void (pci_device_enable_t) (context_t context);
typedef pci_device_enable_t * p_pci_device_enable_t;

typedef void (pci_device_disable_t) (context_t context);
typedef pci_device_disable_t * p_pci_device_disable_t;

typedef void (pci_device_set_master_t) (context_t context);
typedef pci_device_set_master_t * p_pci_device_set_master_t;

typedef struct
{
    p_pci_device_get_info_t get_info;
    p_pci_device_enable_t enable;
    p_pci_device_disable_t disable;
    p_pci_device_set_master_t set_master;
    
} pci_device_interface_table_t;

typedef pci_device_interface_table_t * p_pci_device_interface_table_t;

static inline handle_reference_t pci_device$open (object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0, 0};

    return handle_create (object, INTERFACE_PCI_DEVICE_ID, seq_empty, 0);
}    

static inline void pci_device$get_info (handle_reference_t handle,
    pci_device_info_t *info)
{
    sequence_t ret_seq = {data: NULL, count: 0, block_size: 0};
    uint32_t pars[1] = {(uint32_t) info};
    sequence_t pars_seq = {data: pars, count: 1, block_size: 4};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_GET_INFO_ID, ret_seq, 
        pars_seq);
}

static inline void pci_device$enable (handle_reference_t handle)
{
    sequence_t seq = {data: NULL, count: 0, block_size: 0};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_ENABLE_ID, seq, seq);
}

static inline void pci_device$set_master (handle_reference_t handle)
{
    sequence_t seq = {data: NULL, count: 0, block_size: 0};
    
    handle_invoke_method (handle, METHOD_PCI_DEVICE_SET_MASTER_ID, seq, seq);
}


#endif /* !__INTERFACE_PCI_DEVICE_H__ */

