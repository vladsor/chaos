
#define CLASS_PCI_BUS_OBJECT_ID 0x0004

//#include <Interfaces/pci_bus_object_factory.h>
#include <Interfaces/pci_bus.h>

static inline object_reference_t pci_bus_object$create (class_reference_t class)
{
    sequence_t seq_empty = {NULL, 0, 0};
    
    return object_create (class, seq_empty, SECURITY_CURRENT, seq_empty, 0);
}

