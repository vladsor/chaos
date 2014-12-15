#include <enviroment.h>

#define DEBUG_MODULE_NAME "PciBusObjectClass"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/pci_bus_object.h>

#include "Include/pci_bus_object_class.h"

#include <debug/macros.h>

static class_description_t class_description =
{
/*    class_id_t id; */
    CLASS_PCI_BUS_OBJECT_ID,

/*    wchar_t name[WSTRING_MAX_LENGTH]; */
    L"pci_bus_object",

/*    uint32_t type; */
    CLASS_TYPE_STATIC,
    
/*    uint32_t number_of_interfaces; */
    0,
};

class_reference_t pci_bus_object_class_register (interface_reference_t interfaces[])
{
    sequence_t seqs;
    seqs.data = interfaces;
    seqs.count = 1;
    
    return class_create (&class_description, seqs, REFERENCE_NULL);
}

