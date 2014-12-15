#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

object_reference_t object_create (class_reference_t class_reference, 
    security_reference_t security_reference, sequence_t parameters, 
    uint32_t options)
{
    p_object_t object;
    p_class_t class;
    p_security_t security;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, {%p, %u}, %u)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        class_reference, security_reference, 
        parameters.data, parameters.count, 
        options);

#if defined (SECURITY_ENABLED)
    object_create_security_check ();
#endif
    
    class = class_translate_reference (class_reference);
    security = security_translate_reference (security_reference);

#if defined (CHECK_PARAMETERS)
    object_create_check_parameters (class, security, parameters, options);
#endif
    
    object = object_create_internal (class, security, parameters, options);

    object->header.is_static = FALSE;

    return (object_reference_t) object;
}

void object_destroy (object_reference_t object_reference)
{
    p_object_t object;

#if defined (SECURITY_ENABLED)
    object_destroy_security_check (object);
#endif

    object = object_translate_reference (object_reference);
    
#if defined (CHECK_PARAMETERS)
    object_destroy_check_parameters (object);
#endif

    object_destroy_internal (object);
}

object_reference_t object_get_current (void)
{
    return OBJECT_CURRENT;
}
    
object_reference_t object_get_kernel (void)
{
    return OBJECT_KERNEL;
}    

uint64_t object_get_data (object_reference_t object_reference)
{
    p_object_t object;

    object = object_translate_reference (object_reference);
    
    return object->data;
}
    
void object_set_data (object_reference_t object_reference, uint64_t object_data)
{
    p_object_t object;

    object = object_translate_reference (object_reference);
    
    object->data = object_data;
}    

class_reference_t object_get_class (object_reference_t object_reference)
{
    p_object_t object;

    object = object_translate_reference (object_reference);

    return (class_reference_t) object_get_class_internal (object);
}
    
interface_reference_t object_get_interface_by_id (
    object_reference_t object_reference, interface_id_t interface_id)
{
    p_object_t object;

    object = object_translate_reference (object_reference);

    return (interface_reference_t) object_get_interface_by_id_internal (object, 
        interface_id);
}
/*
event_supplier_reference_t object_get_event_supplier (
    object_reference_t object_reference, 
    uint32_t event_supplier_id)
{
    p_object_t object;
    
    object = object_translate_reference (object_reference);

    if (event_supplier_id >= object->event_suppliers.count)
    {
        return REFERENCE_NULL;
    }    

    return (event_supplier_reference_t) object_get_event_supplier_internal (
        object, event_supplier_id);
}    
    
event_consumer_reference_t object_get_event_consumer (
    object_reference_t object_reference, 
    uint32_t event_consumer_id)
{
    p_object_t object;

    object = object_translate_reference (object_reference);

    if (event_consumer_id >= object->event_consumers.count)
    {
        return REFERENCE_NULL;
    }    

    return (event_consumer_reference_t) object_get_event_consumer_internal (
        object, event_consumer_id);
}    
*/
security_reference_t object_get_security (
    object_reference_t object_reference)
{
    p_object_t object;
    
    object = object_translate_reference (object_reference);

    return (security_reference_t) object_get_security_internal (object);
}

void object_set_security (object_reference_t object_reference,
    security_reference_t security_reference)
{
    p_object_t object;
    p_security_t security;

    object = object_translate_reference (object_reference);
    security = security_translate_reference (security_reference);

    object_set_security_internal (object, security);
}

