#include <enviroment.h>

#include "../interfaces.h"
#include "../classes.h"

#include <Interfaces/namespace.h>
#include "namespace_interface.h"

#include <Classes/flat_namespace_object.h>

#define DEBUG_MODULE_NAME L"Kernel{Namespace}"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>
#include <exception/macros.h>

#define FORCE_CREATE (TRUE)

//static handle_reference_t global_namespace;
extern handle_reference_t kernel_handle_root_flat_namespace;

const char *char_illegals = " ;+=[]'\"*\\<>?|/";

static bool is_char_illegal (wchar_t c)
{
    int i;
    
    if (c > UINT8_MAX)
    {
        return FALSE;
    }

    for (i = 0; char_illegals[i] != '\0'; i++)
    {
        if ((char) c == char_illegals[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}

static bool get_element (wchar_t *full_name, wchar_t *element_name, 
    wchar_t **next_name)
{
    wchar_t *current = full_name;
    wchar_t *dest = element_name;
    
    (*next_name) = NULL;
    
    if (current[0] == L'/')
    {
        current++;
    }

    while (current[0] != L'\0' && current[0] != L'/')
    {
        if (is_char_illegal (current[0]))
        {
            return FALSE;
        }

        dest[0] = current[0];
        dest++;
        current++;
    }
    
    dest[0] = L'\0';

    (*next_name) = current;
    
    return TRUE;
}

static void bind (context_t context,
    wchar_t *name, reference_t reference)
{
    wchar_t element_name[WSTRING_MAX_LENGTH];
    wchar_t *current_name;
    wchar_t *next_name;
    reference_t reference_current;
    handle_reference_t namespace_current;
    handle_reference_t namespace_external = REFERENCE_NULL;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (\"%S\", %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        name, reference);

    if (context.object_data == 0)
    {
        namespace_current = kernel_handle_root_flat_namespace;
    }
    else
    {
        namespace_current = (handle_reference_t) 
            (address_t) context.object_data;
    }

    current_name = name;

    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != L'\0')
    {
        uint32_t type;
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"%S: %s: (%S, %S, %S)\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            current_name, element_name, next_name);

        reference_current = flat_namespace$get_entry (namespace_current, 
            element_name, &type);
            
        if (type == NAME_TYPE_REFERENCE)
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
        else if (type == NAME_TYPE_INTERNAL_NAMESPACE)
        {
            namespace_current = reference_current;
        }
        else if (type == NAME_TYPE_EXTERNAL_NAMESPACE)

        {
            namespace_external = reference_current;
            break;
        }    
        else if (type == NAME_TYPE_NONE)
        {
            if (!FORCE_CREATE)
            {
                EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
            }
            else
            {
                object_reference_t namespace_new;
                handle_reference_t namespace_next;
                
                namespace_new = flat_namespace$create (
                    kernel_classes_info[
                        KERNEL_CLASS_FLAT_NAMESPACE_INDEX].class);
                        
                namespace_next = flat_namespace$handle$create (namespace_new);
                    
                flat_namespace$add_entry (namespace_current, element_name, 
                    namespace_next, NAME_TYPE_INTERNAL_NAMESPACE);
                    
                namespace_current = namespace_next;
            }    
        }
        else
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }    

        current_name = next_name;
    }
    
    if (next_name == NULL)
    {
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != L'\0')
    {
        namespace$bind (namespace_external, next_name, reference);
    }
    else
    {
        flat_namespace$add_entry (namespace_current, element_name, 
            reference, NAME_TYPE_REFERENCE);
    }
}

static void rebind (context_t context UNUSED,
    wchar_t *old_name UNUSED, wchar_t *new_name UNUSED)
{
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (\"%S\", \"%S\")\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        old_name, new_name);
}

static reference_t resolve (context_t context,
    wchar_t *name)
{
    wchar_t element_name[WSTRING_MAX_LENGTH];
    wchar_t *current_name;
    wchar_t *next_name;
    reference_t reference_current;
    handle_reference_t namespace_current;
    handle_reference_t namespace_external = REFERENCE_NULL;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (\"%S\")\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        name);

    if (context.object_data == 0)
    {
        namespace_current = kernel_handle_root_flat_namespace;
    }
    else
    {
        namespace_current = (handle_reference_t) 
            (address_t) context.object_data;
    }

    current_name = name;

    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != L'\0')
    {
        uint32_t type;
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"%S: %s: (%S, %S, %S)\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            current_name, element_name, next_name);

        reference_current = flat_namespace$get_entry (namespace_current, 
            element_name, &type);
            
        if (type == NAME_TYPE_REFERENCE)
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
        else if (type == NAME_TYPE_INTERNAL_NAMESPACE)
        {
            namespace_current = reference_current;
        }
        else if (type == NAME_TYPE_EXTERNAL_NAMESPACE)
        {
            namespace_external = reference_current;
            break;
        }    
        else
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }    

        current_name = next_name;
    }

    if (next_name == NULL)
    {
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != L'\0')
    {
        return namespace$resolve (namespace_external, next_name);
    }

    reference_current = flat_namespace$get_entry (namespace_current, 
    	element_name, NULL);

    if (reference_current == REFERENCE_NULL)
    {
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    return reference_current;
}

static void unbind (context_t context UNUSED,
    wchar_t *name)
{
    wchar_t element_name[WSTRING_MAX_LENGTH];
    wchar_t *current_name;
    wchar_t *next_name;
    reference_t reference_current;
    handle_reference_t namespace_current;
    handle_reference_t namespace_external = REFERENCE_NULL;
    
    DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE,
        L"%S: %s (\"%S\")\n",
        DEBUG_MODULE_NAME, __FUNCTION__, 
        name);

    if (context.object_data == 0)
    {
        namespace_current = kernel_handle_root_flat_namespace;
    }
    else
    {
        namespace_current = (handle_reference_t) 
            (address_t) context.object_data;
    }

    current_name = name;

    while (get_element (current_name, element_name, &next_name) && 
        next_name != NULL && next_name[0] != L'\0')
    {
        uint32_t type;
        
        DEBUG_PRINTW (DEBUG_LEVEL_INFORMATIVE1,
            L"%S: %s: %S, %S, %S\n",
            DEBUG_MODULE_NAME, __FUNCTION__, 
            current_name, element_name, next_name);

        reference_current = flat_namespace$get_entry (namespace_current, 
            element_name, &type);
            
        if (type == NAME_TYPE_REFERENCE)
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }
        else if (type == NAME_TYPE_INTERNAL_NAMESPACE)
        {
            namespace_current = reference_current;
        }
        else if (type == NAME_TYPE_EXTERNAL_NAMESPACE)
        {
            namespace_external = reference_current;
            break;
        }    
        else
        {
            EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
        }    

        current_name = next_name;
    }
    
    if (next_name == NULL)
    {
        EXCEPTION_THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    if (next_name[0] != L'\0')
    {
        namespace$unbind (namespace_external, next_name);
    }
    else
    {
        flat_namespace$delete_entry (namespace_current, element_name);
    }
}


static namespace_interface_table_t table = 
{
    bind:               &bind,
    rebind:             &rebind,
    resolve:            &resolve,
    unbind:             &unbind
};

/* Main function. */

interface_reference_t namespace_init (void)
{
    return namespace_interface_register (&table);
}

