#include <enviroment.h>

//#include <Interfaces/event_supplier_factory.h>

#include "Include/event_supplier_factory_interface.h"

#define DEBUG_MODULE_NAME "EventSupplierFactory"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void create_wrapper (uint64_t function, context_t context, 
    object_reference_t object UNUSED, event_supplier_reference_t event_supplier, 
    sequence_t parameters_in UNUSED)
{
    p_event_supplier_factory_create_t create;
    
    create = (p_event_supplier_factory_create_t) (address_t) function;

    create (context, event_supplier);
}

static void destroy_wrapper (uint64_t function, context_t context, 
    object_reference_t object UNUSED, event_supplier_reference_t event_supplier)
{
    p_event_supplier_factory_destroy_t destroy;

    destroy = (p_event_supplier_factory_destroy_t) (address_t) function;

    destroy (context, event_supplier);
}

static description_reference_t method_description_create;
static description_reference_t method_description_destroy;

static method_reference_t methods[METHOD_EVENT_SUPPLIER_FACTORY_NUMBER];
static sequence_t method_seq = { data: methods, 
    count: METHOD_EVENT_SUPPLIER_FACTORY_NUMBER };

static description_reference_t interface_description;

interface_reference_t event_supplier_factory_interface_register (
    p_event_supplier_factory_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_create = method_description_register (
        METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID,
        L"create",
        METHOD_TYPE_EVENT_SUPPLIER_CREATE,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_EVENT_SUPPLIER_FACTORY_CREATE_ID] = 
        method_create_event_supplier_create (
            method_description_create, REFERENCE_NULL, MEMORY_CURRENT, 
            &create_wrapper, (address_t) table->create, 0);

    method_description_destroy = method_description_register (
        METHOD_EVENT_SUPPLIER_FACTORY_DESTROY_ID,
        L"destroy",
        METHOD_TYPE_EVENT_SUPPLIER_DESTROY,
        NULL,
        empty_seq,
        empty_seq);
        
    methods[METHOD_EVENT_SUPPLIER_FACTORY_DESTROY_ID] = 
        method_create_event_supplier_destroy (
            method_description_destroy, REFERENCE_NULL, MEMORY_CURRENT,
            &destroy_wrapper, (address_t) table->destroy, 0);

    interface_description = interface_description_register (
        INTERFACE_EVENT_SUPPLIER_FACTORY_ID,
        L"event_supplier_factory",
        INTERFACE_TYPE_EVENT_SUPPLIER_FACTORY,
        empty_seq);
        
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}

