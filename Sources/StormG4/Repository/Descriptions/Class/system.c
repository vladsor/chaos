#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

description_reference_t class_description_register 
(
    id_t id,
    const wchar_t *name,
    uint32_t type,
    uint32_t number_of_interfaces,
    uint32_t number_of_event_suppliers,
    uint32_t number_of_event_consumers
)
{
    p_class_description_t description;
    
    memory_allocate ((void **) &description, sizeof (class_description_t));
    
    description->header.id = id;
    wstring_copy (description->name, name);
    description->type = type;
    description->number_of_interfaces = number_of_interfaces;
    description->number_of_event_suppliers = number_of_event_suppliers;
    description->number_of_event_consumers = number_of_event_consumers;

    return (description_reference_t) description;
}    

void class_description_unregister 
(
    description_reference_t description_reference UNUSED
)
{
}    

