#include <enviroment.h>

#include <Interfaces/pci_bus_control.h>
#include "Include/pci_bus_control_interface.h"

#define DEBUG_MODULE_NAME L"PciBusControl"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void get_amount_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    uint32_t count;
    p_pci_bus_control_get_amount_t get_amount;
    
    get_amount = (p_pci_bus_control_get_amount_t) (address_t) function;
    
    count = get_amount (context);

    (uint32_t) ((p_uint32_t) parameters_out.data)[0] = count;
}

static void get_devices_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_pci_bus_control_get_devices_t get_devices;
    sequence_t devices;
    uint32_t start;
    uint32_t count;
    
    get_devices = (p_pci_bus_control_get_devices_t) (address_t) function;

    start = (uint32_t) ((p_uint32_t) (parameters_in.data))[0];
    
    devices.data = (p_void_t) ((p_uint32_t) (parameters_out.data))[1];
    devices.count = (uint32_t) ((p_uint32_t) (parameters_out.data))[2];
   
    count = get_devices (context, devices, start);

    (uint32_t) ((p_uint32_t) parameters_out.data)[0] = count;
}

static void find_devices_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_pci_bus_control_find_devices_t find_devices;
    
    uint16_t vendor_id;
    uint16_t device_id;
    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;
    sequence_t devices;
    uint32_t start;
    
    uint32_t count;

    find_devices = (p_pci_bus_control_find_devices_t) (address_t) function;
    
    vendor_id = (uint32_t) ((p_uint32_t) (parameters_in.data))[0];
    device_id = (uint32_t) ((p_uint32_t) (parameters_in.data))[1];
    class_id = (uint32_t) ((p_uint32_t) (parameters_in.data))[2];
    subclass_id = (uint32_t) ((p_uint32_t) (parameters_in.data))[3];
    interface_id = (uint32_t) ((p_uint32_t) (parameters_in.data))[4];

    start = (uint32_t) ((p_uint32_t) (parameters_in.data))[5];

    devices.data = (p_void_t) ((p_uint32_t) (parameters_out.data))[1];
    devices.count = (uint32_t) ((p_uint32_t) (parameters_out.data))[2];
    
    count = find_devices (context, vendor_id, device_id, class_id, subclass_id,
        interface_id, devices, start);

    (uint32_t) ((p_uint32_t) parameters_out.data)[0] = count;
}

static description_reference_t method_description_get_amount;
static description_reference_t method_description_get_devices;
static description_reference_t method_description_find_devices;

static method_reference_t methods[METHOD_PCI_BUS_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_PCI_BUS_CONTROL_NUMBER};

static description_reference_t interface_description;

interface_reference_t pci_bus_control_interface_register (
    p_pci_bus_control_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_get_amount = method_description_register (
        METHOD_PCI_BUS_CONTROL_GET_AMOUNT_ID,
        L"get_amount",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_BUS_CONTROL_GET_AMOUNT_ID] = method_create_dynamic (
        method_description_get_amount, REFERENCE_NULL, MEMORY_CURRENT,
        &get_amount_wrapper, (address_t) table->get_amount, 0);

    method_description_get_devices = method_description_register (
        METHOD_PCI_BUS_CONTROL_GET_DEVICES_ID,
        L"get_devices",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_BUS_CONTROL_GET_DEVICES_ID] = method_create_dynamic (
        method_description_get_devices, REFERENCE_NULL, MEMORY_CURRENT,
        &get_devices_wrapper, (address_t) table->get_devices, 0);
    
    method_description_find_devices = method_description_register (
        METHOD_PCI_BUS_CONTROL_FIND_DEVICES_ID,
        L"find_devices",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_BUS_CONTROL_FIND_DEVICES_ID] = method_create_dynamic (
        method_description_find_devices, REFERENCE_NULL, MEMORY_CURRENT,
        &find_devices_wrapper, (address_t) table->find_devices, 0);

    interface_description = interface_description_register (
        INTERFACE_PCI_BUS_CONTROL_ID,
        L"pci_bus_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

