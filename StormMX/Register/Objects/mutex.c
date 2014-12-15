#include <enviroment.h>

#include <Classes/mutex.h>

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
    thread_t *thread;

} mutex_handle_data_t;

typedef struct
{
    bool is_locked;
    mutex_handle_data_t *locked_handles;

} mutex_data_t;


static return_t mutex_create (context_t *context, 
    void *mutex_parameters)
{
    mutex_data_t *mutex;
    mutex_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, mutex_parameters);
    
    parameters = (mutex_create_parameters_t *) mutex_parameters;
    
    memory_allocate ((void **) &mutex, sizeof (mutex_data_t));
    
    mutex->is_locked = parameters->is_locked;
    mutex->locked_handles = NULL;
    
    context->object_data = mutex;
    
    return 0;
}

 
static return_t mutex_destroy (context_t *context)
{
    mutex_data_t *mutex;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    mutex = (mutex_data_t *) context->object_data;
    
    memory_deallocate (mutex);
    
    return 0;
}

static return_t mutex_lock (context_t *context)
{
    mutex_data_t *mutex;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
        
    mutex = (mutex_data_t *) context->object_data;
    
    if (mutex->is_locked)
    {
        mutex_handle_data_t handle;
        
        handle.state.st = STATE_LOCKED;
        handle.thread = thread_get_current ();
        mutex->locked_handles = &handle;
        
        thread_lock (handle.thread);
    }
    
    mutex->is_locked = TRUE;
            
    return 0;
}

static return_t mutex_unlock (context_t *context)
{
    mutex_data_t *mutex;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
        
    mutex = (mutex_data_t *) context->object_data;
    
    if (!mutex->is_locked)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Try to unlock not locked mutex.",
            __FILE__, __FUNCTION__);
            
        return -1;
    }

    mutex->is_locked = FALSE;

    if (mutex->locked_handles != NULL)
    {
        thread_unlock (mutex->locked_handles->thread);
        mutex->locked_handles = NULL;
    }
        
    return 0;
}

object_create_method_t mutex_create_method =
{
    &mutex_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t mutex_destroy_method =
{
    &mutex_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &mutex_create_method,
    (method_t *) &mutex_destroy_method,
};

#define number_of_control_methods 2


static mutex_lock_method_t mutex_lock_method =
{
    MUTEX_LOCK_METHOD (mutex_lock)
};

static mutex_unlock_method_t mutex_unlock_method =
{
    MUTEX_UNLOCK_METHOD (mutex_unlock)
};

static method_t *mutex_methods[] = 
{
    (method_t *) &mutex_lock_method,
    (method_t *) &mutex_unlock_method,
};

#define number_of_methods 2

static interface_id_t mutex_control_id;
static interface_id_t mutex_interface_id;
static class_id_t mutex_class_id;
static handle_t class;

return_t mutex_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;

    return_value = register_interface_register (&mutex_control_id, 
        IID_MUTEX_CONTROL, INTERFACE_TYPE_CONTROL, number_of_control_methods, 
        control_methods, NULL);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering control interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_interface_register (&mutex_interface_id, 
        IID_MUTEX, INTERFACE_TYPE_DYNAMIC, number_of_methods, 
        mutex_methods, NULL);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering mutex interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_class_register (&mutex_class_id, 
        CID_MUTEX, CLASS_TYPE_DYNAMIC, 1, &mutex_interface_id, 
        mutex_control_id);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering mutex class failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }
    
    register_object_create (&class, integer_class_id, &mutex_class_id);
    global_namespace_bind ("/storm/classes/mutex", &class);

    return 0;
}
