#include <enviroment.h>

#include <Interfaces/namespace.h>
#include <Interfaces/flat_namespace.h>

#include "flat_namespace.h"
#include "flat_namespace_interface.h"

#define DEBUG_MODULE_NAME L"FlatNamespace"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

//static void flat_namespace_add_entry (context_t context, 
//    wchar_t *name, reference_t reference, uint32_t type)
static FLAT_NAMESPACE_ADD_ENTRY_WRAPPER (add_entry, context, name, reference, type)
{
    return_t return_value;
    flat_name_t *entry;
    flat_namespace_t *namespace;
    
    namespace = (flat_namespace_t *) (address_t) context.object_data;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %S, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        namespace, name, reference);

    return_value = memory_allocate ((void **) &entry, sizeof (flat_name_t));
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINTW (DEBUG_LEVEL_ERROR,
            L"%s: %s: Memory allocation failed.\n",
            DEBUG_MODULE_NAME, __FUNCTION__);
            
        return;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: entry = %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        entry);

    memory_clear (entry, sizeof (flat_name_t));
    
    wstring_copy (entry->name, name);
    entry->type = type;
    
    entry->reference = reference_acquire (reference);

    hash_table_add_element (namespace->names_table, (p_hash_element_t) entry);

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: All done.\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
}

//static reference_t flat_namespace_get_entry (context_t context, 
//    wchar_t *name, p_uint32_t type)
static FLAT_NAMESPACE_GET_ENTRY_WRAPPER (get_entry, context, name, type)
{
    flat_name_t *entry;
    flat_namespace_t *namespace;
    
    namespace = (flat_namespace_t *) (address_t) context.object_data;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %S, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        namespace, name, type);

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: entry = %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__, entry);

    if (entry != NULL)
    {
        if (type != NULL)
        {
            (*type) = entry->type;
        }    
                   
        return reference_acquire (entry->reference);
    }
    
    if (type != NULL)
    {
        (*type) = NAME_TYPE_NONE;
    }    

    DEBUG_PRINTW (DEBUG_LEVEL_WARNING,
        L"%S: %s: No such entry.\n",
        DEBUG_MODULE_NAME, __FUNCTION__);

    return REFERENCE_NULL;
}

//static void flat_namespace_delete_entry (context_t context, 
//    wchar_t *name)
static FLAT_NAMESPACE_DELETE_ENTRY (delete_entry, context, name)
{
    flat_name_t *entry;
    flat_namespace_t *namespace;
    
    namespace = (flat_namespace_t *) (address_t) context.object_data;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %S)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        namespace, name);

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    if (entry != NULL)
    {
        reference_release (entry->reference);
        
        hash_table_delete_element (namespace->names_table, name); 
        memory_deallocate (entry);
    }
}

//static uint32_t flat_namespace_list_entries (context_t context, 
//    sequence_t names, uint32_t start)
static FLAT_NAMESPACE_LIST_ENTRIES (list_entries, context, names, start)
{
    p_flat_name_t entry;
    uint32_t index;
    iterator_t *i;
    flat_namespace_t *namespace;
    
    namespace = (flat_namespace_t *) (address_t) context.object_data;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (%p, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        namespace, start);

    for (i = (iterator_t *) hash_table_get_iterator (namespace->names_table), 
        index = 0; iterator$has_next (i); index++)
    {
        entry = (p_flat_name_t) iterator$get_next (i);
        
        wstring_copy (((wchar_t **) names.data)[index], entry->name);
    }
    
    return iterator$has_next (i);
}

/* Main function. */

void flat_namespace_init (class_reference_t class_reference)
{
    flat_namespace_interface_table_t table = 
    {
        add_entry: &add_entry,
        get_entry: &get_entry,
        delete_entry: &delete_entry,
        list_entries: &list_entries
    };
    
    flat_namespace_interface_register (class_reference, &table);
}

