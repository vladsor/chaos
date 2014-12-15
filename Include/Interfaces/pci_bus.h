
#define INTERFACE_PCI_BUS_ID 0x0007

enum
{
    METHOD_PCI_BUS_GET_AMOUNT_ID,
    METHOD_PCI_BUS_GET_DEVICES_ID,
    METHOD_PCI_BUS_FIND_DEVICES_ID,

    METHOD_PCI_BUS_NUMBER
};

typedef uint32_t (pci_bus_get_amount_t) (context_t context);
typedef pci_bus_get_amount_t * p_pci_bus_get_amount_t;
    
typedef uint32_t (pci_bus_get_devices_t) (context_t context, 
    sequence_t devices, uint32_t start);
typedef pci_bus_get_devices_t * p_pci_bus_get_devices_t;
    
typedef uint32_t (pci_bus_find_devices_t) (context_t context, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, 
    sequence_t devices, uint32_t start);
typedef pci_bus_find_devices_t * p_pci_bus_find_devices_t;

typedef struct
{
    p_pci_bus_get_amount_t get_amount;
    p_pci_bus_get_devices_t get_devices;
    p_pci_bus_find_devices_t find_devices;
} pci_bus_interface_table_t;

typedef pci_bus_interface_table_t * p_pci_bus_interface_table_t;

static inline handle_reference_t pci_bus$open (object_reference_t object)
{
    sequence_t seq_empty = {NULL, 0, 0};

    return handle_create (object, INTERFACE_PCI_BUS_ID, seq_empty, 0);
}    

static inline uint32_t pci_bus$get_amount (handle_reference_t handle)
{
    sequence_t pars_seq = {data: NULL, count: 0, block_size: 0};
    uint32_t ret = 0;
    sequence_t ret_seq = {data: &ret, count: 1, block_size: 4};
    
    handle_invoke_method (handle, METHOD_PCI_BUS_GET_AMOUNT_ID, ret_seq, 
        pars_seq);
    
    return ret;
}

static inline uint32_t pci_bus$find_devices (handle_reference_t handle, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, 
    sequence_t devices, uint32_t start)
{
    uint32_t ret = 0;
    sequence_t ret_seq = {data: &ret, count: 1, block_size: 4};
    uint32_t pars[9] = {vendor_id, device_id, class_id, subclass_id, 
        interface_id, 
        (uint32_t) devices.data, devices.count, devices.block_size, start};
    sequence_t pars_seq = {data: pars, count: 9, block_size: 9 * 4};
    
    handle_invoke_method (handle, METHOD_PCI_BUS_FIND_DEVICES_ID, ret_seq, 
        pars_seq);
    
    return ret;
}    


