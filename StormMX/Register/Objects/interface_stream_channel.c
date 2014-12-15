#include <enviroment.h>
#include <memory_inlines.h>

#include <Classes/stream_channel.h>
#include <Classes/integer.h>

#include "../objects.h"

//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL 11
#define DEBUG_LEVEL DEBUG_LEVEL_NONE
#include <debug/macros.h>

typedef struct
{
//    sempahore_t semaphore_full;
//    semaphore_t semaphore_empty;
//    mutex_t lock;

    uint64_t count;

    size_t block_size;
    uint32_t max_blocks;

    uint32_t free_slot;
    uint32_t last_slot;
    bool is_fool;
    
    thread_t *thread_read;
    thread_t *thread_write;
    
    uint8_t data[0];
} stream_channel_data_t;


static return_t stream_channel_create (context_t *context, 
    void *stream_channel_parameters)
{
    return_t return_value;

    stream_channel_data_t *channel;
    stream_channel_create_parameters_t *parameters;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p)\n",
        __FILE__, __FUNCTION__, context, stream_channel_parameters);
    
    parameters = (stream_channel_create_parameters_t *) stream_channel_parameters;
    
    return_value = memory_allocate ((void **) &channel, 
        sizeof (stream_channel_data_t) + parameters->block_size * 
            parameters->max_blocks);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return -1;
    }
    
    channel->count = 0;
    channel->block_size = parameters->block_size;
    channel->max_blocks = parameters->max_blocks;

    channel->free_slot = 0;
    channel->last_slot = 0;
    channel->is_fool = FALSE;
    channel->thread_read = NULL;
    channel->thread_write = NULL;
    
    context->object_data = channel;
    
    return 0;
}

 
static return_t stream_channel_destroy (context_t *context)
{
    stream_channel_data_t *channel = context->object_data;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);
    
    memory_deallocate (channel);
    
    return 0;
}

static return_t output_stream_open (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t output_stream_close (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t output_stream_write (context_t *context, 
    uint8_t *data, uint32_t count)
{
    stream_channel_data_t *channel = context->object_data;
    uint32_t written_count;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, context, data, count);

    if ((channel->block_size != 0) && (data == NULL))
    {
        return -1;
    }

    for (written_count = 0; written_count < count; written_count++)
    {
        channel->count++;
        
        if (channel->is_fool)
        {
            channel->thread_write = thread_get_current ();
            thread_lock (channel->thread_write);
        }
    
        if (channel->block_size > 0)
        {
            DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                "%s::%s #Block: %llu, Slot: %u/%u, Count: %u\n",
                __FILE__, __FUNCTION__, 
                channel->count, channel->free_slot, channel->last_slot, 
                written_count);

//            semaphore_down (channel->semaphore_empty);

            memory_copy (channel->data + channel->free_slot * 
                channel->block_size, data + written_count * 
                channel->block_size, channel->block_size);
                
            channel->free_slot++;
            channel->free_slot %= channel->max_blocks;
            
            if (channel->free_slot == channel->last_slot)
            {
                channel->is_fool = TRUE;
            }
            
            if (channel->thread_read != NULL)
            {
                thread_unlock (channel->thread_read);
                channel->thread_read = NULL;
            }
//            semaphore_up (channel->semaphore_full);        
        }
    }        
    
    return 0;
}

static return_t input_stream_open (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t input_stream_close (context_t *context UNUSED)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p)\n",
        __FILE__, __FUNCTION__, context);

    return 0;
}

static return_t input_stream_read (context_t *context, 
    uint8_t *data, uint32_t count)
{
    stream_channel_data_t *channel = context->object_data;
    uint32_t read_count;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s (%p, %p, %u)\n",
        __FILE__, __FUNCTION__, context, data, count);

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Stream channel: %u, %u\n",
        __FILE__, __FUNCTION__, channel->block_size, channel->max_blocks);

    for (read_count = 0; read_count < count; read_count++)
    {
        if ((channel->free_slot == channel->last_slot) && !channel->is_fool)
        {
            channel->thread_read = thread_get_current ();
            thread_lock (channel->thread_read);
        }

        if (channel->block_size > 0)
        {
//            semaphore_down (channel->semaphore_full);
            
            if (data != NULL)
            {
                DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
                    "%s::%s #Block: %llu, Slot: %u/%u, Count: %u\n",
                    __FILE__, __FUNCTION__, 
                    channel->count, channel->free_slot, channel->last_slot, 
                    read_count);
                    
                memory_copy (data + read_count * channel->block_size, 
                    channel->data + channel->last_slot * channel->block_size, 
                    channel->block_size);
            }

            if (channel->free_slot == channel->last_slot)
            {
                channel->is_fool = FALSE;
            }
        
            channel->last_slot++;
            channel->last_slot %= channel->max_blocks;

            if (channel->thread_write != NULL)
            {
                thread_unlock (channel->thread_write);
                channel->thread_write = NULL;
            }

//            semaphore_up (channel->semaphore_empty);        
        }
    }
    
    return 0;
}

object_create_method_t stream_channel_create_method =
{
    &stream_channel_create,
    MID_OBJECT_CREATE,
    sizeof (void *),
    1,
    {
        {sizeof (void *)}
    }
};

object_destroy_method_t stream_channel_destroy_method =
{
    &stream_channel_destroy,
    MID_OBJECT_DESTROY,
    0,
    0,
};

static method_t *control_methods[] = 
{
    (method_t *) &stream_channel_create_method,
    (method_t *) &stream_channel_destroy_method,
};

static output_stream_write_method_t output_stream_write_method =
{
    OUTPUT_STREAM_WRITE_METHOD (output_stream_write)
};

static method_t *output_stream_methods[] = 
{
    (method_t *) &output_stream_write_method,
};

interface_control_t output_stream_control = 
{
    output_stream_open, output_stream_close,
};

static input_stream_read_method_t input_stream_read_method =
{
    INPUT_STREAM_READ_METHOD (input_stream_read)
};

static method_t *input_stream_methods[] = 
{
    (method_t *) &input_stream_read_method,
};

interface_control_t input_stream_control = 
{
    input_stream_open, input_stream_close,
};

/*
static io_stream_read_method_t io_stream_read_method =
{
    IO_STREAM_READ_METHOD (input_stream_read)
};

static io_stream_write_method_t io_stream_write_method =
{
    IO_STREAM_WRITE_METHOD (input_stream_write)
};

static method_t *io_stream_methods[] = 
{
    (method_t *) &io_stream_read_method,
    (method_t *) &io_stream_write_method,
};
*/

static interface_id_t stream_channel_class_control_id;
static interface_id_t interface_ids[NUMBER_OF_STREAM_CHANNEL_INTERFACES];
static class_id_t stream_channel_class_id;
static handle_t class = {HANDLE_HEADER_EMPTY, NULL};

return_t stream_channel_init (int argc UNUSED, char *argv[] UNUSED)
{
    return_t return_value;

    return_value = register_interface_register (
        &stream_channel_class_control_id, IID_STREAM_CHANNEL_CLASS_CONTROL, 
        INTERFACE_TYPE_CONTROL, NUMBER_OF_OBJECT_CONTROL_METHODS, 
        control_methods, NULL);
    
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering control interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    return_value = register_interface_register (&interface_ids[0], 
        IID_INPUT_STREAM, INTERFACE_TYPE_DYNAMIC, 
        NUMBER_OF_INPUT_STREAM_METHODS, input_stream_methods, 
        &input_stream_control);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering 'input stream' interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Input stream iid: %X.\n",
        __FILE__, __FUNCTION__, interface_ids[0]);

    return_value = register_interface_register (&interface_ids[1], 
        IID_OUTPUT_STREAM, INTERFACE_TYPE_DYNAMIC, 
        NUMBER_OF_OUTPUT_STREAM_METHODS, output_stream_methods, 
        &output_stream_control);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering 'output stream' interface failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }        

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE,
        "%s::%s Output stream iid: %X.\n",
        __FILE__, __FUNCTION__, interface_ids[1]);

    return_value = register_class_register (&stream_channel_class_id, 
        CID_STREAM_CHANNEL, CLASS_TYPE_DYNAMIC, 
        NUMBER_OF_STREAM_CHANNEL_INTERFACES, interface_ids, 
        stream_channel_class_control_id);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_PRINT (DEBUG_LEVEL_ERROR,
            "%s::%s Registering 'stream channel' class failed (%X).\n",
            __FILE__, __FUNCTION__, return_value);
            
        return return_value;
    }
    
    integer$create (&class, stream_channel_class_id);

    global_namespace_bind ("/storm/classes/stream_channel", &class);

    return 0;
}
