#include <enviroment.h>
#include <string.h>

#include <Classes/keyboard.h>

#include "Include/controller.h"
#include "Include/keyboard.h"

#include "Include/interface.h"

#include "Include/keyboard_class.h"
#include "Include/debug_event_class.h"
#include "Include/irq_event_class.h"
#include "Include/keyboard_event_class.h"
#include "Include/event_supplier_factory_interface.h"

#define DEBUG_MODULE_NAME L"Keyboard"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#ifndef __STORM_KERNEL__
#   define DEBUG_SUPPLIER (keyboard_debug_supplier)
#endif

#include <debug/macros.h>
#include <exception/macros.h>

static interface_reference_t keyboard_interfaces[1];
static event_supplier_interface_reference_t keyboard_event_suppliers[2];
static event_consumer_interface_reference_t keyboard_event_consumers[1];

static class_reference_t keyboard_class; 
static object_reference_t keyboard_object;
volatile event_supplier_reference_t keyboard_debug_supplier = REFERENCE_NULL;
static event_supplier_reference_t keyboard_irq_supplier;
static event_consumer_reference_t keyboard_irq_consumer;
static event_queue_reference_t keyboard_irq_queue;

static cpu_reference_t irq_handler_cpu = REFERENCE_NULL;

/* Handler for the keyboard IRQ. */

static void keyboard_irq_handler (context_t context UNUSED)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    handle_event ();
}

static volatile event_supplier_reference_t keyboard_supplier = REFERENCE_NULL;

static void create (context_t context UNUSED, 
    event_supplier_reference_t event_supplier)
{
    keyboard_supplier = event_supplier;
}    

static void destroy (context_t context UNUSED, 
    event_supplier_reference_t event_supplier UNUSED)
{
    keyboard_supplier = REFERENCE_NULL;
}    

static event_supplier_factory_interface_table_t table =
{
    create: &create,
    destroy: &destroy
};    

void interface_fire_keyboard_event (p_keyboard_event_data_t event_data)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
        
    if (keyboard_supplier == REFERENCE_NULL)
    {
        return;
    }
    
    keyboard$fire (keyboard_supplier, event_data);
}    

/* Main function for the keyboard handling. */

return_t keyboard_main (int argc UNUSED, char *argv[] UNUSED, 
    char **envp UNUSED)
{
    const char *message;
    sequence_t empty_seq = {data: NULL, count: 0};

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%u, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        argc, argv, envp);

    /* Flush any pending input. */

    keyboard_clear_input ();

    message = keyboard_init ();

    if (message != NULL)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR, 
            L"%S: %s\n", 
            DEBUG_MODULE_NAME,
            message);
	
        return -1;
    }

    keyboard_interfaces[0] = event_supplier_factory_interface_register (&table);
    
    keyboard_event_suppliers[0] = keyboard_supplier_interface_register (
        EVENT_SUPPLIER_TYPE_PUSH, NULL, REFERENCE_NULL, keyboard_interfaces[0]);

    keyboard_event_suppliers[1] = debug_supplier_interface_register (
        EVENT_SUPPLIER_TYPE_PUSH, NULL, REFERENCE_NULL);

    irq_handler_cpu = cpu_create (0);
    
    keyboard_event_consumers[0] = irq_consumer_interface_register (
        EVENT_CONSUMER_TYPE_PUSH, &keyboard_irq_handler, irq_handler_cpu);

    keyboard_class = keyboard_class_register (keyboard_interfaces, 
        keyboard_event_suppliers, keyboard_event_consumers, REFERENCE_NULL);

    keyboard_object = object_create (keyboard_class, SECURITY_CURRENT, 
        empty_seq, 0);

    keyboard_debug_supplier = debug$supplier$create (keyboard_object);
    event_supplier_set_queue (keyboard_debug_supplier, kernel_debug_queue);

    keyboard_supplier = keyboard$supplier$create (keyboard_object);

    /* Handle keyboard IRQs. */

    keyboard_irq_supplier = irq$supplier$create (OBJECT_KERNEL, KEYBOARD_IRQ);
    keyboard_irq_consumer = irq$consumer$create (keyboard_object);

    keyboard_irq_queue = event_queue_create (irq_description_register (), 
        EVENT_QUEUE_TYPE_ASYNCHRONOUS, 1);
    event_supplier_set_queue (keyboard_irq_supplier, keyboard_irq_queue);
    event_consumer_set_queue (keyboard_irq_consumer, keyboard_irq_queue);

    /* Update the keyboard LEDs. */

    keyboard_update_leds ();

    /* No keys pressed at startup. */

    keyboard_reset_pressed_keys ();
    
    keyboard_load_maps ();

    namespace$bind (kernel_handle_namespace, L"/devices/keyboard", 
        keyboard_object);
    
    return 0;
}


