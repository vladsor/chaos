#ifndef REPOSITORY_REFERENCE_H
#define REPOSITORY_REFERENCE_H

#ifndef DEBUG_MODULE_NAME
#define DEBUG_MODULE_NAME "Repository"
#endif

#ifndef DEBUG_LEVEL
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#endif

#include <debug/macros.h>
#include <exception/macros.h>

static inline void object_add_child_internal (p_object_t object, 
    p_reference_struct_t reference)
{
    if (object == NULL)
    {
        return;
    }
    
    list_node_insert (&object->childs, (list_node_t *) reference, 
        LIST_OPTION_LAST);
}

static inline void object_remove_child_internal (p_object_t object, 
    p_reference_struct_t reference)
{
    if (object == NULL)
    {
        return;
    }

    list_node_remove (&object->childs, (list_node_t *) reference);
}

#include "../Reference/Include/internal.h"

#endif /* REPOSITORY_REFERENCE_H */

