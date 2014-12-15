#include <enviroment.h>

#define DEBUG_MODULE_NAME L"Kernel"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/kernel.h"

#include <Classes/kernel.h>

#include "interfaces.h"
#include "event_supplier_interfaces.h"
#include "event_consumer_interfaces.h"

#include <debug/macros.h>

class_reference_t kernel_class;
object_reference_t kernel_object;

kernel_interface_info_t kernel_interfaces_info[] =
{
    [KERNEL_INTERFACE_KERNEL_CONTROL_INDEX] =
        { L"KernelControl", &kernel_control_init, REFERENCE_NULL, TRUE },
        
    [KERNEL_INTERFACE_FLAT_NAMESPACE_OBJECT_FACTORY_INDEX] = 
        { L"FlatNamespaceObjectFactory", &flat_namespace_object_factory_init, 
            REFERENCE_NULL, TRUE },
            
    [KERNEL_INTERFACE_NAMESPACE_INDEX] = 
        { L"Namespace", &namespace_init, REFERENCE_NULL, TRUE },

    [KERNEL_INTERFACE_TIMER_INDEX] =
        { L"Timer", &timer_interface_init, REFERENCE_NULL, TRUE },        

    [KERNEL_INTERFACE_STORM_MODULE_FACTORY_INDEX] =
        { L"StormModuleFactory", &storm_module_factory_interface_init, 
        REFERENCE_NULL, TRUE },        

    [KERNEL_INTERFACE_IRQ_SUPPLIER_FACTORY_INDEX] = 
        { L"IrqSupplierFactory", &irq_supplier_factory_init, 
        REFERENCE_NULL, TRUE },

    [KERNEL_INTERFACE_STORM_PROGRAM_FACTORY_INDEX] =
        { L"StormProgramFactory", &storm_program_factory_interface_init, 
        REFERENCE_NULL, TRUE },        

    [KERNEL_EVENT_SUPPLIER_INTERFACE_IRQ_INDEX] =
        { L"IRQ", &irq_supplier_init, TRUE },

    [KERNEL_EVENT_SUPPLIER_INTERFACE_DEBUG_INDEX] =
        { L"Debug", &debug_supplier_init, TRUE },
};

#define NUMBER_OF_KERNEL_INTERFACES (sizeof (kernel_interfaces_info) / \
    sizeof (kernel_interface_info_t))

kernel_role_info_t kernel_roles_info[] =
{
    [KERNEL_EVENT_CONSUMER_INTERFACE_DEBUG_INDEX] =
        { L"Debug", &debug_supplier_init, TRUE },
};

#define NUMBER_OF_KERNEL_ROLES \
    (sizeof (kernel_event_consumer_interfaces_info) / \
    sizeof (kernel_event_consumer_interface_info_t))

void kernel_init (void)
{
    uint32_t index;
    uint32_t count;
    description_reference_t class_description;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    class_description = class_description_register (    
        CLASS_KERNEL_ID,
        L"kernel",
        CLASS_TYPE_STATIC);

    kernel_class = class_create (class_description, int_seq, REFERENCE_NULL, 0);

    // Initing interfaces
    for (index = 0; index < NUMBER_OF_KERNEL_INTERFACES; index++)
    {
        if (!kernel_interfaces_info[index].enabled)
        {
            continue;
        }
            
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Init interface: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_interfaces_info[index].name);
            
        kernel_interfaces_info[index].init (kernel_class);
    }

    // Initing roles
    for (index = 0, count = 0; 
        index < NUMBER_OF_KERNEL_EVENT_SUPPLIER_INTERFACES; index++)
    {
        if (!kernel_event_supplier_interfaces_info[index].enabled)
        {
            continue;
        }
            
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Init role: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_roles_info[index].name);

        roles[count] = 
            kernel_roles_interfaces_info[index].init ();

        count++;
    }    

    kernel_object = kernel$create (kernel_class);
}
