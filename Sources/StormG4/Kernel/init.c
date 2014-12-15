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
};

#define NUMBER_OF_KERNEL_INTERFACES (sizeof (kernel_interfaces_info) / \
    sizeof (kernel_interface_info_t))

static interface_reference_t interfaces[NUMBER_OF_KERNEL_INTERFACES];
static sequence_t int_seq = {data: interfaces, count: 0};

kernel_event_supplier_interface_info_t kernel_event_supplier_interfaces_info[] =
{
    [KERNEL_EVENT_SUPPLIER_INTERFACE_IRQ_INDEX] =
        { L"IRQ", &irq_supplier_init, TRUE },

    [KERNEL_EVENT_SUPPLIER_INTERFACE_DEBUG_INDEX] =
        { L"Debug", &debug_supplier_init, TRUE },
};

#define NUMBER_OF_KERNEL_EVENT_SUPPLIER_INTERFACES \
    (sizeof (kernel_event_supplier_interfaces_info) / \
    sizeof (kernel_event_supplier_interface_info_t))

static event_supplier_interface_reference_t 
    event_supplier_interfaces[NUMBER_OF_KERNEL_INTERFACES];
static sequence_t event_sup_int_seq = {
    data: event_supplier_interfaces, count: 0};

kernel_event_consumer_interface_info_t kernel_event_consumer_interfaces_info[] =
{
    [KERNEL_EVENT_CONSUMER_INTERFACE_DEBUG_INDEX] =
        { L"Debug", &debug_consumer_init, TRUE },
};

#define NUMBER_OF_KERNEL_EVENT_CONSUMER_INTERFACES \
    (sizeof (kernel_event_consumer_interfaces_info) / \
    sizeof (kernel_event_consumer_interface_info_t))

static event_consumer_interface_reference_t 
    event_consumer_interfaces[NUMBER_OF_KERNEL_INTERFACES];
static sequence_t event_con_int_seq = {
        data: event_consumer_interfaces, count: 0};

static description_reference_t class_description;

void kernel_init (void)
{
    uint32_t index;
    uint32_t count;
    sequence_t seq_empty = {data: NULL, count: 0};
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    // Initing interfaces
    for (index = 0, count = 0; index < NUMBER_OF_KERNEL_INTERFACES; index++)
    {
        if (!kernel_interfaces_info[index].enabled)
        {
            continue;
        }
            
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Init interface: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_interfaces_info[index].name);
            
        interfaces[count] = kernel_interfaces_info[index].init ();
        kernel_interfaces_info[index].interface = interfaces[count];
    
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1, 
            L"%S: %s: Interface[%u]=%p\n",
            DEBUG_MODULE_NAME, __FUNCTION__,
            count, interfaces[count]);
            
        count++;
    }

    int_seq.count = count;

    // Initing event supplier interfaces
    for (index = 0, count = 0; 
        index < NUMBER_OF_KERNEL_EVENT_SUPPLIER_INTERFACES; index++)
    {
        if (!kernel_event_supplier_interfaces_info[index].enabled)
        {
            continue;
        }
            
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Init event supplier interface: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_event_supplier_interfaces_info[index].name);

        event_supplier_interfaces[count] = 
            kernel_event_supplier_interfaces_info[index].init ();

        count++;
    }    

    event_sup_int_seq.count = count;

    // Initing event consumer interfaces
    for (index = 0, count = 0; 
        index < NUMBER_OF_KERNEL_EVENT_CONSUMER_INTERFACES; index++)
    {
        if (!kernel_event_consumer_interfaces_info[index].enabled)
        {
            continue;
        }
            
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE, 
            L"%S: Init event consumer interface: %S\n",
            DEBUG_MODULE_NAME, 
            kernel_event_consumer_interfaces_info[index].name);

        event_consumer_interfaces[count] = 
            kernel_event_consumer_interfaces_info[index].init ();

        count++;
    }    
    
    event_con_int_seq.count = count;

    class_description = class_description_register (    
        CLASS_KERNEL_ID,
        L"kernel",
        CLASS_TYPE_STATIC,
        int_seq.count,
        event_sup_int_seq.count,
        event_con_int_seq.count);

    kernel_class = class_create (class_description, int_seq, 
        event_sup_int_seq, event_con_int_seq, REFERENCE_NULL, 0);

    kernel_object = object_create (kernel_class, SECURITY_ABSOLUTE, 
        seq_empty, 0);
}
