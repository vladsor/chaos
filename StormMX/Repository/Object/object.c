#include <enviroment.h>

#define MODULE_NAME "object"
#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE

#include <debug/macros.h>
#include <exception/macros.h>


extern void object_create (p_object_reference_t object_reference,
    class_reference_t class_reference, 
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

    if (object_reference == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    if (class_reference == NULL)
    {
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p, cid: %X, type: %u\n",
        __FILE__, __FUNCTION__,
         class, class->description->id, class->description->type);
    
    object = (p_object_t) (*object_reference);

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

void object_destroy (object_reference_t object_reference);
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, object_reference);

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

class_reference_t object_get_class (
    object_reference_t object_reference)
{
    return object->class;
}
    
interface_reference_t object_get_interface (
    object_reference_t object_reference, interface_id_t interface_id)
{
}

security_reference_t object_get_security (
    object_reference_t object_reference)
{
}

void object_set_security (security_reference_t security_reference)
{
}

void handle_open (p_handle_reference_t handle_reference, 
    object_reference_t object_reference, interface_id_t interface_id,
    sequence_t parameters, uint32_t options)
{
    uint32_t i;
    p_class_t class;
    p_interface_t interface;
    handle_t repository;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %X)\n",
        __FILE__, __FUNCTION__, handle, interface_id);

    if (handle->object == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Empty handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }

    switch ((uint32_t) handle->class)    
    {
        case OBJECT_THIS:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_KERNEL:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_THIS_PROCESS:
        {
            class = NULL;
            break;
        }
        
        case OBJECT_THIS_THREAD:
        {
            class = NULL;
            break;
        }
        
        default:
        {
            class = handle->object->class;
        }
    };
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p.\n",
        __FILE__, __FUNCTION__, class);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Number of interfaces: %u.\n",
        __FILE__, __FUNCTION__, class->number_of_interfaces);

    for (i = 0; i < class->number_of_interfaces; i++)
    {
        interface = class->interfaces[i];

        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s Interface: %p {%u}.\n",
            __FILE__, __FUNCTION__, interface, i);
            
        if (interface->iid == interface_id)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Interface %X match.\n",
                __FILE__, __FUNCTION__, interface->real_iid);
                
            if (repository->interface != NULL)
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                    "%s::%s Calling user control function: %p.\n",
                    __FILE__, __FUNCTION__, interface->control->open);
                    
                repository$object_open (repository, handle, interface_id, 
                    options, parameters);
            }

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Number of methods: %u.\n",
                __FILE__, __FUNCTION__, interface->number_of_methods);

            handle->interface = interface;
            
            break;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s DONE\n",
        __FILE__, __FUNCTION__);
}

void handle_close (handle_reference_t handle_reference)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    if (handle->interface == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not opened handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW (EXCEPTION_INVALID_PARAMETERS);
    }
                 
    repository$object_close (repository, handle);    

    handle->object->number_of_handles--;
    
    if (handle->object->number_of_handles == 0)
    {
        repository_object_destroy (handle);
    }
    
    handle->interface = NULL;
}

void object_invoke_method (handle_t handle, method_id_t method_id, 
    sequence_t parameters, sequence_t return_value)
{
    p_method_t current_method;
    
    if (handle->current_interface == NULL)
    {
    }
    
    current_method = handle->current_interface->methods[method_id];
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Invoke ((%s) %s)->%s ()\n",
        __FILE__, __FUNCTION__,
        handle->current_interface->name,
        handle->current_object->name,
        handle->current_interface->method_descriptions[method_id]->name);
    
    if (handle->current_interface->type == INTERFACE_TYPE_STATIC)
    {
        asm (
            "addl %2, %%esp\n"
            "movsb %1, %%esp"
            "call %0"
            :
            :
                "g" (current_method),
                "m" (parameters.data),
                "g" (parameters.length));
    }
    else if (handle->current_interface->type == INTERFACE_TYPE_DYNAMIC)
    {
        context_t context;
        
        context.object_data = handle->current_object->data;
        context.handle_data = handle->current_interface_data;

        asm (
            "addl %2, %%esp\n"
            "movsb %1, %%esp\n"
            "addl %4, %%esp\n"
            "movsb %3, %%esp\n"
            "call %0"
            :
            :
                "g" (current_method),
                "m" (parameters.data),
                "g" (parameters.length),
                "m" (&context),
                "ig" (sizeof (context)));
    }
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
