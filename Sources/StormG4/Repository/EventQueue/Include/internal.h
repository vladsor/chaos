
static inline void event_queue_fire_internal (p_event_queue_t event_queue, 
    sequence_t event_data)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        event_queue, event_data.data, event_data.count);

    if (event_queue->capacity > 0)
    {
        event_queue->buffer_head++;
        event_queue->buffer_head %= event_queue->capacity;
    }    
    
    count_up (&event_queue->buffer_count);

    if (event_queue->consumer != NULL)
    {
        if (event_queue->consumer->type == EVENT_CONSUMER_TYPE_PUSH)
        {
            if (event_queue->type == EVENT_QUEUE_TYPE_ASYNCHRONOUS)
            {
                event_consumer_interface_fire_async_internal (
                    event_queue->consumer, event_data);
            }    
            else if (event_queue->type == EVENT_QUEUE_TYPE_SYNCHRONOUS)
            {
                event_consumer_interface_fire_sync_internal (
                    event_queue->consumer, event_data);
            }    
        }    
    }    
}    

static inline void event_queue_wait_internal (p_event_queue_t event_queue, 
    sequence_t event_data)
{
    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        event_queue, event_data.data, event_data.count);

    if (event_queue->supplier != NULL)
    {
        if (event_queue->supplier->type == EVENT_SUPPLIER_TYPE_PULL)
        {
            event_supplier_interface_wait_internal (event_queue->supplier, 
                event_data);
        }
        else
        {
            count_down (&event_queue->buffer_count);

            if (event_queue->capacity > 0)
            {
                event_queue->buffer_tail++;
                event_queue->buffer_tail %= event_queue->capacity;
            }    
        }    
    }    
}    


