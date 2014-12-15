#include <enviroment.h>

#include <Classes/pci_device.h>

#include "Include/pci_device_class.h"

#define DEBUG_MODULE_NAME L"PciDeviceClass"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>

class_reference_t pci_device_class_register (
	interface_reference_t interfaces[],     
	event_supplier_interface_reference_t supplier_interfaces[],
	event_consumer_interface_reference_t consumer_interfaces[])
{
    description_reference_t class_description;

    sequence_t int_seq = {data: interfaces, count: 0};
    sequence_t sup_seq = {data: supplier_interfaces, count: 0};
    sequence_t cons_seq = {data: consumer_interfaces, count: 0};
    
    class_description = class_description_register (
        CLASS_PCI_DEVICE_ID,
        L"pci_device",
        CLASS_TYPE_STATIC,
        1, 0, 0);
    
    return class_create (class_description, int_seq, sup_seq, cons_seq, 
        REFERENCE_NULL, 0);
}

