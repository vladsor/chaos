#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/group.h"
#include "../Include/object.h"

#include <debug/macros.h>
#include <exception/macros.h>

p_group_t group_create_static_internal (p_group_t group)
{
    uint32_t index;
    p_object_t object;
    
    for (index = 0; index < group->objects.count; index++)
    {
        object = ((p_p_object_t) group->objects.data)[index];
        
        reference_acquire_internal (object);
    }
    
    reference_create_internal (&group->header, REFERENCE_TYPE_GROUP);
    
    return group;
}
    
void group_destroy_static_internal (p_group_t group)
{
    uint32_t index;
    p_object_t object;
    
    reference_destroy_internal (group);

    for (index = 0; index < group->objects.count; index++)
    {
        object = ((p_p_object_t) group->objects.data)[index];
        
        reference_release_internal (object);
    }
}
    
p_group_t group_create_internal (sequence_t group_objects)
{
    p_group_t group;
    
    memory_allocate ((void **) &group, sizeof (group_t))
    
    group->objects.count = group_objects.count;
    
    memory_allocate ((void **) &group->objects.data, sizeof (p_group_t) * 
        group_objects.count);
        
    memory_copy (group->objects.data, group_objects.data, sizeof (p_group_t) * 
        group_objects.count);
    
    return group_create_static_internal (group);
}

void group_destroy_internal (p_group_t group)
{
    group_destroy_static_internal_group (group);
    
    memory_deallocate (group->objects.data);
    memory_deallocate (group);
}    

//p_group_t group_current = NULL;

