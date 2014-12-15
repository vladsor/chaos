#include <enviroment.h>
#include <memory_inlines.h>

#include <Classes/event_channel.h>
#include <Classes/integer.h>

#include "../objects.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
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
    uint64_t count;
    uint32_t slot;

} event_provider_handle_data_t;

typedef struct
{
    uint64_t count;
    uint32_t slot;
    state_t state;
    thread_t *thread;

} event_observer_handle_data_t;

typedef struct
{
    uint64_t count;
    size_t data_size;
    uint32_t max_events;

    uint32_t free_slot;
    uint32_t last_slot;
    bool is_full;
    event_observer_handle_data_t *locked_handles;
    
    uint8_t data[0];
} event_channel_data_t;


static return_t event_channel_create (context_t *context, 
    void *event_parameters)
{
    event_channel_data_t *event;
    event_channel_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, event_parameters);
    
    parameters = (event_channel_create_parameters_t *) event_parameters;
    
    memory_allocate ((void **) &event, sizeof (event_channel_data_t) + 
        parameters->event_data_size * parameters->max_events);
    
    event->count = 0;
    event->data_size = parameters->event_data_size;
    event->max_events = parameters->max_events;

    event->free_slot = 0;
    event->last_slot = 0;
    event->is_full = FALSE;
    event->locked_handles = NULL;
    
    context->object_data = event;
    
    return 0;
}

 
static return_t event_channel_destroy (context_t *context)
{
    event_channel_data_t *event = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
    
    memory_deallocate (event);
    
    return 0;
}

static return_t event_provider_open (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t event_provider_close (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t event_provider_write (context_t *context, 
    uint8_t *event_data)
{
//    event_handle_t *event_handle = context->handler_data;
    
    event_channel_data_t *event_channel = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, event_data);


    if ((event_channel->data_size != 0) && (event_data == NULL))
    {
        return -1;
    }

    event_channel->count++;
    
    if (event_channel->data_size != 0)
    {
        DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
            "%s::%s #Event: %llu, Slot: %u\n",
            __FILE__, __FUNCTION__, 
            event_channel->count, event_channel->free_slot);

        if (event_channel->is_full)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s::%s Warning overflow [%u].\n",
                __FILE__, __FUNCTION__, 
                event_channel->max_events);
//            return OVERFLOW;
//            return -1;
            event_channel->last_slot++;
            event_channel->last_slot %= event_channel->max_events;
        }
        else
        {
//            event_channel->current_events++;
        }

        memory_copy (event_channel->data + event_channel->free_slot * 
            event_channel->data_size, event_data, event_channel->data_size);
                
        event_channel->free_slot++;
        event_channel->free_slot %= event_channel->max_events;
        
        if (event_channel->free_slot == event_channel->last_slot)
        {
            event_channel->is_full = TRUE;
        }
    }

    if (event_channel->locked_handles != NULL)
    {
        thread_unlock (event_channel->locked_handles->thread);
        event_channel->locked_handles = NULL;
    }
        
    return 0;
}

static return_t event_observer_open (context_t *context UNUSED)
{
    event_channel_data_t *event_channel = context->object_data;
    event_observer_handle_data_t *handle_data;        

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    memory_allocate ((void **) &handle_data, 
        sizeof (event_observer_handle_data_t));

    handle_data->count = event_channel->count;
    handle_data->state.st = STATE_UNLOCKED;
    handle_data->thread = thread_get_current ();

    context->handle_data = handle_data;

    return 0;
}

static return_t event_observer_close (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t event_observer_read (context_t *context, uint8_t *event_data)
{
    event_observer_handle_data_t *event_handle = context->handle_data;
    event_channel_data_t *event = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, event_data);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Event channel: %u, %u\n",
        __FILE__, __FUNCTION__, event->data_size, event->max_events);

    if (event_handle->count >= event->count)
    {
        event_handle->state.st = STATE_LOCKED;
        event->locked_handles = event_handle;
        event_handle->thread = thread_get_current ();
        
        thread_lock (event_handle->thread);
    }
    
    event_handle->count++;
    
    if (event->data_size > 0)
    {
        if (event_data != NULL)
        {
            memory_copy (event_data, event->data + event->last_slot * 
                event->data_size, event->data_size);
        }
        
        if (event->last_slot == event->free_slot)
        {
            event->is_full = FALSE;
        }
        
        event->last_slot++;
        event->last_slot %= event->max_events;
    }
    
    return 0;
}

static return_t event_observer_peek (context_t *context, uint8_t *event_data)
{
    event_observer_handle_data_t *event_handle = context->handle_data;
    event_channel_data_t *event = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, event_data);
    
    if (event_handle->count >= event->count)
    {
//        wait (timeout);
    }
    
    event_handle->count++;
    
    if ((event->data_size > 0) && (event_data != NULL))
    {
        memory_copy (event_data, event->data + event_handle->slot * 
            event->data_size, event->data_size);
    }
    
    return 0;
}

object_create_method_t event_channel_create_method =
{
    &event_channel_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t event_channel_destroy_method =
{
    &event_channel_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &event_channel_create_method,
    (method_t *) &event_channel_destroy_method,
};

#define number_of_control_methods 2

static event_provider_write_method_t event_channel_write_method =
{
    EVENT_PROVIDER_WRITE_METHOD (event_provider_write)
};

static method_t *event_provider_methods[] = 
{
    (method_t *) &event_channel_write_method,
};

#define number_of_provider_methods 1

interface_control_t event_provider_control = 
{
    event_provider_open, event_provider_close,
};

static event_observer_read_method_t event_channel_read_method =
{
    EVENT_OBSERVER_READ_METHOD (event_observer_read)
};

static event_observer_peek_method_t event_channel_peek_method =
{
    EVENT_OBSERVER_PEEK_METHOD (event_observer_peek)
};

static method_t *event_observer_methods[] = 
{
    (method_t *) &event_channel_read_method,
    (method_t *) &event_channel_peek_method,
};

#define number_of_observer_methods 2

interface_control_t event_observer_control = 
{
    event_observer_open, event_observer_close,
};

static interface_id_t event_channel_control_id;
static interface_id_t interface_ids[2];
static class_id_t event_channel_class_id;
static handle_t class;

return_t event_channel_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;

    return_value = register_interface_register (&event_channel_control_id, 
        IID_EVENT_CHANNEL, INTERFACE_TYPE_CONTROL, number_of_control_methods, 
        control_methods, NULL);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering control interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_interface_register (&interface_ids[0], 
        IID_EVENT_PROVIDER, INTERFACE_TYPE_DYNAMIC, number_of_provider_methods, 
        event_provider_methods, &event_provider_control);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering provider interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Event provider iid: %X.\n",
        __FILE__, __FUNCTION__, interface_ids[0]);

    return_value = register_interface_register (&interface_ids[1], 
        IID_EVENT_OBSERVER, INTERFACE_TYPE_DYNAMIC, number_of_observer_methods, 
        event_observer_methods, &event_observer_control);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering observer interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Event observer iid: %X.\n",
        __FILE__, __FUNCTION__, interface_ids[1]);

    return_value = register_class_register (&event_channel_class_id, 
        CID_EVENT_CHANNEL, CLASS_TYPE_DYNAMIC, 2, interface_ids, 
        event_channel_control_id);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering event channel class failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }
    
    integer$create (&class, event_channel_class_id);
    global_namespace_bind ("/storm/classes/event_channel", &class);

    return 0;
}
