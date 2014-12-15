
#ifndef REPOSITORY_METHOD_INTERNAL_H
#define REPOSITORY_METHOD_INTERNAL_H

static inline p_method_t method_create_static_internal (p_method_t method)
{
    description_reference_acquire_internal (method->description);
//    reference_acquire_internal (method->memory);
//    reference_acquire_internal (method->computer);

    reference_create_internal (&method->header, REFERENCE_TYPE_METHOD);
    return method;
}

static inline void method_destroy_static_internal (p_method_t method)
{
    reference_destroy_internal (method);

//    reference_release_internal (method->computer);
//    reference_release_internal (method->memory);
    description_reference_release_internal (method->description);
}

static inline p_method_t method_create_internal (
    description_reference_t method_description, 
    p_computer_t method_computer,
    p_memory_t method_memory,
    p_method_function_t method_function, uint64_t method_data,
    uint32_t options UNUSED)
{
    p_method_t method;

    DEBUG_PRINT (DEBUG_LEVEL_INFORMATIVE, 
        "%s: %s (%p, %p, %p)\n",
        DEBUG_MODULE_NAME, __FUNCTION__,
        method_description, method_computer, method_function);
    
    memory_allocate ((void **) &method, sizeof (method_t));

    method->description = method_description;

    method->computer = method_computer;
    method->memory = method_memory;
    method->function = method_function;
    method->data = method_data;

    return method_create_static_internal (method);
}

static inline void method_destroy_internal (p_method_t method)
{
    method_destroy_static_internal (method);

    memory_deallocate (method);
}

static inline p_method_function_t method_get_function_internal (
    p_method_t method)
{
    return method->function;
}
    
static inline uint32_t method_get_type_internal (p_method_t method)
{
    return method->description->type;
}    

static inline uint64_t method_get_data_internal (p_method_t method)
{
    return method->data;
}
    
#endif /* !REPOSITORY_METHOD_INTERNAL_H */

