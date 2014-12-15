// Dynamic
extern method_reference_t method_create (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_method_function_t function, uint64_t data,
    uint32_t options);

extern void method_destroy (method_reference_t method_reference);

extern void method_invoke (method_reference_t method, 
    computer_reference_t computer, 
    sequence_t parameters_in, sequence_t parameters_inout, 
    sequence_t parameters_out, 
    uint32_t options);

extern void method_invoke_async (method_reference_t method, 
    context_t context, 
    computer_reference_t computer, 
    sequence_t parameters, event_queue_reference_t event_queue);


// Utils
static inline method_reference_t method_create_dynamic (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_dynamic_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_object_create (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_object_create_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_object_destroy (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_object_destroy_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_event_supplier_create (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_event_supplier_create_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_event_supplier_destroy (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_event_supplier_destroy_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_event_supplier_handler (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_event_supplier_handler_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

static inline method_reference_t method_create_event_consumer_handler (
    description_reference_t description, 
    computer_reference_t computer,
    memory_reference_t memory,
    p_function_event_consumer_handler_t function, uint64_t data,
    uint32_t options)
{
    return method_create (description, computer, memory, 
        (p_method_function_t) function, data, options);
}

