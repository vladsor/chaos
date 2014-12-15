
#define INTERFACE_PCI_BUS_CONTROL_ID 0x0007

enum
{
    METHOD_PCI_BUS_CONTROL_GET_AMOUNT_ID,
    METHOD_PCI_BUS_CONTROL_GET_DEVICES_ID,
    METHOD_PCI_BUS_CONTROL_FIND_DEVICES_ID,

    METHOD_PCI_BUS_CONTROL_NUMBER
};

typedef uint32_t (pci_bus_control_get_amount_t) (context_t context);
typedef pci_bus_control_get_amount_t * p_pci_bus_control_get_amount_t;
    
typedef uint32_t (pci_bus_control_get_devices_t) (context_t context, 
    sequence_t devices, uint32_t start);
typedef pci_bus_control_get_devices_t * p_pci_bus_control_get_devices_t;
    
typedef uint32_t (pci_bus_control_find_devices_t) (context_t context, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, 
    sequence_t devices, uint32_t start);
typedef pci_bus_control_find_devices_t * p_pci_bus_control_find_devices_t;

typedef struct
{
    p_pci_bus_control_get_amount_t get_amount;
    p_pci_bus_control_get_devices_t get_devices;
    p_pci_bus_control_find_devices_t find_devices;
    
} pci_bus_control_interface_table_t;

typedef pci_bus_control_interface_table_t * p_pci_bus_control_interface_table_t;

static inline handle_reference_t pci_bus_control$handle$create (
    object_reference_t object)
{
    sequence_t seq_empty = {data: NULL, count: 0};

    return handle_create (object, INTERFACE_PCI_BUS_CONTROL_ID, seq_empty, 0);
}    

static inline uint32_t pci_bus_control$get_amount (handle_reference_t handle)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    uint32_t ret = 0;
    sequence_t pars_out_seq = {data: &ret, count: 1};
    
    handle_invoke_method (handle, METHOD_PCI_BUS_CONTROL_GET_AMOUNT_ID,
        REFERENCE_NULL, empty_seq, empty_seq, pars_out_seq, 0);
    
    return ret;
}

static inline uint32_t pci_bus_control$find_devices (handle_reference_t handle, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, 
    sequence_t devices, uint32_t start)
{
    uint32_t pars_in[9] = {vendor_id, device_id, class_id, subclass_id, 
        interface_id, start};
    sequence_t pars_in_seq = {data: pars_in, count: 6};

    sequence_t empty_seq = {data: NULL, count: 0};
    
    uint32_t pars_out[] = { 0, (uint32_t) devices.data, devices.count };
    sequence_t pars_out_seq = {data: pars_out, count: 3};
    
    handle_invoke_method (handle, METHOD_PCI_BUS_CONTROL_FIND_DEVICES_ID, 
        REFERENCE_NULL, pars_in_seq, empty_seq, pars_out_seq, 0);
    
    return pars_out[0];
}    


