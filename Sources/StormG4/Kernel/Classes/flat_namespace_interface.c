#include <enviroment.h>

#include <Interfaces/flat_namespace.h>
#include "flat_namespace_interface.h"

#define DEBUG_MODULE_NAME "FlatNamespace"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

static void add_entry_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_flat_namespace_add_entry_t add_entry;
    
    add_entry = (p_flat_namespace_add_entry_t) (address_t) function;
    
    add_entry (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0],
        (reference_t) ((uint32_t *) parameters_in.data)[1],
        (uint32_t) ((uint32_t *) parameters_in.data)[2]);
}

static void get_entry_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED,
    sequence_t parameters_out)
{
    p_flat_namespace_get_entry_t get_entry;
    reference_t reference;
    
    get_entry = (p_flat_namespace_get_entry_t) (address_t) function;
    
    reference = get_entry (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0],
        (p_uint32_t) ((uint32_t *) parameters_in.data)[1]);
        
    (reference_t) ((p_uint32_t) parameters_out.data)[0] = reference;
}

static void delete_entry_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out UNUSED)
{
    p_flat_namespace_delete_entry_t delete_entry;
    
    delete_entry = (p_flat_namespace_delete_entry_t) (address_t) function;
    
    delete_entry (context,
        (p_wchar_t) ((uint32_t *) parameters_in.data)[0]);
}

static void list_entries_wrapper (uint64_t function, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout UNUSED, 
    sequence_t parameters_out)
{
    p_flat_namespace_list_entries_t list_entries;
    uint32_t start;
    sequence_t names_seq;
    uint32_t count;
    
    list_entries = (p_flat_namespace_list_entries_t) (address_t) function;
    start = ((p_uint32_t) parameters_in.data)[0];
    
    count = list_entries (context, names_seq, start);
        
    (uint32_t) ((p_uint32_t) parameters_out.data)[0] = count;
}

static description_reference_t method_description_add_entry;
static description_reference_t method_description_get_entry;
static description_reference_t method_description_delete_entry;
static description_reference_t method_description_list_entries;

static method_reference_t methods[METHOD_FLAT_NAMESPACE_NUMBER];
static sequence_t method_seq = {data: methods, 
    count: METHOD_FLAT_NAMESPACE_NUMBER};

static description_reference_t interface_description;

interface_reference_t flat_namespace_interface_register (
    p_flat_namespace_interface_table_t table)
{
    sequence_t empty_seq = {data: NULL, count: 0};
    interface_reference_t interface;

    method_description_add_entry = method_description_register (
        METHOD_FLAT_NAMESPACE_ADD_ENTRY_ID,
        L"add_entry",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_FLAT_NAMESPACE_ADD_ENTRY_ID] = method_create_dynamic (
        method_description_add_entry, REFERENCE_NULL, MEMORY_CURRENT,
        &add_entry_wrapper, (address_t) table->add_entry, 0);
        
    method_description_get_entry = method_description_register (
        METHOD_FLAT_NAMESPACE_GET_ENTRY_ID,
        L"get_entry",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_FLAT_NAMESPACE_GET_ENTRY_ID] = method_create_dynamic (
        method_description_get_entry, REFERENCE_NULL, MEMORY_CURRENT,
        &get_entry_wrapper, (address_t) table->get_entry, 0);

    method_description_delete_entry = method_description_register (
        METHOD_FLAT_NAMESPACE_DELETE_ENTRY_ID,
        L"delete_entry",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_FLAT_NAMESPACE_DELETE_ENTRY_ID] = method_create_dynamic (
        method_description_delete_entry, REFERENCE_NULL, MEMORY_CURRENT,
        &delete_entry_wrapper, (address_t) table->delete_entry, 0);

    method_description_list_entries = method_description_register (
        METHOD_FLAT_NAMESPACE_LIST_ENTRIES_ID,
        L"list_entries",
        METHOD_TYPE_DYNAMIC,
        NULL,
        empty_seq,
        empty_seq);

    methods[METHOD_FLAT_NAMESPACE_LIST_ENTRIES_ID] = method_create_dynamic (
        method_description_list_entries, REFERENCE_NULL, MEMORY_CURRENT,
        &list_entries_wrapper, (address_t) table->list_entries, 0);
    
    interface_description = interface_description_register (
        INTERFACE_FLAT_NAMESPACE_ID,
        L"flat_namespace",
        INTERFACE_TYPE_DYNAMIC,
        empty_seq);
    
    interface = interface_create (interface_description, method_seq, 
        REFERENCE_NULL, 0);
    
    return interface;
}



