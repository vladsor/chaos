#include <enviroment.h>

#define MODULE_NAME "object"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>

void object_create (p_object_reference_t p_object,
    class_reference_t class, 
    sequence_t own_interfaces, sequence_t joined_objects, 
    sequence_t parameters, uint32_t options)
{
    handle_t handle;
    uint32_t i;
    p_object_t object;
    p_object_t repository;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, {%p, %u}, {%p, %u}, %8.8X)\n",
        __FILE__, __FUNCTION__, class,
        joined_objects.data, joined_objects.length,
        parameters.data, parameters.length, options);

    if (p_object == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    if (class == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p, cid: %X, type: %u\n",
        __FILE__, __FUNCTION__,
         class, class->description->id, class->description->type);
    
    object = (p_object_t) (*p_object);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Object = %p\n",
        __FILE__, __FUNCTION__, object);

    repository = class->repository;
    
    class->number_of_references++;
    
    object->own_interfaces = own_interfaces;
    object->joined_objects = joined_objects;

    handle_open (repository, IID_OBJECT_CONTROL);
    object->data = object$create (repository, class, parameters, options);    
    handle_close (repository);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Returns.\n",
        __FILE__, __FUNCTION__);
}

void object_destroy (object_reference_t object);
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, object);

    if (object->number_of_references > 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not closed handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_IS_LOCKED);
    }

    object$destroy (repository, object->data);    

    class->number_of_references--;
}

class_reference_t object_get_class (object_reference_t object)
{
    return object->class;
}
    
interface_reference_t object_get_interface (object_reference_t object, 
    interface_id_t interface_id)
{
    uint32_t i, j;
    
    for (i = 0; i < object->own_interfaces; i++)
    {
        if (object->own_interfaces[i]->description.id == interface_id)
        {
            return object->own_interfaces[i];
        }
    }
    
    class = object->class;
    
    for (i = 0; i < class->interfaces; i++)
    {
        if (class->interfaces[i]->description.id == interfaces_id)
        {
            return class->interfaces[i];
        }
    }
    
    for (j=object->joined_objects; j >= 0; j--)
    {
        class = object->joined_objects[j]->class;
        
        for (i = 0; i < class->interfaces; i++)
        {
            if (class->interfaces[i]->description.id == interfaces_id)
            {
                return class->interfaces[i];
            }
        }
    }

    return NULL;
}

security_reference_t object_get_security (object_reference_t object)
{
    return object->security;
}

void object_set_security (object_reference_t object, 
    security_reference_t security)
{
    object->security = security;
}

/*
void repository_object_add_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
{
    
}

void repository_object_delete_joined_objects (handle_t handle, 
    uint32_t number_of_joined, handle_t joined_objects[])
{
}

void repository_object_add_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
{
}

void repository_object_delete_interfaces (handle_t handle, 
    uint32_t number_of_interfaces, interface_t interfaces[])
{
}
*/
