
#define CLASS_PCI_DEVICE_OBJECT_ID 0x0005

//#include <Interfaces/pci_device_object_factory.h>
#include <Interfaces/pci_device.h>

static inline object_reference_t pci_device_object$create (
    class_reference_t class, void *device)
{
    sequence_t seq_empty = {NULL, 0, 0};
    sequence_t pars = {device, 0, 0};
    
    return object_create (class, seq_empty, SECURITY_CURRENT, pars, 0);
}

