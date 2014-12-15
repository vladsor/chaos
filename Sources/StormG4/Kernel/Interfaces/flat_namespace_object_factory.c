#include <enviroment.h>

#include "../interfaces.h"

#include "../Classes/flat_namespace.h"

#include <Interfaces/flat_namespace_object_factory.h>

#include "flat_namespace_object_factory_interface.h"

#define DEBUG_MODULE_NAME L"FlatNamespaceObjectFactory"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

static int key_string_compare (void *key1, void *key2)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s (%S, %S)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        (wchar_t *) key1, (wchar_t *) key2);
        
    return (wstring_compare ((wchar_t *) key1, (wchar_t *) key2) == 0) ?
        CONDITION_EQUAL :
        CONDITION_NOT_EQUAL;
}

static unsigned int key_to_hash (void *key)
{
    unsigned int hash = 0;
    unsigned int i;
    wchar_t *string = (wchar_t *) key;
    unsigned int acc = 1;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s (%S)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        (wchar_t *) key);

    for (i = 0; i < wstring_length (string); i++)
    {
        hash = acc * string[i];
        acc *= 31;
    }

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s hash=%u\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        hash);

    return hash;
}

static uint64_t flat_namespace_object_create (context_t context UNUSED)
{
    flat_namespace_t *namespace;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
    
    memory_allocate ((void **) &namespace, sizeof (flat_namespace_t));

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: namespace = %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        namespace);

    memory_clear ((uint8_t *) namespace, sizeof (flat_namespace_t));

    memory_allocate ((void **) &(namespace->names_table), 
        SIZEOF_HASH_TABLE (100));

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
        L"%S: %s: names table = %p\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        namespace->names_table);

    hash_table_create (namespace->names_table, 100, key_to_hash, 
        key_string_compare);
        
    return (uint64_t) (address_t) namespace;
}

static void flat_namespace_object_destroy (context_t context UNUSED, 
    uint64_t data)
{
    flat_namespace_t *namespace;

    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s ()\n",
        DEBUG_MODULE_NAME, __FUNCTION__);
    
    namespace = (flat_namespace_t *) (address_t) data;
/*
    hash_table_destroy (namespace->names_table);
    memory_deallocate (namespace->names_table);
    memory_deallocate (namespace);
*/    
}

static flat_namespace_object_factory_interface_table_t table = 
{
    &flat_namespace_object_create,
    &flat_namespace_object_destroy,
};

/* Main function. */

interface_reference_t flat_namespace_object_factory_init (void)
{
    return flat_namespace_object_factory_interface_register (&table);
}

