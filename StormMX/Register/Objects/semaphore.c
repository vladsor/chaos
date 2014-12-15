#include <enviroment.h>

#include <Classes/semaphore.h>

#include "../objects.h"

#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct
{
    uint32_t st;
} state_t;

enum
{
    STATE_UNLOCKED,
    STATE_LOCKED,
};

typedef struct
{
    state_t state;
    uint32_t value;
    thread_t *thread;

} semaphore_handle_data_t;

typedef struct
{
    uint32_t value;
    uint32_t max;
    
    semaphore_handle_data_t *locked_handles;

} semaphore_data_t;


static return_t semaphore_create (context_t *context, 
    void *semaphore_parameters)
{
    semaphore_data_t *semaphore;
    semaphore_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, semaphore_parameters);
    
    parameters = (semaphore_create_parameters_t *) semaphore_parameters;
    
    memory_allocate ((void **) &semaphore, sizeof (semaphore_data_t));
    
    semaphore->value = parameters->value;
    semaphore->max = parameters->max;
    semaphore->locked_handles = NULL;
    
    context->object_data = semaphore;
    
    return 0;
}

 
static return_t semaphore_destroy (context_t *context)
{
    semaphore_data_t *semaphore;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    semaphore = (semaphore_data_t *) context->object_data;
    
    memory_deallocate (semaphore);
    
    return 0;
}

static return_t semaphore_down (context_t *context, uint32_t value)
{
    semaphore_data_t *semaphore;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, context, value);
        
    semaphore = (semaphore_data_t *) context->object_data;
    
    if (semaphore->value < value)
    {
        semaphore_handle_data_t handle;
        
        handle.value = value;
        handle.state.st = STATE_LOCKED;
        handle.thread = thread_get_current ();
        semaphore->locked_handles = &handle;
        
        thread_lock (handle.thread);
    }
    
    semaphore->value -= value;
            
    return 0;
}

static return_t semaphore_up (context_t *context, uint32_t value)
{
    semaphore_data_t *semaphore;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %u)\n",
        __FILE__, __FUNCTION__, context, value);
        
    semaphore = (semaphore_data_t *) context->object_data;
/*    
    if (!mutex->is_locked)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Try to unlock not locked mutex.",
            __FILE__, __FUNCTION__);
            
        return -1;
    }

*/
    semaphore->value += value;

    if (semaphore->locked_handles != NULL && 
        semaphore->locked_handles->value <= semaphore->value)
    {
        thread_unlock (semaphore->locked_handles->thread);
        semaphore->locked_handles = NULL;
    }
        
    return 0;
}

object_create_method_t semaphore_create_method =
{
    &semaphore_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t semaphore_destroy_method =
{
    &semaphore_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &semaphore_create_method,
    (method_t *) &semaphore_destroy_method,
};

#define number_of_control_methods 2


static semaphore_up_method_t semaphore_up_method =
{
    SEMAPHORE_UP_METHOD (semaphore_up)
};

static semaphore_down_method_t semaphore_down_method =
{
    SEMAPHORE_DOWN_METHOD (semaphore_down)
};

static method_t *semaphore_methods[] = 
{
    (method_t *) &semaphore_up_method,
    (method_t *) &semaphore_down_method,
};

#define number_of_methods 2

static interface_id_t semaphore_control_id;
static interface_id_t semaphore_interface_id;
static class_id_t semaphore_class_id;
static handle_t class;

return_t semaphore_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;

    return_value = register_interface_register (&semaphore_control_id, 
        IID_SEMAPHORE_CONTROL, INTERFACE_TYPE_CONTROL, number_of_control_methods, 
        control_methods, NULL);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering control interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_interface_register (&semaphore_interface_id, 
        IID_SEMAPHORE, INTERFACE_TYPE_DYNAMIC, number_of_methods, 
        semaphore_methods, NULL);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering semaphore interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_class_register (&semaphore_class_id, 
        CID_SEMAPHORE, CLASS_TYPE_DYNAMIC, 1, &semaphore_interface_id, 
        semaphore_control_id);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering semaphore class failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }
    
    register_object_create (&class, integer_class_id, &semaphore_class_id);
    global_namespace_bind ("/storm/classes/semaphore", &class);

    return 0;
}

