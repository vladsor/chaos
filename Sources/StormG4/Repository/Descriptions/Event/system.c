#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

description_reference_t event_description_register 
(
    id_t id,
    const wchar_t *name,
    uint32_t data_length
)
{
    p_event_description_t description;
    
    memory_allocate ((void **) &description, sizeof (event_description_t));
    
    description->header.id = id;
    wstring_copy (description->name, name);
    description->data_length = data_length;

    return (description_reference_t) description;
}    

void event_description_unregister 
(
    description_reference_t description_reference UNUSED
)
{
}    

