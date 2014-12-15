
enum
{
    EVENT_SUPPLIER_TYPE_NONE,
    EVENT_SUPPLIER_TYPE_PUSH,
    EVENT_SUPPLIER_TYPE_PULL,
};    

enum
{
	METHOD_EVENT_SUPPLIER_HANDLER_ID,
};

// Static
extern 
    event_supplier_interface_reference_t 
        event_supplier_interface_create_static 
        (
            p_event_supplier_interface_t event_supplier_interface
        );
     
extern 
    void 
        event_supplier_interface_destroy_static 
        (
            event_supplier_interface_reference_t event_supplier_interface
        );

// Dynamic
extern 
    event_supplier_interface_reference_t 
        event_supplier_interface_create 
        (
//            uint32_t supplier_id,
            event_class_reference_t event_class, 
            int type, 
            method_reference_t handle,
//            reference_t event_supplier_factory,
            uint32_t options
        );

extern 
    void 
        event_supplier_interface_destroy 
        (
            event_supplier_interface_reference_t 
                event_supplier_interface_reference
        );

extern 
    void 
        event_supplier_interface_fire 
        (
            event_supplier_interface_reference_t 
                event_supplier_interface_reference, 
            context_t context, 
            event_queue_reference_t event_queue,
            sequence_t event_data
        );

extern 
    reference_t 
        event_supplier_interface_get_factory 
        (
            event_supplier_interface_reference_t 
                event_supplier_interface_reference
        );

extern 
    void 
        event_supplier_interface_set_factory 
        (
            event_supplier_interface_reference_t 
                event_supplier_interface_reference,
            reference_t factory
        );

