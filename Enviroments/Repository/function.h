
// Common
typedef void (function_dynamic_t) (uint64_t key, context_t context, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out);
typedef function_dynamic_t * p_function_dynamic_t;

typedef void (function_static_t) (uint64_t key, 
    sequence_t parameters_in, sequence_t parameters_inout,
    sequence_t parameters_out);
typedef function_static_t * p_function_static_t;

// Object factory
typedef void (function_object_create_t) (uint64_t key, context_t context,
    class_reference_t class, object_reference_t object, 
    sequence_t parameters_in);
typedef function_object_create_t * p_function_object_create_t;

typedef void (function_object_destroy_t) (uint64_t key, context_t context,
    class_reference_t class, object_reference_t object);
typedef function_object_destroy_t * p_function_object_destroy_t;

// Event supplier factory
typedef void (function_event_supplier_create_t) (uint64_t key, 
    context_t context, object_reference_t object, 
    event_supplier_reference_t event_supplier, 
    sequence_t parameters_in);
typedef function_event_supplier_create_t * p_function_event_supplier_create_t;

typedef void (function_event_supplier_destroy_t) (uint64_t key, 
    context_t context, object_reference_t object, 
    event_supplier_reference_t event_supplier);
typedef function_event_supplier_destroy_t * p_function_event_supplier_destroy_t;

typedef bool (function_event_supplier_handler_t) (uint64_t key, 
    context_t context, sequence_t parameters_out);
typedef function_event_supplier_handler_t * p_function_event_supplier_handler_t;

typedef void (function_event_consumer_handler_t) (uint64_t key, 
    context_t context, sequence_t parameters_in);
typedef function_event_consumer_handler_t * p_function_event_consumer_handler_t;


