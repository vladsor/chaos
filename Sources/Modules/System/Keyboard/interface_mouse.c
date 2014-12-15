#include <enviroment.h>
#include <string.h>

#include <Classes/mouse.h>

#include "Include/controller.h"
#include "Include/mouse.h"

#include "Include/interface.h"

#include "Include/mouse_class.h"
#include "Include/debug_event_class.h"
#include "Include/irq_event_class.h"
#include "Include/mouse_event_class.h"
#include "Include/event_supplier_factory_interface.h"

#define DEBUG_MODULE_NAME L"Mouse"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (mouse_debug_supplier)
#endif

#include <debug/macros.h>
#include <exception/macros.h>

static interface_reference_t mouse_interfaces[1];
static event_supplier_interface_reference_t mouse_event_suppliers[2];
static event_consumer_interface_reference_t mouse_event_consumers[1];

static class_reference_t mouse_class; 
static object_reference_t mouse_object;
volatile event_supplier_reference_t mouse_debug_supplier = REFERENCE_NULL;
static event_supplier_reference_t mouse_irq_supplier;
static event_consumer_reference_t mouse_irq_consumer;
static event_queue_reference_t mouse_irq_queue;

static cpu_reference_t irq_handler_cpu = REFERENCE_NULL;

/* Handler for the mouse IRQ. */

static void mouse_irq_handler (context_t context UNUSED)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    handle_event ();
}

static volatile event_supplier_reference_t mouse_supplier = REFERENCE_NULL;

static void create (context_t context UNUSED, 
    event_supplier_reference_t event_supplier)
{
    mouse_supplier = event_supplier;
}    

static void destroy (context_t context UNUSED, 
    event_supplier_reference_t event_supplier UNUSED)
{
    mouse_supplier = REFERENCE_NULL;
}    

static event_supplier_factory_interface_table_t table =
{
    create: &create,
    destroy: &destroy
};    

void interface_fire_mouse_event (uint32_t x, uint32_t y, uint32_t button)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    if (mouse_supplier == REFERENCE_NULL)
    {
        return;
    }
    
    mouse$fire (mouse_supplier, x, y, button);
}
    
/* Main function for the mouse handling. */

return_t mouse_main (int argc UNUSED, char *argv[] UNUSED, char **envp UNUSED)
{
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    /* Initialise a PS/2 mouse port, if found. */

    if (!mouse_init ())
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: Init failed.\n", 
            DEBUG_MODULE_NAME);
	
        return -1;
    }    

    mouse_interfaces[0] = event_supplier_factory_interface_register (&table);

    mouse_event_suppliers[0] = mouse_supplier_interface_register (
        EVENT_SUPPLIER_TYPE_PUSH, NULL, REFERENCE_NULL, mouse_interfaces[0]);

    mouse_event_suppliers[1] = debug_supplier_interface_register (
        EVENT_SUPPLIER_TYPE_PUSH, NULL, REFERENCE_NULL);

    irq_handler_cpu = cpu_create (0);

    mouse_event_consumers[0] = irq_consumer_interface_register (
        EVENT_CONSUMER_TYPE_PUSH, &mouse_irq_handler, irq_handler_cpu);

    mouse_class = mouse_class_register (mouse_interfaces, mouse_event_suppliers,
        mouse_event_consumers, REFERENCE_NULL);

    mouse_object = object_create (mouse_class, SECURITY_CURRENT, 
        empty_seq, 0);

    mouse_debug_supplier = debug$supplier$create (mouse_object);
    event_supplier_set_queue (mouse_debug_supplier, kernel_debug_queue);
    
    mouse_supplier = mouse$supplier$create (mouse_object);

    /* Handle the mouse IRQs. */

    mouse_irq_supplier = irq$supplier$create (OBJECT_KERNEL, MOUSE_IRQ);
    mouse_irq_consumer = irq$consumer$create (mouse_object);

    mouse_irq_queue = event_queue_create (irq_description_register (), 
        EVENT_QUEUE_TYPE_ASYNCHRONOUS, 1);
    event_supplier_set_queue (mouse_irq_supplier, mouse_irq_queue);
    event_consumer_set_queue (mouse_irq_consumer, mouse_irq_queue);

    namespace$bind (kernel_handle_namespace, L"/devices/mouse", 
        mouse_object);

    return 0;
}

