#include <enviroment.h>

#include <hash_table.h>
#include <ipool.h>

#include <Classes/kernel.h>

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_WARNING
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

#include "objects.h"
#include "table.h"

#include <exception/macros.h>

static pool_of_integers_t *interface_ids_pool = NULL;
static hash_table_t *interfaces_table = NULL;

static pool_of_integers_t *class_ids_pool = NULL;
static hash_table_t *classes_table = NULL;

//static pool_of_integers_t *static_class_ids_pool = NULL;

handle_t object_kernel = {HANDLE_HEADER_EMPTY, NULL};

return_t register_object_create (handle_t *handle, class_id_t real_class_id, 
    void *data)
{
    class_t *class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %X, %p)\n",
        __FILE__, __FUNCTION__, handle, real_class_id, data);

    if ((handle->class != NULL) || (handle->context.object_data != NULL) || 
        (handle->context.handle_data != NULL) || (handle->functions != NULL))
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Not empty handle: %p, %p, %p, %p, %p.\n",
            __FILE__, __FUNCTION__, handle, handle->class, 
            handle->context.object_data, handle->context.handle_data, 
            handle->functions);
        
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    class = (class_t *) hash_table_search_element (classes_table, 
        &real_class_id);

    if (class == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Unknown class: %X\n",
            __FILE__, __FUNCTION__, real_class_id);
            
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }
    
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class: %p, cid: %X, type: %u\n",
        __FILE__, __FUNCTION__, class, class->cid, class->type);
    
    handle->class = class;

    if (class->type == CLASS_TYPE_DYNAMIC)
    {
//        handle->context.object_data = data;
        if (class->control.create != NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Invoke %p (%p)\n",
                __FILE__, __FUNCTION__, class->control.create, data);
                
            class->control.create (&handle->context, data);
        }
        else
        {
            if (data != NULL)
            {
                THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
            }
        }
        
        handle->context.handle_data = NULL;

        class->number_of_objects++;
    }
/*    
    else if (class->type == CLASS_TYPE_STATIC)
    {
        if (data != NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Ignoring data: %p.\n",
                __FILE__, __FUNCTION__, data);
        }

        handle->context.object_data = NULL;
        handle->context.handle_data = NULL;
        
        class->number_of_objects = 1;
    }
*/    
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Unsupported class type: %u.\n",
            __FILE__, __FUNCTION__, class->type);
        
        THROW_SYSTEM (EXCEPTION_NOT_IMPLEMENTED);
    }

    handle->functions = NULL;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Return success.\n",
        __FILE__, __FUNCTION__);

    return STORM_RETURN_SUCCESS;
}

return_t register_handle_clone (handle_t *handle, handle_t *new_handle, 
    uint32_t options)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, handle, new_handle);

    new_handle->class = handle->class;
    new_handle->context.object_data = handle->context.object_data;
    
    if (options & 1)
    {
        new_handle->context.handle_data = handle->context.handle_data;
        new_handle->functions = new_handle->functions;
    }
    else
    {
        new_handle->context.handle_data = NULL;
        new_handle->functions = NULL;
    }
    
    return STORM_RETURN_SUCCESS;
}

return_t register_object_open (handle_t *handle, interface_id_t interface_id)
{
    return_t return_value;
    uint32_t i, j;
    interface_t *interface;
    class_t *class;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %X)\n",
        __FILE__, __FUNCTION__, handle, interface_id);

    if (handle->class == NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Empty handle: %p.\n",
            __FILE__, __FUNCTION__, handle);
        
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
//        return -1;
    }
    else if ((uint32_t) handle->class == UINT32_MAX)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s Open kernel: %p.\n",
            __FILE__, __FUNCTION__, object_kernel.class);
            
        class = object_kernel.class;
        handle->context.object_data = object_kernel.context.object_data;
//        handle->context.object_data = NULL;
    }
    else
    {
        class = handle->class;
    }

    if (handle->functions != NULL)
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Already opened handle: %p, functions: %p.\n",
            __FILE__, __FUNCTION__, handle, handle->functions);
        
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
//        return -1;
    }

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
                
            if ((interface->control != NULL) && 
                (interface->control->open != NULL))
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                    "%s::%s Calling user control function: %p.\n",
                    __FILE__, __FUNCTION__, interface->control->open);
                    
                interface->control->open (&handle->context);
            }

            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                "%s::%s Number of methods: %u.\n",
                __FILE__, __FUNCTION__, interface->number_of_methods);
            
            if (interface->number_of_methods > 0)
            {
                method_function_t **functions;
            
                return_value = memory_allocate ((void **) &functions, 
                    interface->number_of_methods * 
                        sizeof (method_function_t *));
                        
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                        "%s::%s Memory allocation failed (%X).\n",
                        __FILE__, __FUNCTION__, return_value);
                        
                    return return_value;
                }

                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
                    "%s::%s Functions table: %p.\n",
                    __FILE__, __FUNCTION__, functions);
                
                for (j = 0; j < interface->number_of_methods;j++)
                {
                    functions[j] = interface->methods[j]->function;
                }
                
                handle->functions = functions;
            }
            break;
        }
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s DONE\n",
        __FILE__, __FUNCTION__);
    
    return STORM_RETURN_SUCCESS;
}

return_t register_object_reopen (handle_t *handle UNUSED, 
    interface_id_t interface_id UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    return STORM_RETURN_SUCCESS;
}

return_t register_object_close (handle_t *handle)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    if (handle->functions != NULL)
    {
        memory_deallocate (handle->functions);
    }
    
    handle->class->number_of_objects--;
    handle->class = NULL;
    handle->context.object_data = NULL;
    handle->context.handle_data = NULL; 
    handle->functions = NULL;
    
    return STORM_RETURN_SUCCESS;
}

return_t register_interface_register (interface_id_t *real_interface_id,
    interface_id_t interface_id, uint32_t interface_type, 
    uint32_t number_of_methods, method_t *methods[], 
    interface_control_t *control)
{
    return_t return_value;
    
    interface_t *interface;
    uint32_t i;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (rid: %p, iid: %X, nom: %u, methods: %p, control: %p)\n",
        __FILE__, __FUNCTION__, real_interface_id, interface_id, 
        number_of_methods, methods, control);

    pool_of_integers_allocate (interface_ids_pool, real_interface_id);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s riid = %u\n",
        __FILE__, __FUNCTION__, (*real_interface_id));

    return_value = memory_allocate ((void **) &interface, sizeof (interface_t) + 
        sizeof (method_t *) * number_of_methods);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return -1;
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Interface = %p\n",
        __FILE__, __FUNCTION__, interface);

    interface->real_iid = (*real_interface_id);
    interface->iid = interface_id;
    interface->type = interface_type;
    interface->number_of_classes = 0;
    interface->control = control;
    
    interface->number_of_methods = number_of_methods;

    for (i = 0; i < number_of_methods; i++)
    {
        interface->methods[i] = methods[i];        
    }

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Adding to storage: %p....\n",
        __FILE__, __FUNCTION__, interface);

    hash_table_add_element (interfaces_table, (hash_element_t *) interface);

    return STORM_RETURN_SUCCESS;
}

return_t register_interface_unregister (interface_id_t real_interface_id)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    hash_table_delete_element (interfaces_table, &real_interface_id);
    pool_of_integers_deallocate (interface_ids_pool, real_interface_id);

    return STORM_RETURN_SUCCESS;
}

return_t register_class_register (class_id_t *real_class_id, 
    class_id_t class_id, uint32_t class_type, uint32_t number_of_interfaces, 
    interface_id_t interface_ids[], interface_id_t class_control_id)
{
    class_t *class;
    uint32_t i;
    interface_t *interface;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (cid: %X, type: %u, noi: %u, ids: %p, ciid: %X)\n",
        __FILE__, __FUNCTION__, class_id, class_type, number_of_interfaces,
        interface_ids, class_control_id);

    if (class_type == CLASS_TYPE_DYNAMIC)
    {
        pool_of_integers_allocate (class_ids_pool, real_class_id);
        
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
            "%s::%s rcid = %u\n",
            __FILE__, __FUNCTION__, (*real_class_id));
    }
/*    
    else if (class_type == CLASS_TYPE_STATIC)
    {
        if ((class_id <= CID_STATIC_NONE) || (class_id > CID_STATIC_NONE + 
            CID_STATIC_POOL_LIMIT))
        {
            DEBUG_PRINT (DEBUG_LEVEL_ERROR,
                "%s::%s Static class ID is out range.\n",
                __FILE__, __FUNCTION__);
                
            return -1;
        }

        (*real_class_id) = class_id;
    }
*/
    else
    {
        DEBUG_PRINT (DEBUG_LEVEL_WARNING,
            "%s::%s Unknown class type: %X\n",
            __FILE__, __FUNCTION__, class_type);
  
        THROW_SYSTEM (EXCEPTION_INVALID_PARAMETERS);
    }

    memory_allocate ((void **) &class, sizeof (class_t) + 
      sizeof (interface_t *) * number_of_interfaces);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1,
        "%s::%s Class = %p\n",
        __FILE__, __FUNCTION__, class);

    class->real_cid = (*real_class_id);
    class->cid = class_id;
    class->number_of_objects = 0;
    class->type = class_type;

    if (class_control_id != IID_NONE)
    {
        interface = (interface_t *) hash_table_search_element (interfaces_table,
            &class_control_id);
        
        if (interface->type != INTERFACE_TYPE_CONTROL)
        {
            return -1;
        }
        
        class->control.create = 
            (object_create_function_t *) interface->methods[0]->function;
        class->control.destroy = 
            (object_destroy_function_t *) interface->methods[1]->function;
    }
    else
    {
        class->control.create = NULL;
        class->control.destroy = NULL;
//        return -1;
    }
    
    class->number_of_interfaces = number_of_interfaces;

    for (i = 0; i < number_of_interfaces; i++)
    {
        interface = (interface_t *) hash_table_search_element (interfaces_table,
            &interface_ids[i]);
            
        if (interface == NULL)
        {
            DEBUG_PRINT (DEBUG_LEVEL_WARNING,
                "%s::%s Unknown interface: %X {%u}\n",
                __FILE__, __FUNCTION__, interface_ids[i], i);
                
            return -1;
        }

        interface->number_of_classes++;
        class->interfaces[i] = interface;
    }

    hash_table_add_element (classes_table, (hash_element_t *) class);

    return STORM_RETURN_SUCCESS;
}

return_t register_class_unregister (class_id_t real_class_id)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    hash_table_delete_element (classes_table, &real_class_id);
    pool_of_integers_deallocate (class_ids_pool, real_class_id);

    return STORM_RETURN_SUCCESS;
}

static unsigned int iid_to_hash (void *key)
{
    return (unsigned int) (*(uint32_t *) key);
}

static int iid_compare (void *key1, void *key2)
{
    return (*(uint32_t *) key1) == (*(uint32_t *) key2) ? 
        CONDITION_EQUAL :
        CONDITION_NOT_EQUAL;
}

class_id_t kernel_class_id = CID_NONE;
extern interface_id_t namespace_interface_id;

return_t register_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;
    
    uint32_t i;
    uint32_t number_of_interfaces = 0;
    interface_id_t interface_ids[NUMBER_OF_BUILT_IN];

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s ()\n",
        __FILE__, __FUNCTION__);

    memory_allocate ((void **) &interface_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (IID_POOL_LIMIT));
    pool_of_integers_init (interface_ids_pool, IID_POOL_LIMIT);
    pool_of_integers_reserve (interface_ids_pool, IID_NONE);

    memory_allocate ((void **) &interfaces_table, SIZEOF_HASH_TABLE (100));
    hash_table_create (interfaces_table, 100, iid_to_hash, iid_compare);

    memory_allocate ((void **) &class_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (CID_POOL_LIMIT));
    pool_of_integers_init (class_ids_pool, CID_POOL_LIMIT);
    pool_of_integers_reserve (class_ids_pool, CID_NONE);

    memory_allocate ((void **) &classes_table, SIZEOF_HASH_TABLE (100));
    hash_table_create (classes_table, 100, iid_to_hash, iid_compare);
/*
    memory_allocate ((void **) &static_class_ids_pool, 
        SIZEOF_POOL_OF_INTEGERS (CID_STATIC_POOL_LIMIT));
    pool_of_integers_init (static_class_ids_pool, CID_STATIC_POOL_LIMIT);
    pool_of_integers_reserve (static_class_ids_pool, 0);
*/
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Registering built-in objects...\n",
        __FILE__, __FUNCTION__);
  
    for (i = 0; i < NUMBER_OF_BUILT_IN; i++)
    {
        if (objects_built_in[i].enabled)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s::%s Registering: %s...\n",
                __FILE__, __FUNCTION__, objects_built_in[i].name);
                
            return_value = (*objects_built_in[i].init) (
                &interface_ids[number_of_interfaces]);
                
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s::%s Result of registering %s: %u\n",
                __FILE__, __FUNCTION__, objects_built_in[i].name, return_value);
            
            number_of_interfaces++;
        }
    }
    
    register_class_register (&kernel_class_id, CID_KERNEL, CLASS_TYPE_DYNAMIC, 
        number_of_interfaces, interface_ids, IID_NONE);

    register_object_create ((handle_t *) &object_kernel, kernel_class_id, NULL);

    integer_init ();
    mutex_init (0, NULL);
    semaphore_init (0, NULL);
    event_channel_init (0, NULL);
    stream_channel_init (0, NULL);

    storm_module_init (0, NULL);
    
    return STORM_RETURN_SUCCESS;
}

