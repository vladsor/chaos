#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>


description_reference_t method_description_register 
(
    id_t id,
    const wchar_t *name,
    uint32_t type,
    p_void_t return_type UNUSED,
    sequence_t parameter_descriptions UNUSED,
    sequence_t exception_descriptions UNUSED
)
{
    p_method_description_t description;
    
    memory_allocate ((void **) &description, sizeof (method_description_t));
    
    description->header.id = id;
    wstring_copy (description->name, name);
    description->type = type;

    return (description_reference_t) description;
}    

void method_description_unregister 
(
    description_reference_t description_reference UNUSED
)
{
}    

