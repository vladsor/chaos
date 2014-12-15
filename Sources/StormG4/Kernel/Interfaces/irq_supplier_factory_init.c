#include <enviroment.h>

#define DEBUG_MODULE_NAME "Kernel"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <Classes/kernel.h>

#include <Interfaces/irq_supplier_factory.h>

#include "../interfaces.h"
#include "irq_supplier_factory_interface.h"

#include <debug/macros.h>
#include <exception/macros.h>

static void event_irq_handler (unsigned int irq_number UNUSED, 
    p_void_t parameter, irq_cpu_registers_t registers UNUSED)
{
    event_supplier_reference_t irq_supplier;
    
    irq_supplier = (event_supplier_reference_t) parameter;
    
    irq$fire (irq_supplier);
}

static void create (context_t context UNUSED, 
    event_supplier_reference_t irq_supplier, uint32_t irq_number)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        irq_supplier, irq_number);
    
    event_supplier_set_data (irq_supplier, irq_number);
    irq_register (irq_number, &event_irq_handler, irq_supplier);
}    

static void destroy (context_t context UNUSED, 
    event_supplier_reference_t irq_supplier)
{
    uint32_t irq_number;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        irq_supplier);
    
    irq_number = event_supplier_get_data (irq_supplier);
    irq_unregister (irq_number);
}    

static irq_supplier_factory_interface_table_t table =
{
    create: &create,
    destroy: &destroy
};    

interface_reference_t irq_supplier_factory_init (void)
{
    return irq_supplier_factory_interface_register (&table);
}
    
