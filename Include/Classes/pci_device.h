
#define CLASS_PCI_DEVICE_ID 0x0005

//#include <Interfaces/pci_device_object_factory.h>
#include <Interfaces/pci_device_control.h>

static inline object_reference_t pci_device$object$create (
    class_reference_t class)
{
    sequence_t seq_empty = {data: NULL, count: 0};
    
    return object_create (class, SECURITY_CURRENT, seq_empty, 0);
}

