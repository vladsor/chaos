
#define IID_SEMAPHORE 0x00000003

enum
{
    MID_SEMAPHORE_UP,
    MID_SEMAPHORE_DOWN,
};

typedef return_t (semaphore_up_function_t) (context_t *context, uint32_t value);
typedef return_t (semaphore_down_function_t) (context_t *context, uint32_t value);

    
typedef struct
{
    semaphore_up_function_t *up;
    semaphore_down_function_t *down;
} semaphore_interface_t;

typedef struct
{
    semaphore_up_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} semaphore_up_method_t;

#define SEMAPHORE_UP_METHOD(function) \
    (&(function)), \
    (MID_SEMAPHORE_UP), \
    (sizeof (uint32_t)), \
    (1), \
    { \
        {sizeof (uint32_t)}, \
    }    
    
typedef struct
{
    semaphore_down_function_t *function;
    method_id_t method_id;
    uint32_t parameters_size;

    uint32_t number_of_parameters;

    parameter_t parameters[1];

} semaphore_down_method_t;

#define SEMAPHORE_DOWN_METHOD(function) \
    (&(function)), \
    (MID_SEMAPHORE_DOWN), \
    (sizeof (uint32_t)), \
    (1), \
    { \
        {sizeof (uint32_t)}, \
    }    

#define semaphore$up(handle,value) \
    ((semaphore_interface_t *) ((handle)->functions))->up ( \
        &((handle)->context), \
        (value))

#define semaphore$down(handle,value) \
    ((semaphore_interface_t *) ((handle)->functions))->down ( \
        &((handle)->context), \
        (value))



