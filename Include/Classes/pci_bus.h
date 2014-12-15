
#define CLASS_PCI_BUS_ID 0x0004

//#include <Interfaces/pci_bus_object_factory.h>
#include <Interfaces/pci_bus_control.h>

static inline object_reference_t pci_bus$object$create (class_reference_t class)
{
    sequence_t seq_empty = {data: NULL, count: 0};
    
    return object_create (class, SECURITY_CURRENT, seq_empty, 0);
}

