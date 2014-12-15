#include <enviroment.h>

#include <Interfaces/storm_module_factory.h>
#include "storm_module_factory_interface.h"

#define DEBUG_MODULE_NAME "StormModuleFactory"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void create_wrapper (uint64_t function, context_t context, 
    class_reference_t class UNUSED, object_reference_t object, 
    sequence_t parameters_in)
{
    p_storm_module_factory_create_t create;
    uint64_t data;
    elf_header_t *elf_header;
    
    elf_header = (elf_header_t *) ((uint32_t *) parameters_in.data)[0];

    create = (p_storm_module_factory_create_t) (address_t) function;
    
    data = create (context, elf_header);
        
    object_set_data (object, data);
}

static void destroy_wrapper (uint64_t function, context_t context, 
    class_reference_t class UNUSED, object_reference_t object)
{
    p_object_factory_destroy_t destroy;
    uint64_t data;

    destroy = (p_object_factory_destroy_t) (address_t) function;
    
    data = object_get_data (object);
    destroy (context, data);
}

static description_reference_t method_description_create;
static description_reference_t method_description_destroy;

static method_reference_t methods[METHOD_OBJECT_FACTORY_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_OBJECT_FACTORY_NUMBER};

static description_reference_t interface_description;

interface_reference_t storm_module_factory_interface_register (
    p_storm_module_factory_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;
    
    method_description_create = method_description_register (
        METHOD_OBJECT_FACTORY_CREATE_ID,
        L"create",
        METHOD_TYPE_OBJECT_CREATE,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_OBJECT_FACTORY_CREATE_ID] = method_create_object_create (
        method_description_create, REFERENCE_NULL, MEMORY_CURRENT, 
        &create_wrapper, (address_t) table->create, 0);

    method_description_destroy = method_description_register (
        METHOD_OBJECT_FACTORY_DESTROY_ID,
        L"destroy",
        METHOD_OBJECT_FACTORY_DESTROY_ID,
        NULL,
        empty_seq,
        empty_seq);
        
    methods[METHOD_OBJECT_FACTORY_DESTROY_ID] = method_create_object_destroy (
        method_description_destroy, REFERENCE_NULL, MEMORY_CURRENT,
        &destroy_wrapper, (address_t) table->destroy, 0);

    methods[METHOD_OBJECT_FACTORY_CLONE_ID] = REFERENCE_NULL;

    interface_description = interface_description_register (
        INTERFACE_STORM_MODULE_FACTORY_ID,
        L"storm_module_factory",
        INTERFACE_TYPE_OBJECT_FACTORY,
        empty_seq);
        
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}




