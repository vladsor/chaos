
#define IID_SYNCHRONIZER 0x00000D01

enum
{
    MID_SYNCHRONIZER_WAIT,
};

typedef return_t (synchronizer_wait_function_t) (context_t *context);
    
typedef struct
{
    synchronizer_wait_function_t *get;
} synchronizer_interface_t;

typedef struct
{
    synchronizer_wait_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[0];

} synchronizer_wait_method_t;

#define SYNCHRONIZER_WAIT_METHOD(function) \
    (&(function)), \
    (MID_SYNCHRONIZER_WAIT), \
    (0), \
    (0)
    
#define synchronizer$wait(handle) \
    ((synchronizer_interface_t *) ((handle)->functions))->wait ( \
        &((handle)->context)





