enum
{
    INTERFACE_TYPE_DYNAMIC,
    INTERFACE_TYPE_STATIC,
};

#define IID_NONE                (0)

typedef uint32_t interface_id_t;
typedef interface_id_t * p_interface_id_t;

typedef struct
{
    interface_id_t id;
    uint32_t interface_type;
    sequence_t method_descriptions;
    
} interface_description_t;

typedef interface_description_t * p_interface_description_t;

typedef struct
{
    HASH_ELEMENT_PART;
    
    interface_id_t id;

    char name[STRING_MAX_LENGTH];

    p_interface_description_t description; 
    sequence_t methods;

    uint32_t number_of_references;
} interface_t;

typedef interface_t * p_interface_t;

#if defined (__STORM_KERNEL__) || defined (__STORM_KERNEL_MODULE__)
typedef p_interface_t interface_reference_t;
#elif defined (__STORM_PROGRAM__)
typedef interface_id_t interface_reference_t;
#else
#error "Unknown target of object file"
#endif

typedef interface_reference_t * p_interface_reference_t;

extern void interface_register (p_interface_reference_t interface_reference, 
    p_interface_description_t interface_description, 
    sequence_t interface_methods);

extern void interface_unregister (interface_reference_t interface_reference);
/*
extern void interface_invoke_static_method (
    interface_reference_t interface_reference, 
    method_id_t method_id, sequence_t parameters, sequence_t return_value);

extern void interface_invoke_dynamic_method (
    interface_reference_t interface_reference,
    handle_reference_t handle_reference,
    method_id_t method_id, sequence_t parameters, sequence_t return_value);
*/
