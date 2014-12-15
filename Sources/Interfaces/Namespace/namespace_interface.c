#include <enviroment.h>

#include <Interfaces/namespace.h>
#include "namespace_interface.h"

#define DEBUG_MODULE_NAME "namespace_interface"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

static void bind_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out UNUSED)
{
    p_namespace_bind_t bind;
    
    bind = (p_namespace_bind_t) (address_t) function;
    
    bind (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0], 
        (reference_t) ((uint32_t *) parameters_in.data)[1]);
}

static void rebind_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out UNUSED)
{
    p_namespace_rebind_t rebind;
    
    rebind = (p_namespace_rebind_t) (address_t) function;
    
    rebind (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0], 
        (p_wchar_t) ((uint32_t *) parameters_in.data)[1]);
}

static void resolve_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_namespace_resolve_t resolve;
    reference_t reference;

    resolve = (p_namespace_resolve_t) (address_t) function;
    
    reference = resolve (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0]);
        
    ((p_reference_t) (parameters_out.data))[0] = reference;
}

static void unbind_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out UNUSED)
{
    p_namespace_unbind_t unbind;
    
    unbind = (p_namespace_unbind_t) (address_t) function;
    
    unbind (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0]);
}

static description_reference_t method_description_bind;
static description_reference_t method_description_rebind;
static description_reference_t method_description_resolve;
static description_reference_t method_description_unbind;

static method_reference_t methods[METHOD_NAMESPACE_NUMBER];
static sequence_t method_seq = {data: methods, count: METHOD_NAMESPACE_NUMBER};

static description_reference_t interface_description;

interface_reference_t namespace_interface_register (
    p_namespace_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_bind = method_description_register (
        METHOD_NAMESPACE_BIND_ID,
        L"bind",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_NAMESPACE_BIND_ID] = method_create_dynamic (
        method_description_bind, REFERENCE_NULL, MEMORY_CURRENT,
        &bind_wrapper, (address_t) table->bind, 0);
        
    method_description_rebind = method_description_register (
        METHOD_NAMESPACE_REBIND_ID,
        L"rebind",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_NAMESPACE_REBIND_ID] = method_create_dynamic (
        method_description_rebind, REFERENCE_NULL, MEMORY_CURRENT,
        &rebind_wrapper, (address_t) table->rebind, 0);

    method_description_resolve = method_description_register (
        METHOD_NAMESPACE_RESOLVE_ID,
        L"resolve",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_NAMESPACE_RESOLVE_ID] = method_create_dynamic (
        method_description_resolve, REFERENCE_NULL, MEMORY_CURRENT,
        &resolve_wrapper, (address_t) table->resolve, 0);

    method_description_unbind = method_description_register (
        METHOD_NAMESPACE_REBIND_ID,
        L"unbind",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);
    
    methods[METHOD_NAMESPACE_UNBIND_ID] = method_create_dynamic (
        method_description_unbind, REFERENCE_NULL, MEMORY_CURRENT,
        &unbind_wrapper, (address_t) table->unbind, 0);
    
    interface_description = interface_description_register (
        INTERFACE_NAMESPACE_ID,
        L"namespace",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}



