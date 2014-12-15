#define IID_PCI_BUS 0x00003001

enum
{
    MID_PCI_BUS_GET_AMOUNT,
    MID_PCI_BUS_GET_DEVICES,
    MID_PCI_BUS_FIND_DEVICES,
};

typedef return_t (pci_bus_get_amount_function_t) (context_t *context, 
    uint32_t *devices);
typedef return_t (pci_bus_get_devices_function_t) (context_t *context, 
    uint32_t start, uint32_t count, handle_t *devices);
typedef return_t (pci_bus_find_devices_function_t) (context_t *context, 
    uint16_t vendor_id, uint16_t device_id, uint8_t class_id, 
    uint8_t subclass_id, uint8_t interface_id, uint32_t start, 
    uint32_t *count, handle_t *devices);

typedef struct
{
    pci_bus_get_amount_function_t *get_amount;
    pci_bus_get_devices_function_t *get_devices;
    pci_bus_find_devices_function_t *find_devices;
} pci_bus_interface_t;

typedef struct
{
    pci_bus_get_amount_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} pci_bus_get_amount_method_t;

#define PCI_BUS_GET_AMOUNT_METHOD(function) \
    (&(function)), \
    (MID_PCI_BUS_GET_AMOUNT), \
    (sizeof (uint32_t *)), \
    (1), \
    { \
        {sizeof (uint32_t *)}, \
    }    

typedef struct
{
    pci_bus_get_devices_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[3];

} pci_bus_get_devices_method_t;

#define PCI_BUS_GET_DEVICES_METHOD(function) \
    (&(function)), \
    (MID_PCI_BUS_GET_DEVICES), \
    (sizeof (uint32_t *)), \
    (3), \
    { \
        {sizeof (uint32_t)}, \
        {sizeof (uint32_t)}, \
        {sizeof (handle_t *)}, \
    }    

typedef struct
{
    pci_bus_find_devices_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[8];

} pci_bus_find_devices_method_t;

#define PCI_BUS_FIND_DEVICES_METHOD(function) \
    (&(function)), \
    (MID_PCI_BUS_GET_DEVICES), \
    (sizeof (uint32_t *)), \
    (8), \
    { \
        {sizeof (uint16_t)}, \
        {sizeof (uint16_t)}, \
        {sizeof (uint16_t)}, \
        {sizeof (uint16_t)}, \
        {sizeof (uint16_t)}, \
        {sizeof (uint32_t)}, \
        {sizeof (uint32_t *)}, \
        {sizeof (handle_t *)}, \
    }    

#define pci_bus$get_amount(handle,devices) \
    ((pci_bus_interface_t *) ((handle)->functions))->get_amount ( \
        &((handle)->context), \
        (device))

#define pci_bus$get_devices(handle,start,count,devices) \
    ((pci_bus_interface_t *) ((handle)->functions))->get_devices ( \
        &((handle)->context), \
        (start), (count), (devices))

#define pci_bus$find_devices(handle,vendor_id,device_id,class_id,subclass_id,\
        interface_id,start,count,devices) \
    ((pci_bus_interface_t *) ((handle)->functions))->find_devices ( \
        &((handle)->context), \
        (vendor_id), (device_id), (class_id), (subclass_id), (interface_id), \
        (start), (count), (devices))

