#include <enviroment.h>

#define MODULE_NAME "Repository"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

class_reference_t class_create_static (p_class_t class)
{
    class_reference_t class_reference;
    
#if defined (SECURITY_ENABLED)
    class_create_security_check ();
#endif
    
    class_reference = (class_reference_t) class_create_static_internal (class);
    
    class->header.is_static = TRUE;        

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        class->transaction = transaction_current;

        class->transaction_slot_index = transaction_add_slot (
            transaction_current, class_reference, 
            OPERATION_CLASS_CREATE_STATIC);
    }
#endif

    return class_reference;    
}

void class_destroy_static (class_reference_t class_reference)
{
    p_class_t class = (p_class_t) class_reference;
    
#if defined (SECURITY_ENABLED)
    class_destroy_security_check (class);
#endif

#if defined (TRANSACTION_ENABLED)
    if ((class->transaction != NULL) && 
        (class->transaction != transaction_current))
    {
        THROW_SYSTEM (EXCEPTION_IS_LOCKED);
    }
    
    if (transaction_current != NULL)
    {
        if (class->transaction == NULL)
        {
#   if defined (REPOSITORY_EXTERNAL)
            hash_table_delete_element (classs_table, 
                (p_hash_element_t) class);
#   endif
            transaction_add_slot (transaction_current, class,
                OPERATION_CLASS_DESTROY_STATIC);
            return;
        }
        
        transaction_clear_slot (class->transaction, 
            class->transaction_slot_index);
    }
#endif

    class_destroy_static_internal (class);
}

