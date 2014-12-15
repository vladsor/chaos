
typedef void (method_function_t) (void);
typedef method_function_t * p_method_function_t;

typedef struct
{
    reference_struct_t header;

    p_method_description_t description;

    computer_reference_t computer;
    memory_reference_t memory;

    p_method_function_t function;
    uint64_t data;
} method_t;

typedef method_t * p_method_t;
typedef p_method_t * p_p_method_t;


// Static
extern method_reference_t method_create_static (p_method_t method);

extern void method_destroy_static (method_reference_t method_reference);

    
