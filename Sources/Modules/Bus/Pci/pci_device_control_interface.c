#include <enviroment.h>

#include <Interfaces/pci_device_control.h>
#include "Include/pci_device_control_interface.h"

#define DEBUG_MODULE_NAME L"PciDeviceControl"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void get_info_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_pci_device_control_get_info_t get_info;
    pci_device_info_t *info;

    get_info = (p_pci_device_control_get_info_t) (address_t) function;

    info = (pci_device_info_t *) ((p_uint32_t) (parameters_out.data))[0];
    
    get_info (context, info);
}

static void enable_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_pci_device_control_enable_t enable;
    
    enable = (p_pci_device_control_enable_t) (address_t) function;
    
    enable (context);
}

static void disable_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_pci_device_control_disable_t disable;
    
    disable = (p_pci_device_control_disable_t) (address_t) function;
    
    disable (context);
}

static void set_master_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in UNUSED, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_pci_device_control_set_master_t set_master;
    
    set_master = (p_pci_device_control_set_master_t) (address_t) function;
    
    set_master (context);
}

static description_reference_t method_description_get_info;
static description_reference_t method_description_enable;
static description_reference_t method_description_disable;
static description_reference_t method_description_set_master;

static method_reference_t methods[METHOD_PCI_DEVICE_CONTROL_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_PCI_DEVICE_CONTROL_NUMBER};

static description_reference_t interface_description;

interface_reference_t pci_device_control_interface_register (
    p_pci_device_control_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_get_info = method_description_register (
        METHOD_PCI_DEVICE_CONTROL_GET_INFO_ID,
        L"get_info",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_DEVICE_CONTROL_GET_INFO_ID] = method_create_dynamic (
        method_description_get_info, REFERENCE_NULL, MEMORY_CURRENT,
        &get_info_wrapper, (address_t) table->get_info, 0);

    method_description_enable = method_description_register (
        METHOD_PCI_DEVICE_CONTROL_ENABLE_ID,
        L"enable",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_DEVICE_CONTROL_ENABLE_ID] = method_create_dynamic (
        method_description_enable, REFERENCE_NULL, MEMORY_CURRENT,
        &enable_wrapper, (address_t) table->enable, 0);

    method_description_disable = method_description_register (
        METHOD_PCI_DEVICE_CONTROL_DISABLE_ID,
        L"disable",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_DEVICE_CONTROL_DISABLE_ID] = method_create_dynamic (
        method_description_disable, REFERENCE_NULL, MEMORY_CURRENT,
        &disable_wrapper, (address_t) table->disable, 0);
    
    method_description_set_master = method_description_register (
        METHOD_PCI_DEVICE_CONTROL_SET_MASTER_ID,
        L"set_master",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_PCI_DEVICE_CONTROL_SET_MASTER_ID] = method_create_dynamic (
        method_description_set_master, REFERENCE_NULL, MEMORY_CURRENT,
        &set_master_wrapper, (address_t) table->set_master, 0);
    
    interface_description = interface_description_register (
        INTERFACE_PCI_DEVICE_CONTROL_ID,
        L"pci_device_control",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);

    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

