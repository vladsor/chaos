#include <enviroment.h>

#define DEBUG_MODULE_NAME "Repository"
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE
//#define DEBUG_LEVEL DEBUG_LEVEL_INFORMATIVE1
//#define DEBUG_LEVEL DEBUG_LEVEL_NONE

#include "../Include/internal.h"

#include <debug/macros.h>
#include <exception/macros.h>

event_supplier_reference_t event_supplier_create (
    object_reference_t object_reference, 
    event_id_t event_class_id, 
    sequence_t parameters, 
    uint32_t options)
{
    p_event_supplier_t sup;
    p_object_t object;
    
    object = (p_object_t) object_reference;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object_reference);
    
    memory_allocate ((void **) &sup, sizeof (event_supplier_t));
    memory_clear (sup, sizeof (event_supplier_t));
    
    sup->object = object;
    sup->interface = object_get_event_supplier_interface_by_id_internal (object, 
        event_class_id);
    
    return event_supplier_create_static_internal (sup, parameters, options);
}    

void event_supplier_destroy (
    event_supplier_reference_t reference)
{
    p_event_supplier_t sup;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference);
    
    sup = reference;
    
    event_supplier_destroy_static_internal (sup);
    
    memory_deallocate (sup);
}    

void event_supplier_fire_event (
    event_supplier_reference_t reference, 
    sequence_t event_data,
    uint32_t options UNUSED)
{
    p_event_supplier_t sup;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE1, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference, event_data.data, event_data.count);
    
    sup = reference;
    
    if (sup->queue != NULL)
    {
        event_queue_fire_internal (sup->queue, event_data);
    }    
}    

void event_supplier_set_data (
    event_supplier_reference_t reference, 
    uint64_t data)
{
    p_event_supplier_t sup;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference);
    
    sup = reference;
    sup->data = data;
}

uint64_t event_supplier_get_data (
    event_supplier_reference_t reference)
{
    p_event_supplier_t sup;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference);
    
    sup = reference;
    
    return sup->data;
}

void event_supplier_set_queue (
    event_supplier_reference_t reference, 
    event_queue_reference_t event_queue)
{
    p_event_supplier_t sup;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference, event_queue);
    
    sup = reference;
    
    sup->queue = (p_event_queue_t) event_queue;
    ((p_event_queue_t) event_queue)->supplier = sup->interface;
}
    
event_consumer_reference_t event_consumer_create (
    object_reference_t object_reference, 
    event_id_t event_class_id, 
    sequence_t parameters, 
    uint32_t options)
{
    p_event_consumer_t con;
    p_object_t object;
    
    object = (p_object_t) object_reference;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        object_reference);
    
    memory_allocate ((void **) &con, sizeof (event_consumer_t));
    memory_clear (con, sizeof (event_consumer_t));
    
    con->object = object;
    con->interface = object_get_event_consumer_interface_by_id_internal (object, 
        event_class_id);
    
    return event_consumer_create_static_internal (con, parameters, options);
}    
    
void event_consumer_destroy (
    event_consumer_reference_t reference)
{
    p_event_consumer_t cons;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference);
    
    cons = reference;
    
    memory_deallocate (cons);
}    

void event_consumer_wait_event (
    event_consumer_reference_t reference, 
    sequence_t event_data,
    uint32_t options UNUSED)
{
    p_event_consumer_t cons;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, {%p, %u})\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference, event_data.data, event_data.count);

    cons = reference;

    if (cons->queue != NULL)
    {
        event_queue_wait_internal (cons->queue, event_data);
    }    
}    

void event_consumer_set_queue (
    event_consumer_reference_t reference, 
    event_queue_reference_t event_queue UNUSED)
{
    p_event_consumer_t cons;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        reference);
    
    cons = reference;
    cons->queue = (p_event_queue_t) event_queue;
    ((p_event_queue_t) event_queue)->consumer = cons->interface;
}

void repository_event_supplier_init (void)
{
}
    
void repository_event_consumer_init (void)
{
}    

