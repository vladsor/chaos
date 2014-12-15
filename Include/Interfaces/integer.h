
#define IID_INTEGER 0x00000D01

enum
{
    MID_INTEGER_GET,
    MID_INTEGER_SET,
};

typedef return_t (integer_get_function_t) (context_t *context, uint32_t *value);
typedef return_t (integer_set_function_t) (context_t *context, uint32_t value);
    
typedef struct
{
    integer_get_function_t *get;
    integer_set_function_t *set;
} integer_interface_t;

typedef struct
{
    integer_get_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} integer_get_method_t;

#define INTEGER_GET_METHOD(function) \
    (&(function)), \
    (MID_INTEGER_GET), \
    (sizeof (uint32_t *)), \
    (1), \
    { \
        {sizeof (uint32_t *)}, \
    }    

typedef struct
{
    integer_set_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} integer_set_method_t;

#define INTEGER_SET_METHOD(function) \
    (&(function)), \
    (MID_INTEGER_SET), \
    (sizeof (uint32_t)), \
    (1), \
    { \
        {sizeof (uint32_t)}, \
    }    

#define integer$get(handle,value) \
    ((integer_interface_t *) ((handle)->functions))->get ( \
        &((handle)->context), \
        (value))

#define integer$set(handle,value) \
    ((integer_interface_t *) ((handle)->functions))->set ( \
        &((handle)->context), \
        (value))



