#define IID_PCI_DEVICE 0x00003002

enum
{
    MID_PCI_DEVICE_GET_INFO,
    MID_PCI_DEVICE_ENABLE,
    MID_PCI_DEVICE_DISABLE,
    MID_PCI_DEVICE_SET_MASTER,
};

#define PCI_NUMBER_OF_RESOURCES         12

#ifndef PCI_RESOURCE_DEFINED
#define PCI_RESOURCE_DEFINED
typedef struct 
{
    const char *name;
    unsigned long start, end;
    unsigned long flags;
} pci_resource_t;
#endif /* !PCI_RESOURCE_DEFINED */

typedef struct
{
    uint16_t vendor_id;
    char vendor_name[80];

    uint16_t device_id;
    char device_name[80];

    unsigned int irq;
  
    pci_resource_t resource[PCI_NUMBER_OF_RESOURCES];

} pci_device_info_t;

typedef return_t (pci_device_get_info_function_t) (context_t *context, 
    pci_device_info_t *info);
typedef return_t (pci_device_enable_function_t) (context_t *context);
typedef return_t (pci_device_disable_function_t) (context_t *context);
typedef return_t (pci_device_set_master_function_t) (context_t *context);

typedef struct
{
    pci_device_get_info_function_t *get_info;

    pci_device_enable_function_t *enable;
    pci_device_disable_function_t *disable;
    pci_device_set_master_function_t *set_master;
    
} pci_device_interface_t;

typedef struct
{
    pci_device_get_info_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} pci_device_get_info_method_t;

#define PCI_DEVICE_GET_INFO_METHOD(function) \
    (&(function)), \
    (MID_PCI_DEVICE_GET_INFO), \
    (sizeof (uint32_t *)), \
    (1), \
    { \
        {sizeof (uint32_t *)}, \
    }    

typedef struct
{
    pci_device_enable_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} pci_device_enable_method_t;

#define PCI_DEVICE_ENABLE_METHOD(function) \
    (&(function)), \
    (MID_PCI_DEVICE_ENABLE), \
    (0), \
    (0)  

typedef struct
{
    pci_device_disable_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} pci_device_disable_method_t;

#define PCI_DEVICE_DISABLE_METHOD(function) \
    (&(function)), \
    (MID_PCI_DEVICE_DISABLE), \
    (0), \
    (0)  

typedef struct
{
    pci_device_set_master_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} pci_device_set_master_method_t;

#define PCI_DEVICE_SET_MASTER_METHOD(function) \
    (&(function)), \
    (MID_PCI_DEVICE_SET_MASTER), \
    (0), \
    (0)  

#define pci_device$get_info(handle,info) \
    ((pci_device_interface_t *) ((handle)->functions))->get_info ( \
        &((handle)->context), \
        (info))

#define pci_device$enable(handle) \
    ((pci_device_interface_t *) ((handle)->functions))->enable ( \
        &((handle)->context))

#define pci_device$disable(handle) \
    ((pci_device_interface_t *) ((handle)->functions))->disable ( \
        &((handle)->context))

#define pci_device$set_master(handle) \
    ((pci_device_interface_t *) ((handle)->functions))->set_master ( \
        &((handle)->context))
