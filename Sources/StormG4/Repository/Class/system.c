#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

class_reference_t class_create (description_reference_t class_description,
    sequence_t class_interfaces, sequence_t class_event_suppliers, 
    sequence_t class_event_consumers, handle_reference_t class_object_factory,
    uint32_t options)
{
    p_class_t class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        class_description, class_interfaces.data, class_object_factory);

#if defined (SECURITY_ENABLED)
    class_create_security_check ();
#endif

#if defined (CHECK_PARAMETERS)
    class_create_check_parameters (class_description, class_interfaces, 
        class_event_suppliers, class_event_consumers, class_object_factory);
#endif
    
    class = class_create_internal (class_description, 
        class_interfaces, class_event_suppliers, class_event_consumers, 
        class_object_factory, REFERENCE_NULL, options);

    class->header.is_static = FALSE;        

#if defined (TRANSACTION_ENABLED)
    if (transaction_current != NULL)
    {
        class->transaction = transaction_current;

        class->transaction_slot_index = transaction_add_slot (
            transaction_current, class_reference, 
            OPERATION_CLASS_CREATE);
    }
#endif

    return (class_reference_t) class;        
}

void class_destroy (class_reference_t class_reference)
{
    p_class_t class;

#if defined (SECURITY_ENABLED)
    class_destroy_security_check (class);
#endif
    
    class = class_translate_reference (class_reference);
    
#if defined (CHECK_PARAMETERS)
    class_destroy_check_parameters (class);
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
                OPERATION_class_DESTROY);
            return;
        }
        
        transaction_clear_slot (class->transaction, 
            class->transaction_slot_index);
    }
#endif

    class_destroy_internal (class);
}

void class_set_interfaces (class_reference_t class_reference, 
    sequence_t class_interfaces)
{
    p_class_t class;

#if defined (SECURITY_ENABLED)
    class_set_interface_security_check (class);
#endif

    class = class_translate_reference (class_reference);
    
#if defined (CHECK_PARAMETERS)
    class_set_interface_check_parameters (class);
#endif
    
    class_set_interfaces_internal (class, class_interfaces);
}
/*
sequence_t class_get_interfaces (class_reference_t class_reference)
{
    p_class_t class;

#if defined (SECURITY_ENABLED)
    class_get_interfaces_security_check (class);
#endif

    class = class_translate_reference (class_reference);
    
#if defined (CHECK_PARAMETERS)
    class_get_interfaces_check_parameters (class);
#endif
    
    return class_get_interfaces_internal (class);
}
*/
interface_reference_t class_get_interface_by_id (
    class_reference_t class_reference, interface_id_t interface_id)
{
    p_class_t class;

#if defined (SECURITY_ENABLED)
    class_get_interface_security_check (class);
#endif

    class = class_translate_reference (class_reference);
    
#if defined (CHECK_PARAMETERS)
    class_get_interface_check_parameters (class);
#endif
    
    return (interface_reference_t) class_get_interface_by_id_internal (class,
        interface_id);
}

