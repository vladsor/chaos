#include <enviroment.h>

#include <string.h>
#include <hash_table.h>

#include <Interfaces/namespace.h>

#include "../objects.h"

#include <exception/macros.h>

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#define FORCE_CREATE TRUE

typedef struct 
{
    hash_table_t *names_table;
} flat_namespace_t;

typedef struct
{
    flat_namespace_t root;
    
} namespace_t;

static namespace_t global_namespace;

enum
{
    NAME_TYPE_OBJECT,
    NAME_TYPE_INTERNAL_NAMESPACE,
    NAME_TYPE_LINK,
    NAME_TYPE_EXTERNAL_NAMESPACE,
};

typedef struct
{
    HASH_ELEMENT_PART;
    
    char name[STRING_MAX_LENGTH];
    unsigned int type;
    
    union
    {
        handle_t handle;
        flat_namespace_t *child_namespace;  
        struct flat_name_t *link;
    };
    
} flat_name_t;

static int key_string_compare (void *key1, void *key2)
{
    return (string_compare ((char *) key1, (char *) key2) == 0) ?
        CONDITION_EQUAL :
        CONDITION_NOT_EQUAL;
}

static return_t flat_namespace_create (flat_namespace_t *namespace)
{
    memory_allocate ((void **) &namespace->names_table, 
        SIZEOF_HASH_TABLE (100));
    hash_table_create (namespace->names_table, 100, string_to_hash, 
        key_string_compare);
        
    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_destroy (flat_namespace_t *namespace UNUSED)
{
//    hash_table_destroy ();
//    memory_deallocate (namespace->names_table);
    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_add_handle (flat_namespace_t *namespace, 
    char *name, handle_t *handle)
{
    return_t return_value;
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, handle);

    return_value = memory_allocate ((void **) &entry, sizeof (flat_name_t));
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Memory allocation failed.\n",
            __FILE__, __FUNCTION__);
            
        return return_value;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s::%s Entry: %p\n",
        __FILE__, __FUNCTION__, entry);
    
    string_copy (entry->name, name);
    entry->type = NAME_TYPE_OBJECT;
    
    register_handle_clone (handle, &entry->handle, 0);

    hash_table_add_element (namespace->names_table, (hash_element_t *) entry);

    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_add_external_namespace (
    flat_namespace_t *namespace, char *name, handle_t *namespace_handle)
{
    return_t return_value;
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, namespace_handle);

    return_value = memory_allocate ((void **) &entry, sizeof (flat_name_t));
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Memory allocation failed.\n",
            __FILE__, __FUNCTION__);
            
        return return_value;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s::%s Entry: %p\n",
        __FILE__, __FUNCTION__, entry);
    
    string_copy (entry->name, name);
    entry->type = NAME_TYPE_EXTERNAL_NAMESPACE;
    
    register_handle_clone (namespace_handle, &entry->handle, 1);

    hash_table_add_element (namespace->names_table, (hash_element_t *) entry);

    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_add_namespace (flat_namespace_t *namespace, 
    char *name, flat_namespace_t *child_namespace)
{
    return_t return_value;
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, child_namespace);

    return_value = memory_allocate ((void **) &entry, sizeof (flat_name_t));

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Memory allocation failed.\n",
            __FILE__, __FUNCTION__);
            
        return return_value;
    }
    
    string_copy (entry->name, name);
    entry->type = NAME_TYPE_INTERNAL_NAMESPACE;
    entry->child_namespace = child_namespace;

    hash_table_add_element (namespace->names_table, (hash_element_t *) entry);

    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_delete_entry (flat_namespace_t *namespace, 
    char *name)
{
    flat_name_t *entry;

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    if (entry != NULL)
    {
        hash_table_delete_element (namespace->names_table, name); 
        memory_deallocate (entry);
    }

    return STORM_RETURN_SUCCESS;        
}

static return_t flat_namespace_get_handle (flat_namespace_t *namespace, 
    char *name, handle_t *handle)
{
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, handle);

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s::%s entry: %p\n",
        __FILE__, __FUNCTION__, entry);

    if (entry != NULL)
    {
        if (entry->type == NAME_TYPE_OBJECT)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
                "%s::%s Stored handle: %p, Class: %p\n",
                __FILE__, __FUNCTION__, &entry->handle, &entry->handle.class);
                
            register_handle_clone (&entry->handle, handle, 0);
            
            return STORM_RETURN_SUCCESS;        
        }
        else
        {
            return NAMESPACE_RETURN_NOT_HANDLE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "%s::%s No such entry.\n",
        __FILE__, __FUNCTION__);

    return NAMESPACE_RETURN_NAME_NOT_EXISTS;
}

static return_t flat_namespace_get_external_namespace (flat_namespace_t *namespace, 
    char *name, handle_t *handle)
{
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, handle);

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s::%s entry: %p\n",
        __FILE__, __FUNCTION__, entry);

    if (entry != NULL)
    {
        if (entry->type == NAME_TYPE_EXTERNAL_NAMESPACE)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
                "%s::%s Stored handle: %p, Class: %p\n",
                __FILE__, __FUNCTION__, &entry->handle, &entry->handle.class);
                
            register_handle_clone (&entry->handle, handle, 1);
            
            return STORM_RETURN_SUCCESS;        
        }
        else
        {
            return NAMESPACE_RETURN_NOT_HANDLE;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "%s::%s No such entry.\n",
        __FILE__, __FUNCTION__);

    return NAMESPACE_RETURN_NAME_NOT_EXISTS;
}

static return_t flat_namespace_get_namespace (flat_namespace_t *namespace, 
    char *name, flat_namespace_t **child)
{
    flat_name_t *entry;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s (%p, %s, %p)\n",
        __FILE__, __FUNCTION__, namespace, name, child);

    entry = (flat_name_t *) hash_table_search_element (namespace->names_table, 
        name); 

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE2,
        "%s::%s entry: %p\n",
        __FILE__, __FUNCTION__, entry);

    if (entry != NULL)
    {
        if (entry->type == NAME_TYPE_INTERNAL_NAMESPACE)
        {
            (*child) = entry->child_namespace;   
            
            return STORM_RETURN_SUCCESS;
        }
        else
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Not namespace: %s.\n",
                __FILE__, __FUNCTION__, name);
                
            return NAMESPACE_RETURN_NOT_NAMESPACE;
        }
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_WARNING,
        "%s::%s Name not exists: %s.\n",
        __FILE__, __FUNCTION__, name);

    return NAMESPACE_RETURN_NAME_NOT_EXISTS;
}

/*
return_t flat_namespace_list_entries (char *names[], uint32_t *number_of_entries)
{
}

*/


//const char *char_illegals = " ;+=[]',\"*\\<>?:|";
const char *char_illegals = " ;+=[]'\"*\\<>?|/";

static bool is_char_illegal (char c)
{
    int i;

    for (i = 0; char_illegals[i]; i++)
    {
        if (c == char_illegals[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

static bool get_element (char *full_name, char *element_name, 
    char **next_name)
{
    char *current = full_name;
    char *dest = element_name;
    
    (*next_name) = NULL;
    
    if (current[0] == '/')
    {
        current++;
    }

    while (current[0] != '\0' && current[0] != '/')
    {
        if (is_char_illegal (current[0]))
        {
            return FALSE;
        }

        dest[0] = current[0];
        dest++;
        current++;
    }
    
    dest[0] = '\0';

    (*next_name) = current;
    
    return TRUE;
}

void namespace_bind (context_t *context, char *name, handle_t *handle)
{
    return_t return_value;
    
    char element_name[256];
    char *current_name = name;
    char *next_name;
    flat_namespace_t *current_namespace = NULL;
    handle_t ext_namespace;
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (\"%s\", %p)\n",
        __FILE__, __FUNCTION__, name, handle);
        
    if (context == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else if (context->object_data == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else
    {
        THROW_SYSTEM (EXCEPTION_NOT_IMPLEMENTED);
    }

    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != '\0')
    {
        flat_namespace_t *next_namespace;

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s (%s, %s, %s)\n",
            __FILE__, __FUNCTION__, current_name, element_name, next_name);
            
        return_value = flat_namespace_get_namespace (current_namespace, 
                element_name, &next_namespace);
                
        if (return_value == NAMESPACE_RETURN_NOT_NAMESPACE)
        {
                return_value = flat_namespace_get_external_namespace (current_namespace, 
                    element_name, &ext_namespace);
                
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                        "%s::%s Invalid name: %s [%s-not namespace]\n",
                        __FILE__, __FUNCTION__, name, element_name);

                    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
                }
                break;
            }
            else if ((return_value == NAMESPACE_RETURN_NAME_NOT_EXISTS) && 
                FORCE_CREATE)
            {
                memory_allocate ((void **) &next_namespace, 
                    sizeof (flat_namespace_t));
                    
                flat_namespace_create (next_namespace);
                flat_namespace_add_namespace (current_namespace, element_name,
                    next_namespace);
            }
            else if (return_value != STORM_RETURN_SUCCESS)
            {

                DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                    "%s::%s Invalid name: %s [%s]\n",
                    __FILE__, __FUNCTION__, name, element_name);
                
                THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);    
        }
            
        current_namespace = next_namespace;
        current_name = next_name;
    }

    if (next_name == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Invalid name: %s\n",
            __FILE__, __FUNCTION__, name);
    
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != '\0')
    {
        namespace$bind (&ext_namespace, next_name, handle);
    }
    else
    {
        if (flat_namespace_add_handle (current_namespace, 
            element_name, handle) != STORM_RETURN_SUCCESS)
        {
            THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
    }
}

void namespace_rebind (context_t *context, char *old_name, char *new_name)
{
    handle_t handle;

    namespace_resolve (context, old_name, &handle);
    namespace_unbind (context, old_name);
    namespace_bind (context, new_name, &handle);
}

void namespace_resolve (context_t *context, char *name, handle_t *handle)
{
    return_t return_value;
    
    char element_name[256];
    char *current_name = name;
    char *next_name;
    flat_namespace_t *current_namespace = NULL;
    handle_t ext_namespace;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (\"%s\", %p)\n",
        __FILE__, __FUNCTION__, name, handle);

    if (context == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else if (context->object_data == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else
    {
        THROW_SYSTEM (EXCEPTION_NOT_IMPLEMENTED);
    }

    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != '\0')
    {
    
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s (%s, %s, %s)\n",
            __FILE__, __FUNCTION__, current_name, element_name, next_name);
            
        {
            flat_namespace_t *next_namespace;
            
            if (flat_namespace_get_namespace (current_namespace, element_name, 
                &next_namespace) != STORM_RETURN_SUCCESS)
            {
                return_value = flat_namespace_get_external_namespace (current_namespace, 
                    element_name, &ext_namespace);
                
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
                }
                
                break;
            }
            
            current_namespace = next_namespace;
        }
        current_name = next_name;
    }
    
    if (next_name == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Invalid name: %s\n",
            __FILE__, __FUNCTION__, name);
    
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != '\0')
    {
        namespace$resolve (&ext_namespace, next_name, handle);
    }
    else
    {
        if (flat_namespace_get_handle (current_namespace, 
            element_name, handle) != STORM_RETURN_SUCCESS)
        {
            THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
    }
}

void namespace_unbind (context_t *context, char *name)
{
    return_t return_value;
    
    char element_name[256];
    char *current_name = name;
    char *next_name;
    flat_namespace_t *current_namespace = NULL;
    handle_t ext_namespace;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (\"%s\")\n",
        __FILE__, __FUNCTION__, name);
    
    if (context == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else if (context->object_data == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else
    {
        THROW_SYSTEM (EXCEPTION_NOT_IMPLEMENTED);
    }
    
    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != '\0')
    {
        {
            flat_namespace_t *next_namespace;
            
            if (flat_namespace_get_namespace (current_namespace, element_name, 
                &next_namespace) != STORM_RETURN_SUCCESS)
            {
                return_value = flat_namespace_get_external_namespace (current_namespace, 
                    element_name, &ext_namespace);
                
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
                }
                break;
            }
            
            current_namespace = next_namespace;
        }
        current_name = next_name;
    }
    
    if (next_name == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Invalid name: %s\n",
            __FILE__, __FUNCTION__, name);
    
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != '\0')
    {
        namespace$unbind (&ext_namespace, next_name);
    }
    else
    {
        if (flat_namespace_delete_entry (current_namespace, 
            element_name) != STORM_RETURN_SUCCESS)
        {
            THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
    }
}
/*
return_t namespace_bind_link (namespace_t *namespace, char *name, 
    char *handle_name)
*/

void namespace_bind_namespace (context_t *context, char *name, 
    handle_t *namespace_handle)
{
    return_t return_value;
    
    char element_name[256];
    char *current_name = name;
    char *next_name;
    flat_namespace_t *current_namespace = NULL;
    handle_t ext_namespace;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (\"%s\", %p)\n",
        __FILE__, __FUNCTION__, name, namespace_handle);

    if (context == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else if (context->object_data == NULL)
    {
        current_namespace = &global_namespace.root;
    }
    else
    {
        THROW_SYSTEM (EXCEPTION_NOT_IMPLEMENTED);
    }
    
    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != '\0')
    {

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s (%s, %s, %s)\n",
            __FILE__, __FUNCTION__, current_name, element_name, next_name);
            
        {
            flat_namespace_t *next_namespace;
            
            return_value = flat_namespace_get_namespace (current_namespace, 
                element_name, &next_namespace);
                
            if (return_value == NAMESPACE_RETURN_NOT_NAMESPACE)
            {
                return_value = flat_namespace_get_external_namespace (current_namespace, 
                    element_name, &ext_namespace);
                
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                        "%s::%s Invalid name: %s [%s-not namespace]\n",
                        __FILE__, __FUNCTION__, name, element_name);
                        
                    THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
                }
                break;
            }
            else if ((return_value == NAMESPACE_RETURN_NAME_NOT_EXISTS) && 
                FORCE_CREATE)
            {
                memory_allocate ((void **) &next_namespace, 
                    sizeof (flat_namespace_t));
                    
                flat_namespace_create (next_namespace);
                flat_namespace_add_namespace (current_namespace, element_name,
                    next_namespace);
            }
            else if (return_value != STORM_RETURN_SUCCESS)
            {

                DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                    "%s::%s Invalid name: %s [%s]\n",
                    __FILE__, __FUNCTION__, name, element_name);
                    
                THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
            }
            
            current_namespace = next_namespace;
        }
        current_name = next_name;
    }
    
    if (next_name == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Invalid name: %s\n",
            __FILE__, __FUNCTION__, name);
    
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != '\0')
    {
        namespace$bind_namespace (&ext_namespace, next_name, namespace_handle);
    }
    else
    {
        if (flat_namespace_add_external_namespace (current_namespace, 
            element_name, namespace_handle) != STORM_RETURN_SUCCESS)
        {
            THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
    }
}

static namespace_bind_method_t namespace_bind_method =
{
    NAMESPACE_BIND_METHOD (namespace_bind)
};

static namespace_bind_namespace_method_t namespace_bind_namespace_method =
{
    NAMESPACE_BIND_NAMESPACE_METHOD (namespace_bind_namespace)
};

static namespace_rebind_method_t namespace_rebind_method =
{
    NAMESPACE_REBIND_METHOD (namespace_rebind)
};

static namespace_resolve_method_t namespace_resolve_method =
{
    NAMESPACE_RESOLVE_METHOD (namespace_resolve)
};

static namespace_unbind_method_t namespace_unbind_method =
{
    NAMESPACE_UNBIND_METHOD (namespace_unbind)
};

static method_t *methods[] = 
{
    (method_t *) &namespace_bind_method,
    (method_t *) &namespace_bind_namespace_method,
    (method_t *) &namespace_rebind_method,
    (method_t *) &namespace_resolve_method,
    (method_t *) &namespace_unbind_method,
};

#define number_of_methods 4

return_t namespace_init (interface_id_t *interface_id)
{
    flat_namespace_create (&global_namespace.root);

    register_interface_register (interface_id, IID_NAMESPACE, 
        INTERFACE_TYPE_STATIC, NUMBER_OF_NAMESPACE_METHODS, methods, NULL);
    
    return 0;
}
/*
return_t namespace_deinit (void)
{
//    flat_namespace_destroy (namespace->root);
    return -1;
}

*/
