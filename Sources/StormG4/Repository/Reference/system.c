#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include <debug/macros.h>
#include <exception/macros.h>

#include "../Include/internal.h"

uint32_t magic_number_table[] =
{
    [REFERENCE_TYPE_METHOD] = REFERENCE_MAGIC_NUMBER_METHOD,
    [REFERENCE_TYPE_INTERFACE] = REFERENCE_MAGIC_NUMBER_INTERFACE,
    [REFERENCE_TYPE_CLASS] = REFERENCE_MAGIC_NUMBER_CLASS,
    [REFERENCE_TYPE_SECURITY] = REFERENCE_MAGIC_NUMBER_SECURITY,
    [REFERENCE_TYPE_OBJECT] = REFERENCE_MAGIC_NUMBER_OBJECT,
    [REFERENCE_TYPE_HANDLE] = REFERENCE_MAGIC_NUMBER_HANDLE,

    [REFERENCE_TYPE_EVENT_SUPPLIER_INTERFACE] = 
        REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER_INTERFACE,
    [REFERENCE_TYPE_EVENT_SUPPLIER] = REFERENCE_MAGIC_NUMBER_EVENT_SUPPLIER,
    [REFERENCE_TYPE_EVENT_CONSUMER_INTERFACE] = 
        REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER_INTERFACE,
    [REFERENCE_TYPE_EVENT_CONSUMER] = REFERENCE_MAGIC_NUMBER_EVENT_CONSUMER,

    [REFERENCE_TYPE_EVENT_QUEUE] = REFERENCE_MAGIC_NUMBER_EVENT_QUEUE,
};

reference_t reference_acquire (reference_t reference)
{
    return reference_acquire_internal (reference);
}
    
void reference_release (reference_t reference)
{
    reference_release_internal (reference);
}    

uint32_t reference_get_type (reference_t reference)
{
    return reference_get_type_internal (reference);
}
    
object_reference_t reference_get_owner (reference_t reference)
{
    return reference_get_owner_internal (reference);
}
    
uint32_t reference_get_number_of_references (reference_t reference)
{
    return reference_get_number_of_references_internal (reference);
}    

bool reference_is_nill (reference_t reference)
{
    return reference_is_nill_internal (reference);
}
    
bool reference_is_exists (reference_t reference)
{
    return reference_is_exists_internal (reference); 
}
    
bool reference_equals (reference_t reference, reference_t reference2)
{
    return reference_equals_internal (reference, reference2);
}

