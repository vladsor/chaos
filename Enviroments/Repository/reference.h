
enum reference_type_t
{
    REFERENCE_TYPE_METHOD,
    REFERENCE_TYPE_INTERFACE,
    REFERENCE_TYPE_CLASS,
    REFERENCE_TYPE_SECURITY,
    REFERENCE_TYPE_OBJECT,
    REFERENCE_TYPE_HANDLE,
    
    REFERENCE_TYPE_EVENT_SUPPLIER_INTERFACE,
    REFERENCE_TYPE_EVENT_SUPPLIER,
    REFERENCE_TYPE_EVENT_CONSUMER_INTERFACE,
    REFERENCE_TYPE_EVENT_CONSUMER,
    
    REFERENCE_TYPE_EVENT_QUEUE,
};

extern reference_t reference_acquire (reference_t reference);
extern void reference_release (reference_t reference);

extern uint32_t reference_get_type (reference_t reference);

extern object_reference_t reference_get_owner (reference_t reference);
extern void reference_set_owner (reference_t reference, 
    object_reference_t object_reference);

extern uint32_t reference_get_number_of_references (reference_t reference);

extern bool reference_is_nill (reference_t reference);
extern bool reference_is_exists (reference_t reference);
extern bool reference_equals (reference_t reference, reference_t reference2);


