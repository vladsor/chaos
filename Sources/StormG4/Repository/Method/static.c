#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

method_reference_t method_create_static (p_method_t method)
{
    method_reference_t method_reference;
    
#if defined (SECURITY_ENABLED)
    method_create_security_check ();
#endif
    
    method_reference = (method_reference_t) method_create_static_internal (
    	method);
    
    method->header.is_static = TRUE;

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        method_reference->transaction = transaction_current;

        method_reference->transaction_slot_index = transaction_add_slot (
            transaction_current, method_reference, 
            OPERATION_METHOD_CREATE_STATIC);
    }
#endif

    return method_reference;    
}

void method_destroy_static (method_reference_t method_reference)
{
    p_method_t method = (p_method_t) method_reference;

#if defined (SECURITY_ENABLED)
    method_destroy_security_check (method_reference);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((method->transaction != NULL) && 
        (method->transaction != transaction_current))
    {
        THROW_SYSTEM (method_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (method->transaction == NULL)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (methods_table, 
                (p_hash_element_t) method);
#   endif
            transaction_add_slot (transaction_current, method,
                OPERATION_METHOD_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (method->transaction, method->transaction_slot_index);
    }
#endif

    method_destroy_static_internal (method);
}


